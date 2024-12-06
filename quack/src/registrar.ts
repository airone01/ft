import {join} from 'node:path';
import {readdir} from 'node:fs/promises';
import {
  type Client, Collection, REST, Routes,
} from 'discord.js';
import {z} from 'zod';
import {logger} from './logger.js';
import {env} from './env.js';
import {zSlashCommandBuilder} from './slash-command.js';

export const zCommandFile = z.object({
  handler: z.function(),
  metadata: zSlashCommandBuilder,
  guildOnly: z.boolean().default(false),
});
type CommandFile = z.infer<typeof zCommandFile>;
const commandsDirectory = join(import.meta.dirname, 'commands');

export const rest = new REST({version: '10'}).setToken(env.DISCORD_BOT_TOKEN);

export type ClientAndCommands = Client & {commands: Collection<string, CommandFile>};

export async function registerCommands(client: Client): Promise<void> {
  await registerInternalCommands(client);
  await registerExternalCommands(client);
}

async function registerInternalCommands(client: Client) {
  logger.pending('Building commands...');
  const commandFilesNames = (await readdir(join(import.meta.dirname, 'commands')))
    .filter(file => file.endsWith('.ts')); // eslint-disable-line unicorn/no-await-expression-member
  const commandFiles = await Promise.all(commandFilesNames.map(async file => import(join(commandsDirectory, file))));
  const commands = new Collection<string, CommandFile>();
  let commandsLength = 0;
  for (const file of commandFiles) {
    const {success, data: trueCommand, error} = zCommandFile.safeParse(file);
    if (!success) {
      logger.error(`Error parsing command file: ${error.toString()}`);
      continue;
    }

    commands.set(trueCommand.metadata.name, trueCommand);
    commandsLength++;
  }

  (client as ClientAndCommands).commands = commands;

  logger.star(`Registered ${commandsLength} commands internally`);
}

async function registerExternalCommands(client: Client) {
  const commands = (client as ClientAndCommands).commands;

  const commandsMetadata = commands
    .map(command => command.metadata);
  const guildCommandsMetadata = commands
    .filter(command => command.guildOnly)
    .map(command => command.metadata);
  const guilds = client.guilds.cache.map(guild => guild.id);

  await Promise.all(guilds.map(async guild => {
    await rest.put(Routes.applicationGuildCommands(env.DISCORD_OAUTH2_ID, guild), {body: guildCommandsMetadata});
  }));
  logger.info(`Sent ${guildCommandsMetadata.length} guild commands in ${guilds.length} guilds to Discord`);

  await rest.put(Routes.applicationCommands(env.DISCORD_OAUTH2_ID), {body: commandsMetadata});
  logger.info(`Sent ${commandsMetadata.length} global commands to Discord`);
}

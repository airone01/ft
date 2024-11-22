import {join} from 'node:path';
import {readdir} from 'node:fs/promises';
import {
  type Client, Collection, REST, Routes,
} from 'discord.js';
import {z} from 'zod';
import {logger} from './logger.js';
import {env} from './env.js';
import {zSlashCommandBuilder} from './slash-command.js';

const zCommandFile = z.object({
  handler: z.function(),
  metadata: zSlashCommandBuilder,
  guildOnly: z.boolean().default(false),
});
type CommandFile = z.infer<typeof zCommandFile>;
const commandsDirectory = join(import.meta.dirname, 'commands');

const rest = new REST({version: '10'}).setToken(env.DISCORD_BOT_TOKEN);

export async function registerCommands(client: Client): Promise<Collection<string, CommandFile>> {
  logger.pending('Building commands...');
  const commandFilesNames = (await readdir(join(import.meta.dirname, 'commands'), {recursive: true}))
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

  logger.success(`Built ${commandsLength} commands`);

  const commandsMetadata = commands
    .map(command => command.metadata);
  const guildCommandsMetadata = commands
    .filter(command => command.guildOnly)
    .map(command => command.metadata);
  const guilds = client.guilds.cache.map(guild => guild.id);
  await Promise.all(guilds.map(async guild => {
    await rest.put(Routes.applicationGuildCommands(env.DISCORD_CLIENT_ID, guild), {body: guildCommandsMetadata});
  }));
  logger.info(`Sent requests to register ${guildCommandsMetadata.length} guild commands in ${guilds.length} guilds`);
  await rest.put(Routes.applicationCommands(env.DISCORD_CLIENT_ID), {body: commandsMetadata});
  logger.info(`Sent requests to register ${commandsMetadata.length} global commands`);

  return commands;
}

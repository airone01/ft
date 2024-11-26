import {join} from 'node:path';
import {readdir} from 'node:fs/promises';
import {
  type ChatInputCommandInteraction, type Client, InteractionContextType, Routes, SlashCommandBuilder,
} from 'discord.js';
import {rest, zCommandFile, type ClientAndCommands} from '../registrar.js';
import {buildDefaultEmbed} from '../embed.js';
import {logger} from '../logger.js';
import {env} from '../env.js';

export const metadata = new SlashCommandBuilder()
  .setName('reload')
  .setDescription('Reload a command. Only for Quack adminds.')
  .setContexts([InteractionContextType.BotDM, InteractionContextType.Guild, InteractionContextType.PrivateChannel])
  .addStringOption(option =>
    option.setName('command')
      .setDescription('The command to reload.')
      .setRequired(true))
  .setDefaultMemberPermissions(0); // Set command as only for dev

export async function handler(interaction: ChatInputCommandInteraction, client: Client) {
  await interaction.deferReply();

  const embed = buildDefaultEmbed(metadata, interaction);

  const commandName = interaction.options.getString('command', true).toLowerCase();
  const command = (interaction.client as ClientAndCommands).commands.get(commandName);

  if (interaction.user.id !== '299987270159695874') {
    embed.setDescription('Sry, you\'re not an admin');
    await interaction.editReply({embeds: [embed]});
    return;
  }

  if (!command) {
    embed.setDescription(`There is no command with name \`${commandName}\`!`);
    await interaction.editReply({embeds: [embed]});
    return;
  }

  logger.pending(`Received request to reload '${command.metadata.name}' from '${interaction.user.tag}'`);

  const commandPath = await (async () => {
    const commandsDirectory = join(import.meta.dirname);
    const files = await readdir(commandsDirectory);
    const match = files.find(file => file.endsWith(`${commandName}.ts`));
    if (!match) {
      throw new Error(`Could not find command file for ${commandName}`);
    }

    return join(commandsDirectory, match);
  })();

  // eslint-disable-next-line unicorn/prefer-module, @typescript-eslint/no-dynamic-delete
  delete require.cache[require.resolve(`./${command.metadata.name}.ts`)];
  const file: unknown = await import(commandPath);
  const {success, data: commandData, error} = zCommandFile.safeParse(file);

  if (!success) {
    logger.error(`Error parsing command file: ${error.toString()}`);
    return;
  }

  (interaction.client as ClientAndCommands).commands.set(commandData.metadata.name, commandData);
  logger.complete(`Reloaded command '${command.metadata.name}'`);
  embed.setDescription('Done.');
  await interaction.editReply({embeds: [embed]});
}

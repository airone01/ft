import {type ChatInputCommandInteraction, SlashCommandBuilder} from 'discord.js';

export const metadata = new SlashCommandBuilder()
  .setName('hello')
  .setDescription('Say hello to the world');

export async function handler(interaction: ChatInputCommandInteraction) {
  await interaction.reply('Hello, World!');
}

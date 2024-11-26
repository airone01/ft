import {
  type ChatInputCommandInteraction, EmbedBuilder, InteractionContextType, SlashCommandBuilder,
} from 'discord.js';
import {buildDefaultEmbed} from '../embed.js';

export const metadata = new SlashCommandBuilder()
  .setName('duck')
  .setDescription('Display a random duck image')
  .setContexts([InteractionContextType.BotDM, InteractionContextType.Guild, InteractionContextType.PrivateChannel]);

export async function handler(interaction: ChatInputCommandInteraction) {
  await interaction.deferReply();

  const embed = buildDefaultEmbed(metadata, interaction);

  try {
    embed
      .setTitle('Here is a random duck just for you!')
      .setImage(`https://random-d.uk/api/${Math.floor(Math.random() * 289) + 1}.jpg`);
    await interaction.editReply({embeds: [embed]});
  } catch (error) {
    console.error('Error sending quote image:', error);
    embed.setDescription('Sorry, there was an error sending the quote image.');
    await interaction.editReply({embeds: [embed]});
  }
}

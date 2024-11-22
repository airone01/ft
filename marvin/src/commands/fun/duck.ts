import {
  AttachmentBuilder, type ChatInputCommandInteraction, EmbedBuilder, InteractionContextType, SlashCommandBuilder,
} from 'discord.js';

export const metadata = new SlashCommandBuilder()
  .setName('duck')
  .setDescription('Display a random duck image')
  .setContexts([InteractionContextType.BotDM, InteractionContextType.Guild, InteractionContextType.PrivateChannel]);

export async function handler(interaction: ChatInputCommandInteraction) {
  await interaction.deferReply();

  const response = await fetch('https://random-d.uk/api/v2/random');
  const {url} = await response.json() as unknown as {message: string; url: string};

  try {
    const exampleEmbed = new EmbedBuilder()
      .setTitle('Here is a random duck image')
      .setImage(url)
      .setFooter({
        text: interaction.user.globalName ?? '',
        // eslint-disable-next-line @typescript-eslint/naming-convention
        iconURL: interaction.user.avatarURL() ?? '',
      })
      .setColor('#000000');

    await interaction.editReply({
      embeds: [exampleEmbed],
    });
  } catch (error) {
    console.error('Error sending quote image:', error);
    await interaction.editReply('Sorry, there was an error sending the quote image.');
  }
}

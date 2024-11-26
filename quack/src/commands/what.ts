import {
  type ChatInputCommandInteraction,
  InteractionContextType,
  SlashCommandBuilder,
  AttachmentBuilder,
} from 'discord.js';
import {buildDefaultEmbed} from '../embed.js';
import {logger} from '../logger.js';
import {memeTextBelow} from '../image-processor.js';

export const metadata = new SlashCommandBuilder()
  .setName('what')
  .setDescription('Generates a "What? How?" meme')
  .setContexts([InteractionContextType.BotDM, InteractionContextType.Guild, InteractionContextType.PrivateChannel])
  .addAttachmentOption(option => option
    .setName('image')
    .setDescription('Image to edit')
    .setRequired(true))
  .addStringOption(option => option
    .setName('text')
    .setDescription('Text to display'));

export async function handler(interaction: ChatInputCommandInteraction) {
  const embed = buildDefaultEmbed(metadata, interaction);
  const attachment = interaction.options.getAttachment('image');
  const text = interaction.options.getString('text') ?? 'What?';

  if (!attachment) {
    embed.setDescription('Please provide an image.');
    await interaction.editReply({embeds: [embed]});
    return;
  }

  if (!attachment.contentType?.startsWith('image/')) {
    embed.setDescription('The attachment must be an image.');
    await interaction.editReply({embeds: [embed]});
    return;
  }

  await interaction.deferReply();

  try {
    // Fetch the image
    const response = await fetch(attachment.url);
    const imageBuffer = Buffer.from(await response.arrayBuffer());

    // Process image using WebAssembly module
    const processedImageBuffer = await memeTextBelow(imageBuffer, {
      text,
      backgroundColor: 'black',
    });

    // Create attachment
    const processedAttachment = new AttachmentBuilder(Buffer.from(processedImageBuffer), {
      name: `edited-${attachment.name}`,
      description: `'What?' applied to ${attachment.name}`,
    });

    // Send the response
    embed
      .setTitle(null)
      .setDescription(null)
      .setImage(`attachment://edited-${attachment.name}`);

    await interaction.editReply({
      embeds: [embed],
      files: [processedAttachment],
    });
  } catch (error) {
    logger.error('Error processing image:', error);
    embed.setDescription('Sorry, there was an error processing the image.');
    await interaction.editReply({embeds: [embed]});
  }
}

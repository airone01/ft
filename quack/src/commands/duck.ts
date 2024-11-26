import {
  ActionRowBuilder,
  ButtonBuilder,
  type ButtonInteraction,
  ButtonStyle,
  type ChatInputCommandInteraction, type EmbedBuilder, InteractionContextType, SlashCommandBuilder,
} from 'discord.js';
import {buildDefaultEmbed} from '../embed.js';

export const metadata = new SlashCommandBuilder()
  .setName('duck')
  .setDescription('Display a random duck image')
  .setContexts([InteractionContextType.BotDM, InteractionContextType.Guild, InteractionContextType.PrivateChannel]);

export async function handler(interaction: ChatInputCommandInteraction) {
  await interaction.deferReply();

  const embed = buildDefaultEmbed(metadata, interaction);
  await getRandomDuckEmbed(embed);

  const next = new ButtonBuilder()
    .setCustomId('next')
    .setLabel('Another one!')
    .setEmoji('🦆')
    .setStyle(ButtonStyle.Primary);
  const row = new ActionRowBuilder<ButtonBuilder>()
    .addComponents(next);
  const response = await interaction.editReply({embeds: [embed], components: [row]});
  try {
    const buttonInteraction = await response.awaitMessageComponent({filter: (i => i.user.id === interaction.user.id), time: 60_000}) as ButtonInteraction;
    await getRandomDuckEmbed(embed);
    await recurseInteraction(embed, buttonInteraction);
  } catch {
    // Remove components
    await interaction.editReply({components: []});
  }
}

async function recurseInteraction(embed: EmbedBuilder, interaction: ButtonInteraction) {
  const response = await interaction.update({embeds: [embed]});

  try {
    const buttonInteraction = await response.awaitMessageComponent({filter: (i => i.user.id === interaction.user.id), time: 60_000}) as ButtonInteraction;
    await getRandomDuckEmbed(embed);
    await recurseInteraction(embed, buttonInteraction);
  } catch {
    // Remove components
    await interaction.editReply({components: []});
  }
}

async function getRandomDuckEmbed(embed: EmbedBuilder): Promise<void> {
  embed
    .setTitle('Here is a random duck just for you!')
    .setImage(`https://random-d.uk/api/${Math.floor(Math.random() * 289) + 1}.jpg`);
}

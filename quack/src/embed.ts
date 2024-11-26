import {
  type ChatInputCommandInteraction,
  EmbedBuilder, type SlashCommandBuilder, type SlashCommandOptionsOnlyBuilder,
} from 'discord.js';

type SlashCommand = SlashCommandBuilder | SlashCommandOptionsOnlyBuilder;

export function buildDefaultEmbed(metadata: SlashCommand, interaction: ChatInputCommandInteraction): EmbedBuilder {
  return new EmbedBuilder()
    .setFooter({
      text: interaction.user.globalName ?? '',
      // eslint-disable-next-line @typescript-eslint/naming-convention
      iconURL: interaction.user.avatarURL() ?? '',
    })
    .setTitle(metadata.name)
    .setTimestamp()
    .setColor('#000000');
}

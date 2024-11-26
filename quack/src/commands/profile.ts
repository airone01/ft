import {
  type ChatInputCommandInteraction, InteractionContextType, SlashCommandBuilder,
} from 'discord.js';
import {getUserDetails, getUserProjects, getUserLocations} from '../ft-api.js';
import {buildDefaultEmbed} from '../embed.js';
import {logger} from '../logger.js';

export const metadata = new SlashCommandBuilder()
  .setName('profile')
  .setDescription('Display a user\'s profile')
  .setContexts([InteractionContextType.BotDM, InteractionContextType.Guild, InteractionContextType.PrivateChannel])
  .addStringOption(option => option
    .setName('login')
    .setDescription('User login to look for')
    .setRequired(true));

export async function handler(interaction: ChatInputCommandInteraction) {
  const login = interaction.options.getString('login');

  const embed = buildDefaultEmbed(metadata, interaction);
  if (!login) {
    embed.setDescription('Please provide a login or mention a user.');
    await interaction.editReply({embeds: [embed]});
    return;
  }

  await interaction.deferReply();

  try {
    const [user, projects, locations] = await Promise.all([
      getUserDetails(login),
      getUserProjects(login),
      getUserLocations(login),
    ]);

    if (!user) {
      embed.setDescription('Unknown error.');
      await interaction.editReply({embeds: [embed]});
      return;
    }

    if (!projects || projects.length === 0) {
      embed.setDescription('No projects found.');
      await interaction.editReply({embeds: [embed]});
      return;
    }

    if (!user) {
      embed.setDescription('User not found.');
      await interaction.editReply({embeds: [embed]});
      return;
    }

    const currentCursus = user.cursus_users.at(-1);
    const currentLevel = currentCursus?.level ?? 0;

    embed
      .setTitle(user.login)
      .setThumbnail(user.image.versions.large)
      .addFields(
        {name: 'Location', value: `${(!locations || locations.length === 0) ? 'Not logged' : `${locations[0].campus_id}`} <:mingcute_map_pin_fill:1310643964545728602>`},
        {name: 'Level', value: `${currentLevel.toFixed(2)}`, inline: true},
        {name: 'Wallet', value: `${user.wallet}₳`, inline: true},
        {name: 'CP', value: `${user.correction_point}`, inline: true},
        {name: 'Name', value: `${user.first_name} ${user.last_name}`, inline: true},
        {name: 'Email', value: user.email, inline: true},
        {name: 'Campus', value: user.campus.map(c => c.name).join(', '), inline: true},
      );

    if (projects.length > 0) {
      const lastProjects = projects
        .filter(p => p.final_mark !== null)
        .slice(-3)
        .map(p => `${p.project.name}: ${p.final_mark}%${p.marked ? '✅' : '❌'}`);

      if (lastProjects.length > 0) {
        embed.addFields({name: 'Last Projects', value: lastProjects.join('\n')});
      }
    }

    if (currentCursus?.skills) {
      const topSkills = currentCursus.skills
        .sort((a, b) => b.level - a.level)
        .slice(0, 3)
        .map(s => `${s.name}: ${s.level.toFixed(2)}`);

      if (topSkills.length > 0) {
        embed.addFields({name: 'Top Skills', value: topSkills.join('\n')});
      }
    }

    await interaction.editReply({embeds: [embed]});
  } catch (error) {
    logger.error('Error fetching profile:', error);
    embed.setDescription('Sorry, there was an error fetching the profile.');
    await interaction.editReply({embeds: [embed]});
  }
}

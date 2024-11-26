import {
  type ChatInputCommandInteraction, InteractionContextType, SlashCommandBuilder,
  time,
  TimestampStyles,
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
        {name: 'Location', value: `<:Location:1310643964545728602> ${(!locations || locations.length === 0 || !locations[0].end_at) ? `${locations[0].host} - ${time(new Date(locations[0].begin_at), TimestampStyles.RelativeTime)}` : 'Not logged'}\n<:Campus:1310905787044073533> ${user.campus.map(c => c.name).join(', ')}`, inline: true},
        {name: 'Stats', value: `<:Level:1310906661682020383> ${currentLevel.toFixed(2)}\n<:Wallet:1310910338857832550> ${user.wallet}\n<:Correction_Points:1310642265257152582> ${user.correction_point}`, inline: true},
        {name: 'Contact', value: `<:Name:1310906917727502376> ${user.first_name} ${user.last_name}\n<:Email:1310907404468224061> ||${user.email}||`, inline: true},
      );

    if (projects && projects.length > 0) {
      const lastProjects = projects
        .filter(p => p.final_mark !== null)
        .filter(p => p.marked_at)
        // @ts-expect-error TS glitches here. It's normal to compare Dates. See https://stackoverflow.com/a/10124053
        .sort((a, b) => new Date(b.marked_at!) - new Date(a.marked_at!))
        .slice(0, 3);

      const lastProjectsName = lastProjects
        .map(p => p.project.name);

      if (lastProjectsName.length > 0) {
        embed.addFields({name: 'Last Projects', value: lastProjectsName.join('\n'), inline: true});

        const lastProjectMarks = lastProjects
          // eslint-disable-next-line unicorn/no-nested-ternary
          .map(p => `${p.status === 'waiting_for_correction' ? ':hourglass_flowing_sand:' : (p.marked && p.status === 'finished') ? (p.final_mark! >= 50 ? ':white_check_mark:' : ':x:') : '???'} ${p.final_mark}%`);
        embed.addFields({name: '\u200B', value: lastProjectMarks.join('\n'), inline: true});
        const lastProjectDates = lastProjects
          .map(p => p.marked_at ? time(new Date(p.marked_at), TimestampStyles.RelativeTime) : ' ');
        embed.addFields({name: '\u200B', value: lastProjectDates.join('\n'), inline: true});
      }
    }

    if (currentCursus?.skills) {
      const topSkills = currentCursus.skills
        .sort((a, b) => b.level - a.level)
        .slice(0, 3);
      const topSkillsName = topSkills
        .map(s => s.name);

      if (topSkillsName.length > 0) {
        embed.addFields({name: 'Top Skills', value: topSkillsName.join('\n'), inline: true});

        const topSkillsLevel = topSkills
          .map(s => s.level.toFixed(2));
        embed.addFields({name: '\u200B', value: topSkillsLevel.join('\n'), inline: true});
      }
    }

    await interaction.editReply({embeds: [embed]});
  } catch (error) {
    logger.error('Error fetching profile:', error);
    embed.setDescription('Sorry, there was an error fetching the profile.');
    await interaction.editReply({embeds: [embed]});
  }
}

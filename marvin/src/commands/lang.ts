import {type ChatInputCommandInteraction, SlashCommandBuilder} from 'discord.js';
import { execute as executeBrainFuck } from "@uniiem/brainfuck";
import { z } from 'zod';

export const metadata = new SlashCommandBuilder()
  .setName('execute')
  .setDescription('Execute code in a specific language')
  .addStringOption(option =>
    option.setName('language')
      .setDescription('The language to execute the code in')
      .setRequired(true)
      .addChoices([
        {
          name: 'BrainFuck',
          value: 'brainfuck',
        },
      ]))
  .addStringOption(option =>
    option.setName('code')
      .setDescription('The code to execute')
      .setRequired(true));

export async function handler(interaction: ChatInputCommandInteraction) {
  interaction.options.getString('code')!;
  // If language is brainfuck and code has characters that are not in the brainfuck language, return an error message
  if (interaction.options.getString('language') === 'brainfuck' && !/^[><+\-\[\].,]*$/.test(interaction.options.getString('code')!)) {
    await interaction.reply('The code contains characters that are not in the BrainFuck language.');
    return;
  }

  const res = await executeBrainFuck(interaction.options.getString('code')!);
  const {success, data: resString} = z.string().safeParse(res);

  if (!success) {
    await interaction.reply('An error occurred while executing the code.');
    return;
  }

  await interaction.reply(resString);
}

import {
  Client, GatewayIntentBits,
} from 'discord.js';
import {bot} from './bot.js';
import {ImageProcessor as _ImageProcessor} from './image.js'; // For linking

const client = new Client({
  intents: [GatewayIntentBits.Guilds, GatewayIntentBits.GuildMessages, GatewayIntentBits.DirectMessages],
});

await bot(client);

import {
  Client, GatewayIntentBits,
} from 'discord.js';
import {bot} from './bot.js';

const client = new Client({
  intents: [GatewayIntentBits.Guilds, GatewayIntentBits.GuildMessages, GatewayIntentBits.DirectMessages],
});

await bot(client);

import {ActivityType, Events, type Client} from 'discord.js';
import {registerCommands, type ClientAndCommands} from './registrar.js';
import {logger} from './logger.js';
import {env} from './env.js';

logger.fav('Thank you for using my bot! Consider helping @airone01\n');

export async function bot(client: Client) {
  await Promise.all([
    registerCommands,
    startBot,
  ].map(async function_ => {
    try {
      await function_(client);
    } catch (error) {
      logger.error(error);
    }
  }));
}

async function startBot(client: Client) {
  client.once(Events.ClientReady, readyClient => {
    logger.complete(`BOT ONLINE!!! Logged in as '${readyClient.user?.tag}'`);

    client.user?.setPresence({status: 'online', activities: [{state: 'Pourfendeur de Moulinette devant l\'éternel', name: 'pool 🏊‍♂️', type: ActivityType.Playing}]});
  });

  // Command handler
  client.on(Events.InteractionCreate, async interaction => {
    if (!interaction.isCommand()) {
      return;
    }

    const command = (client as ClientAndCommands).commands.get(interaction.commandName.toLowerCase());

    if (!command) {
      logger.warn(`No command matching ${interaction.commandName} was found.`);
      return;
    }

    try {
      await command.handler(interaction);
    } catch (error) {
      console.error(error);
      await (interaction.replied || interaction.deferred ? interaction.followUp({content: 'There was an error while executing this command!', ephemeral: true}) : interaction.reply({content: 'There was an error while executing this command!', ephemeral: true}));
    }
  });

  await client.login(env.DISCORD_BOT_TOKEN);
}

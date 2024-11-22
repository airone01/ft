import {ActivityType, Events, type Client} from 'discord.js';
import {registerCommands} from './registrar.js';
import {logger} from './logger.js';
import {env} from './env.js';

export async function bot(client: Client) {
  const commands = await registerCommands(client);

  client.once(Events.ClientReady, readyClient => {
    logger.success(`BOT ONLINE!!! Logged in as ${readyClient.user?.tag}`);

    client.user?.setPresence({status: 'online', activities: [{state: 'Pourfendeur de Moulinette devant l\'éternel', name: 'pool 🏊‍♂️', type: ActivityType.Playing}]});
  });

  // Command handler
  client.on(Events.InteractionCreate, async interaction => {
    if (!interaction.isCommand()) {
      return;
    }

    const command = commands.get(interaction.commandName);

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

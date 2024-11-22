import {sqliteTable, text, integer} from 'drizzle-orm/sqlite-core';

export const discordUsers = sqliteTable('discordUsers', {
  id: integer('id').primaryKey().notNull(),
  username: text('username').notNull(),
});

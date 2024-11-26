import {sqliteTable, text, integer} from 'drizzle-orm/sqlite-core';

export const discordUsers = sqliteTable('discordUsers', {
  id: integer('id').primaryKey().notNull(),
  username: text('username').notNull(),
  intraId: integer('intraId'),
});

export const intraUsers = sqliteTable('intraUsers', {
  id: integer('id').primaryKey().notNull(),
  login: text('login').notNull(),
  discordId: integer('discordId'),
});

import {migrate} from 'drizzle-orm/bun-sqlite/migrator';
import {database} from '../src/db.js';

migrate(database, {migrationsFolder: './drizzle'});

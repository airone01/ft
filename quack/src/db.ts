import {join} from 'node:path';
import {mkdir} from 'node:fs/promises';
import {drizzle} from 'drizzle-orm/bun-sqlite';
import {Database} from 'bun:sqlite';
import envPaths from 'env-paths';

const paths = envPaths('marvin');
await mkdir(paths.data, {recursive: true});
const sqlite = new Database(join(paths.data, 'db.sqlite'));

export const database = drizzle(sqlite);

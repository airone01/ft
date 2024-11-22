/* eslint-disable @typescript-eslint/naming-convention */
import {join} from 'node:path';
import {env as processEnv} from 'node:process';
import dotenv from 'dotenv';
import {z} from 'zod';

// Load environment variables from .env file and populate process.env
dotenv.config({path: join(import.meta.dirname, '..', '.env')});

const zEnv = z.object({
  NODE_ENV: z.string().default('development'),
  // Discord
  DISCORD_APP_ID: z.string().min(1),
  DISCORD_PUBLIC_KEY: z.string().min(1),
  DISCORD_BOT_TOKEN: z.string().min(1),
  DISCORD_CLIENT_ID: z.string().min(1),
  // API
  PORT: z.string().default('8020'),
});
export const env = zEnv.parse(processEnv);

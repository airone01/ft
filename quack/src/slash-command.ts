/* eslint-disable @typescript-eslint/naming-convention */
import {z} from 'zod';

// Create the Locale enum schema
const zLocaleEnum = z.enum([
  'id', // Indonesian
  'en-US', // English US
  'en-GB', // English GB
  'bg', // Bulgarian
  'zh-CN', // Chinese CN
  'zh-TW', // Chinese TW
  'hr', // Croatian
  'cs', // Czech
  'da', // Danish
  'nl', // Dutch
  'fi', // Finnish
  'fr', // French
  'de', // German
  'el', // Greek
  'hi', // Hindi
  'hu', // Hungarian
  'it', // Italian
  'ja', // Japanese
  'ko', // Korean
  'lt', // Lithuanian
  'no', // Norwegian
  'pl', // Polish
  'pt-BR', // Portuguese BR
  'ro', // Romanian
  'ru', // Russian
  'es-ES', // Spanish ES
  'es-419', // Spanish LATAM
  'sv-SE', // Swedish
  'th', // Thai
  'tr', // Turkish
  'uk', // Ukrainian
  'vi', // Vietnamese
]);

// Create the LocalizationMap schema
const zLocalizationMap = z.record(zLocaleEnum, z.string().nullable());

// Placeholder for APIApplicationCommandOption until we get its definition
const zAapiiAppCommandOption = z.object({}).passthrough();

// Schema for ToAPIApplicationCommandOptions interface
const zToApiAppCommandOptions = z.object({
  toJSON: z.function()
    .returns(zAapiiAppCommandOption),
});

export const zSlashCommandBuilder = z.object({
  name: z.string(),
  name_localizations: zLocalizationMap.optional(),
  description: z.string(),
  description_localizations: zLocalizationMap.optional(),
  options: z.array(z.unknown()), // This should be ToAPIApplicationCommandOptionsSchema but we need more type info
  contexts: z.array(z.unknown()).optional(), // Need InteractionContextType definition
  default_permission: z.boolean().optional(),
  default_member_permissions: z.unknown().nullable().optional(), // Need Permissions definition
  dm_permission: z.boolean().optional(),
  integration_types: z.array(z.unknown()).optional(), // Need ApplicationIntegrationType definition
  nsfw: z.boolean().optional(),
});

/* eslint-disable @typescript-eslint/naming-convention */
import {defineNuxtConfig} from 'nuxt/config';

// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  compatibilityDate: '2024-11-01',
  postcss: {
    plugins: {
      tailwindcss: {},
      autoprefixer: {},
    },
  },
  routeRules: {
    '/discord': {redirect: 'https://discord.com/oauth2/authorize?client_id=1292146624994480321'},
    '/github': {redirect: 'https://github.com/airone01/ft/tree/main/quack'},
  },
  css: ['~/assets/css/main.css'],
  devtools: {enabled: true},
});

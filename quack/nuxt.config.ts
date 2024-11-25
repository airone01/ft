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
    // eslint-disable-next-line @typescript-eslint/naming-convention
    '/discord': {redirect: 'https://discord.com/oauth2/authorize?client_id=1292146624994480321'},
  },
  css: ['~/assets/css/main.css'],
  devtools: {enabled: true},
});

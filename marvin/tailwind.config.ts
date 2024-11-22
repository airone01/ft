import daisyUi from 'daisyui';
import {type Config} from 'tailwindcss';

const config: Config = {
  content: [
    './components/**/*.{js,vue,ts}',
    './layouts/**/*.vue',
    './pages/**/*.vue',
    './plugins/**/*.{js,ts}',
    './app.vue',
    './error.vue',
  ],
  theme: {
    extend: {},
  },
  plugins: [daisyUi],
  daisyui: {
    themeRoot: ':root', // The element that receives theme color CSS variables
    themes: ['sunset'],
    // DarkTheme: 'sunset', // Name of one of the included themes for dark mode
    base: true, // Applies background color and foreground color for root element by default
    styled: true, // Include daisyUI colors and design decisions for all components
    utils: true, // Adds responsive and modifier utility classes
    prefix: '', // Prefix for daisyUI classnames (components, modifiers and responsive class names. Not colors)
    logs: true, // Shows info about daisyUI version and used config in the console when building your CSS
  },
};

export default config;

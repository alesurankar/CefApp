import 'vuetify/styles'
import './assets/globals.css'

import '@mdi/font/css/materialdesignicons.css'
import '@fontsource/roboto/index.css'

import { createApp } from 'vue'
import App from './App.vue'
import { createVuetify } from 'vuetify'
import { md2 } from 'vuetify/blueprints'
import router from './router/router'
import ContactUs from "./components/ContactUs.vue";
import ButtonCounter from "./components/ButtonCounter.vue";

const vuetify = createVuetify({
    blueprint: md2,
    theme: {
        defaultTheme: 'dark'
    }
})

const app = createApp(App)
app
    .use(vuetify)
    .use(router) 
    .component("ContactUs", ContactUs)
    .component("ButtonCounter", ButtonCounter)
    .mount('#app')

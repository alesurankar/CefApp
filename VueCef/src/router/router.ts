// src/router.ts or router/index.ts
import { createRouter, createWebHistory } from 'vue-router'

import Home from '../views/Home.vue'
import Chart from '../views/Chart.vue'
import Dice_roll_simulator from '../views/dice_roll_simulator.vue'
import learnVue from '../views/learnVue.vue'
import Test_VUE_2 from '../views/Test_VUE_2.vue'
import test2 from '../views/test2.vue'
import loginView from '../views/LoginView.vue'

const routes = [
  { path: '/', component: Home },
  { path: '/chart', component: Chart },
  { path: '/drs', component: Dice_roll_simulator },
  { path: '/learnVue', component: learnVue },
  { path: '/Test_VUE_2', component: Test_VUE_2 },
  { path: '/test2', component: test2 },
  { path: '/login', component: loginView}
]

const router = createRouter({
  history: createWebHistory(),
  routes,
})

export default router

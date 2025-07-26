<script setup>
  import { ref, watch } from 'vue'

  const items = [
    { title: 'Home', value: '/', icon: 'mdi-home' },
    { title: 'Chart', value: 'chart', icon: 'mdi-chart-bar' },
    {
      title: 'Dice_roll_simulator',
      value: 'drs',
    },
    {
      title: 'learnVue',
      value: 'learnVue',
    },
    {
      title: 'Test_VUE_2',
      value: 'Test_VUE_2',
    },
    {
      title: 'test2',
      value: 'test2',
    },
  ]

  const drawer = ref(false)
  const group = ref(null)

  watch(group, () => {
    drawer.value = false
  })
</script>


<template>
  <v-app>
    <v-app-bar flat height="32" class="app-title-bar" color="background">
      <v-app-bar-nav-icon variant="text" @click.stop="drawer = !drawer"></v-app-bar-nav-icon>
      <v-toolbar-title>My files</v-toolbar-title>
      <template v-if="$vuetify.display.mdAndUp">
        <v-btn icon class="rounded-0" style="-webkit-app-region: no-drag;">
          <v-icon size="18">mdi-window-minimize</v-icon>
        </v-btn>
        <v-btn icon class="rounded-0" style="-webkit-app-region: no-drag;">
          <v-icon size="18">mdi-window-maximize</v-icon>
        </v-btn>
        <v-btn icon class="rounded-0" style="-webkit-app-region: no-drag;">
          <v-icon size="18">mdi-close</v-icon>
        </v-btn>
      </template>
    </v-app-bar>
    <v-navigation-drawer
        v-model="drawer"
        :location="$vuetify.display.mobile ? 'left' : undefined"
        temporary
      ><v-list nav>
        <v-list-item
          v-for="item in items"
          :key="item.value"
          :to="`/${item.value}`"
          link
          @click="drawer = false"
          exact
          >
          <v-list-item-icon v-if="item.icon">
          <v-icon>{{ item.icon }}</v-icon>
          </v-list-item-icon>
          <v-list-item-title>{{ item.title }}</v-list-item-title>
        </v-list-item>
      </v-list>
    </v-navigation-drawer>
    <v-main style="height: 500px;">
      <v-card-text>
        <v-fade-transition>
          <router-view />
        </v-fade-transition>
      </v-card-text>
    </v-main>
    
    <v-footer app>
      <span>&copy; 2025</span>
    </v-footer>
  </v-app>
</template>
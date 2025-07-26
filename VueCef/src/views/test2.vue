<template>
    <v-toolbar :elevation="8" class="text-white" image="https://cdn.vuetifyjs.com/images/backgrounds/vbanner.jpg">
      <v-btn icon="mdi-menu"></v-btn>

      <v-toolbar-title text="Vuetify"></v-toolbar-title>

      <v-menu>
      <template v-slot:activator="{ props }">
        <v-btn
          color="primary"
          v-bind="props"
          ><v-btn icon>
            <v-badge content="6" color="red-darken-2">
              <v-icon icon="mdi-bell" color="yellow-darken-2" size="small"></v-icon>
            </v-badge>
          </v-btn>
        </v-btn>
      </template>
      <v-list>
        <v-list-item
          v-for="(item, index) in notifications"
          :key="index"
          :value="index"
        >
          <v-list-item-title>{{ item.title }}</v-list-item-title>
        </v-list-item>
      </v-list>
    </v-menu>

      
      <v-btn to="/login" icon="mdi-login" color="green-darken-2" size="small"></v-btn>
    </v-toolbar>
    <v-main>
      <v-carousel hide-delimiters>
    <v-carousel-item
      v-for="(item,i) in items"
      :key="i"
      :src="item.src"
      cover
    ></v-carousel-item>
  </v-carousel>  
    </v-main>
</template>

<script setup lang="ts">
    const items = [
    {
      src: 'https://cdn.vuetifyjs.com/images/carousel/squirrel.jpg',
    },
    {
      src: 'https://cdn.vuetifyjs.com/images/carousel/sky.jpg',
    },
    {
      src: 'https://cdn.vuetifyjs.com/images/carousel/bird.jpg',
    },
    {
      src: 'https://cdn.vuetifyjs.com/images/carousel/planet.jpg',
    },
  ]

  const notifications = [
        { title: 'Click Me' },
        { title: 'Click Me' },
        { title: 'Click Me' },
        { title: 'Click Me 2' },
  ]

</script>
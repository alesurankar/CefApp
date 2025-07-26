<template>
  <v-container>
    <v-row justify="center">
      <v-col cols="12" md="6">
        <v-card>
          <v-card-text>{{ message }}</v-card-text>
          <ContactUs 
            name="Ales"
            :phone="+123456789" 
            ownername="enmalibolek"
          ></ContactUs>
          <ContactUs 
            name="Bolek"
            :phone="+987654321" 
            ownername="šupakJedni"
                      ></ContactUs>
          <ButtonCounter></ButtonCounter>
          <v-btn @click="increment">Clicked {{ count }} times</v-btn>
        </v-card>
        <v-card class="my-2">
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script setup lang="ts">
const message="Hello vue";
import { ref } from 'vue'

const count = ref(0)
function increment() 
{
  count.value++;

}
</script>

<style scoped>
</style>
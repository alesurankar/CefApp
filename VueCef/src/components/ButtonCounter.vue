<template>
    <v-btn @click="increment">Clicked {{ count }} times</v-btn>
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
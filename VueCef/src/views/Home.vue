<template src="./Home.template.html"></template>

<script setup lang="ts">
import { ref } from 'vue'

const count = ref(0)
const increment = () => count.value++
</script>

<style scoped src="./Home.style.css"></style>
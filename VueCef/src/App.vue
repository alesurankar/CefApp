<script setup lang="ts">
import { ref, computed } from 'vue'
// api definition
interface MyApi {
  doVersion(
    text: string,
    accept: (result: boolean) => void,
    reject: (msg: string) => void,
  ): void;
}
const myApi = window as unknown as MyApi;
function doVersion(text: string): Promise<boolean> {
  return new Promise<boolean>((accept, reject) => myApi.doVersion(text, accept, reject))
}
// reactive data
const answer = ref<string|null>(null)
const inProgress = ref(false)
// computed data
const resultText = computed(() => {
  if(inProgress.value) {
    return "Test in progress...";
  }
  else if(answer.value === null) {
    return "NO DATA";
  }
  else {
    return `You have: ${answer.value}`;
  }
})
// functions
function doit() {
  inProgress.value = true;
  answer.value = null
  doVersion("Path 1").then((yes) => {
    if(yes) {
      return doVersion("Path 1.1").then((yes) => {
        if(yes) {
          answer.value = "1.1";
        }
        else {
          answer.value = "1";
        }
      })
    }
    else {
      return doVersion("Path 2.1").then((yes) => {
        if(yes) {
          answer.value = "2.1";
        }
        else {
          answer.value = "2";
        }
      })
    }
  })
  .finally(() => inProgress.value = false)
}
</script>

<template>
  <v-app>
    <v-main>
      <v-container width="1024">
        <h2 class="mb-2 ml-4">Take the Test</h2>
        <v-card title="Animal" :text="resultText"></v-card>
        <div class="d-flex justify-center mt-3">
          <v-btn color="purple" @click="doit" size="x-large">JUST DO IT</v-btn>
        </div>
      </v-container>
    </v-main>
  </v-app>
</template>

<style scoped>
</style>
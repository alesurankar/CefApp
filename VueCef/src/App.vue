<script setup lang="ts">
import { ref, computed } from 'vue'

interface MyApi {
  doVersion(
    text: string,
    accept: (result: boolean) => void,
    reject: (msg: string) => void,
  ): void;
}

const myApi = window as unknown as MyApi;
// reactive data
const powerLevel = ref<number|null>(null)
const inProgress = ref(false)
// computed data
const powerLevelNorm = computed(() => powerLevel.value ?? 0)
// functions
function doit() {
  inProgress.value = true;
  powerLevel.value = 0


  myApi.doVersion("Question1",
    btn => { 
      powerLevel.value = btn ? <number>powerLevel.value + 1 : <number>powerLevel.value
      myApi.doVersion("Question2",
        btn => { 
          powerLevel.value = btn ? <number>powerLevel.value + 1 : <number>powerLevel.value
          myApi.doVersion("Question3",
            btn => { 
              powerLevel.value = btn ? <number>powerLevel.value + 1 : <number>powerLevel.value
              myApi.doVersion("Question4",
                btn => { 
                  powerLevel.value = btn ? <number>powerLevel.value + 1 : <number>powerLevel.value
                  myApi.doVersion("Question5",
                    btn => { 
                      powerLevel.value = btn ? <number>powerLevel.value + 1 : <number>powerLevel.value
                      inProgress.value = false
                    },
                    msg => { inProgress.value = false; powerLevel.value = null },
                  )
                },
                msg => { inProgress.value = false; powerLevel.value = null },
              )
            },
            msg => { inProgress.value = false; powerLevel.value = null },
          )
        },
        msg => { inProgress.value = false; powerLevel.value = null },
      )
    },
    msg => { inProgress.value = false; powerLevel.value = null },
  )
}
</script>



<template>
  <v-app>
    <v-main>
      <v-container width="1024">
        <h2 class="mb-2 ml-4">Take the Test</h2>
        <v-card title="Power Level" class="mb-3 pa-3 pt-5">
          <div class="ma-4">
            <v-progress-linear
              v-model="powerLevelNorm"
              color="blue-darken-3"
              :indeterminate="powerLevel === null"
              :stream="inProgress"
              rounded
              max="5"
              height="20"
            ></v-progress-linear>
          </div>
        </v-card>
        <div class="d-flex justify-center mt-3">
          <v-btn color="purple" @click="doit" size="x-large">JUST DO IT</v-btn>
        </div>
      </v-container>
    </v-main>
  </v-app>
</template>

<style scoped>
</style>
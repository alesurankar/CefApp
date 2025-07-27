<script setup lang="ts">
import { ref, computed } from 'vue'
interface Item 
{
  name: string;
  price: number;
}
const inventory: Item[] =
[
  { name: 'pivo', price: 1.99},
  { name: 'jabolke', price: 2.45},
  { name: 'hruške', price: 2.38},
  { name: 'banane', price: 2.29},
  { name: 'zobna pasta', price: 1.29},
  { name: 'pica', price: 3.29},
  { name: 'meso', price: 4.26},
  { name: 'lopata', price: 9.99},
  { name: 'motika', price: 12.99},
  { name: 'pivo-V2', price: 2.99},
  { name: 'jabolke-V2', price: 3.45},
  { name: 'hruške-V2', price: 3.38},
  { name: 'banane-V2', price: 3.29},
  { name: 'zobna pasta-V2', price: 2.29},
  { name: 'pica-V2', price: 4.29},
  { name: 'meso-V2', price: 5.26},
  { name: 'lopata-V2', price: 10.99},
  { name: 'motika-V2', price: 13.99},
  { name: 'lopata-V3', price: 11.99},
  { name: 'motika-V3', price: 14.99},
]
interface Entry 
{
  item: Item;
  quantity: number;
}
const entries = ref<Entry[]>([])
function addItem()
{
  entries.value.push({item: inventory[0], quantity: 1})
}
function removeItem(i: number)
{
  entries.value.splice(i, 1)
}
const grandTotal = computed(() =>
  entries.value.reduce((sum, entry) => sum + entry.item.price * entry.quantity, 0)
)
const mb = ref('null')
function doit()
{
  interface MyApi
  {
    doVersion(
      text: string,
      accept: (result: boolean) => void,
      reject: (msg: string) => void,
    ): void;
  }
  const myApi = window as unknown as MyApi;
    myApi.doVersion("ayyyyy yo",
      (btn) => {mb.value = btn ? 'YES' : 'NO'},
      (msg) => mb.value = msg
  )
}
</script>

<template>
  <v-app>
    <v-main>
      <v-container width="1024">
        <h2 class="mb-2 ml-4">My Shooping Cart</h2>
        <v-card class="mb-3 pa-3 pt-5">
          <v-row v-for="(entry, i) in entries" align="center">
            <v-col cols="1">
              <v-btn icon="mdi-trash-can" size="small" variant="text"
                color="red" @click="removeItem(i)"
              ></v-btn>
            </v-col>
            <v-col cols="7">
              <v-autocomplete
                color="primary"
                variant="outlined"
                density="compact"
                hide-details
                :items="inventory"
                item-title="name"
                v-model="entry.item"
                return-object
              ></v-autocomplete>
            </v-col>
            <v-col cols="2">
              <v-number-input
                color="primary"
                variant="outlined"
                density="compact"
                hide-details
                control-variant="stacked"
                v-model="entry.quantity"
                :min="1"
              ></v-number-input>
            </v-col>
            <v-col cols="2" class="d-flex justify-end">
              <p class="price">${{ (entry.item.price * entry.quantity).toFixed(2) }}</p>
            </v-col>
          </v-row>
          <v-row align="center">
            <v-col cols="10" class="d-flex justify-end">
              <p class="price" style="padding-right: 0;">Grand Total:</p>
            </v-col>
            <v-col cols="2" class="d-flex justify-end">
              <p class="price">${{ grandTotal.toFixed(2) }}</p>
            </v-col>
          </v-row>
        </v-card>
        <div class="d-flex justify-end">
          <v-btn icon="mdi-plus" color="purple" @click="addItem"></v-btn>
        </div>
        <div class="d-flex justify-end">
          <v-btn color="green" @click="doit">AYY</v-btn>
          <p class="price">{{ mb }}</p>
        </div>
      </v-container>
    </v-main>
  </v-app>
</template>

<style scoped>
.price
{
  font-size: 20px;
  font-weight: bold;
  padding-right: 20px;
}
</style>
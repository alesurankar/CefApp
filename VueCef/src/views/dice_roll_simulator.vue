<template>
  <body>
    <h1>Dice Roll Simulator</h1>
    <div class="dice" id="dice">
      <v-icon>mdi-dice-1</v-icon>
    </div>
    <v-btn class="button" id="roll">Roll Dice</v-btn>
    <ul id="roll-history">
      <li>Roll 1: <span><v-icon>mdi-dice-1</v-icon></span></li>
      <li>Roll 1: <span><v-icon>mdi-dice-4</v-icon></span></li>
    </ul>
  </body>

  <v-app>
  <v-main>
    <v-container width="1024">
      <h2 class="mb-2 ml-4">My Shooping Cart</h2>
      <v-card class="mb-3 pa-3 pt-5">
          <v-col cols="1">
            <v-btn icon="mdi-trash-can" size="small" variant="text"
            ></v-btn>
          </v-col>
          <v-col cols="7">
            <v-autocomplete
              color="primary"
              variant="outlined"
              density="compact"
              hide-details
              item-title="name"
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
              :min="1"
            ></v-number-input>
          </v-col>
          <v-col cols="2" class="d-flex justify-end">
          </v-col>
        <v-row align="center">
          <v-col cols="10" class="d-flex justify-end">
            <p class="price" style="padding-right: 0;">Grand Total:</p>
          </v-col>
          <v-col cols="2" class="d-flex justify-end">
            <p class="price">${{}}</p>
          </v-col>
        </v-row>
      </v-card>
      <div class="d-flex justify-end">
        <v-btn icon="mdi-plus" color="purple" @click=""></v-btn>
      </div>
      <div class="d-flex justify-end">
        <v-btn color="green" @click="">AYY</v-btn>
      </div>
    </v-container>
  </v-main>
</v-app>
</template>

<script setup lang="ts">
</script>

<style scoped>
body
{
  font-family: sans-serif;
  text-align: center;
  margin: 0;

}
h1
{
  font-size: 3rem;
  margin-top: 2rem;
}
.dice
{
  font-size: 4rem;
  margin: 5px;
}
.button
{
  margin-bottom: 6px;
}
li
{
  font-size: 1.5rem;
  padding: .5rem;
  margin: .5rem;
  border-radius: .5rem;

}
</style>
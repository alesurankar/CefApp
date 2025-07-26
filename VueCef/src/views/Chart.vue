<template>
  <v-container fluid class="bg-red">
    <h1>Chart</h1>
    <v-container class="bg-indigo-lighten-2 text-teal-darken-4  text-uppercase pl-12 ml-4 elevation-10 rounded-circle" >Colored container</v-container>
    <v-row></v-row>
  </v-container>
  <v-container class="bg-blue elevation-16">
    <v-row class="ma-4">
      <v-col cols="6">Column 1</v-col>
      <v-col cols="6">Column 2</v-col>
    </v-row>
    <v-row class="text-deep-purple">none</v-row>
    <v-row class="bg-light-green-darken-2" justify="center">justify-center</v-row>
    <v-row class="text-orange-lighten-3" align="center" >align-center</v-row>
    <v-row>
      <v-col>vrsta1</v-col>
      <v-col>vrsta1</v-col>
      <v-row>
        <v-col>vrsta3</v-col>
        <v-col>vrsta4</v-col>
      </v-row>
      <v-col>vrsta5</v-col>
      <v-col>vrsta6</v-col>
    </v-row>
  </v-container>
</template>

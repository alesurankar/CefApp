<template>
    <v-container class="bg-info rounded p-2 m-2">
        <v-card-text>Name: {{ name }}</v-card-text>
        <v-card-text>Email: {{ email }}</v-card-text>
        <v-card-text>Phone: {{ phone }}</v-card-text>
        <v-card-text class="float-end small" v-if="ownername!=''">
            This contactInfo belongs to {{ ownername }}
        </v-card-text>
    </v-container>
</template>

<script setup lang="ts">
import { ref } from 'vue'
//const email = ref("hello@email.com");
const props = defineProps({
    name: {type: String, required: true }, 
    phone:Number, 
    ownername:String,
    email: {type: String, required: false, default:"-n/a-"}
});
</script>
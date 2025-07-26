<template>
    <v-app>
        <!-- SIDEBAR -->
         <SideBar/>
         
        <v-btn to="/test2" icon="mdi-logout" color="pink-darken-4" size="small"></v-btn>
         <v-main>
            <!-- CARDS -->
             <ImageGallary/>
         </v-main>
    </v-app>
</template>

<script setup lang="ts">
    import SideBar from "../components/SideBar.vue"
    import ImageGallary from "@/components/ImageGallary.vue";
</script>
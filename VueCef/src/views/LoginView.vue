<script setup lang="ts">

    import { ref } from 'vue'
    import { useRouter } from 'vue-router'

    const router = useRouter()
    const form = ref({
        email: '',
        password: '',
        remember: false
    })

    const isLoading = ref(false);

    function submit() {
        isLoading.value = true;

        setTimeout(() => {
            isLoading.value = false;
            //alert(JSON.stringify(form.value));
            router.push('/Test_VUE_2') 
        }, 1600);
    }

</script>

<template>
    <v-toolbar :elevation="8" class="text-white" image="https://cdn.vuetifyjs.com/images/backgrounds/vbanner.jpg">
        <v-toolbar-title text="Login Page"></v-toolbar-title>
        <v-btn to="/test2" icon="mdi-logout" color="pink-darken-4" size="small"></v-btn>
    </v-toolbar>
    <v-container fluid>
        <v-overlay :model-value="isLoading" 
            class="align-center justify-center"
            ><v-progress-circular
                v-if="isLoading"
                indeterminate
                color="white"
            ></v-progress-circular>
        </v-overlay>
        <v-row justify="center">
            <v-col cols="4">
                <v-card class="pa-4 mx-auto">
                    <v-card-title class="text-center">Login Here</v-card-title>
                    <v-card-item>
                        <v-form @submit.prevent="submit">
                            <v-text-field
                                variant="solo"
                                prepend-inner-icon="mdi-email"
                                v-model="form.email"
                                label="Email"
                            ></v-text-field>
                            <v-text-field
                                type="password"
                                variant="solo"
                                prepend-inner-icon="mdi-key"
                                v-model="form.password"
                                label="Password"
                            ></v-text-field>
                            <v-checkbox 
                                v-model="form.remember"
                                label="Remember Me"
                                color="blue"
                                value="true"
                                hide-details
                            ></v-checkbox>
                            <v-btn color="green-darken-2" class="mt-2" type="submit" block>Submit</v-btn>
                        </v-form>
                    </v-card-item>
                    <v-card-actions class="pa-4 mx-auto" width="300">
                        <v-btn variant="outlined" to="/register" color="green-darken-2" class="mt-2" type="submit" block>Register</v-btn>
                    </v-card-actions>
                </v-card>
            </v-col>
        </v-row>
    </v-container>
</template>
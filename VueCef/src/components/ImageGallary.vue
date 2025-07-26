<template>
    <v-card class="ma=5 my=2 pa-3">
        <v-row>
            <v-col v-for="n in 200" cols="1">
                <v-card>
                    <v-img 
                        :src="`https://picsum.photos/500/300?image=${n * 5 + 10}`"
                        :lazy-src="`https://picsum.photos/10/6?image=${n * 5 + 10}`"
                        aspect-ratio="1"
                        cover
                        >
                        <template v-slot:placeholder>
                            <v-row
                                    align="center"
                                    class="fill-height ma-0"
                                    justify="center"
                            >
                                <v-progress-circular
                                    color="grey-lighten-5"
                                    indeterminate
                                ></v-progress-circular>
                            </v-row>
                        </template>
                    </v-img>
                </v-card>
            </v-col>
        </v-row>
    </v-card>
</template>
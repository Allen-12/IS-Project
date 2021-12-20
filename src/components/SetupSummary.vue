<template>
    <v-container>
    <v-row no-gutters>
      <v-col
        v-for="n in 3"
        :key="n"
        cols="12"
        sm="4"
      >
        <v-card
          class="pa-2"
          outlined
          tile
        >
          {{ volume }}
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import Localbase from 'localbase'

let db = new Localbase('tank_db')

export default {
    name: "SetupSummary",
    data: () => ({
        volume: 0,
        height: 0,
        diameter: 0,
        surfaceArea: 0,
    }),
    created: () => {
        db.collection('tank_data').get().then(tank_data => {
            console.log(tank_data);
        })
    }

}
</script>

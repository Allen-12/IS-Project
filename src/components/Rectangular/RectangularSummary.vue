<template>
    <v-container fluid>
        <div class="blue-grey lighten-1 text-h5  text-center mb-2">
            <span class="white--text">Tank: Rectangular</span>
        </div>
      <v-row dense> 
        <v-col cols="6">
           <v-card
            color="blue lighten-1"
            dark
          >
            <v-card-title class="text-h5 white--text">
              Volume (L)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold white--text">{{ volume.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
          </v-card>
        </v-col>
        <v-col cols="6">
           <v-card
            color="blue lighten-1"
            dark
          >
            <v-card-title class="text-h5 white--text">
              Length (cm)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold white--text">{{ length.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
          </v-card>
        </v-col>
      </v-row>
      <v-row dense>
        <v-col cols="6">
           <v-card
            color="blue lighten-1"
            dark
            >
            <v-card-title class="text-h5 white--text">
              Width (cm)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold white--text">{{ width.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
          </v-card>
        </v-col>
        <v-col cols="6">
           <v-card
            color="blue lighten-1"
            dark
            >
            <v-card-title class="text-h5 white--text">
              Height (cm)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold white--text">{{ height.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
          </v-card>
        </v-col>
      </v-row>
  </v-container>
</template>
<script>
import Localbase from 'localbase'

let db = new Localbase('tank_db')

export default{
    name: 'RectangularSummary',
    data: () => ({
        volume: 0,
        length: 0,
        width: 0,
        height: 0,
        tankType: ''
    }),
    created: function() {
        db.collection('tank_data').get().then(tank_data => {
            console.log(typeof tank_data[0].volume);
            this.volume = tank_data[0].volume
            this.length = tank_data[0].length
            this.width = tank_data[0].width
            this.height = tank_data[0].height
            this.tankType = tank_data[0].tank_type
            console.log(this.surfaceArea);
        })
    }
}
</script>
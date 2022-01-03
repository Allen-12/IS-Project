<template>
    <v-container fluid>
        <div class="blue darken-1 text-h5  text-center mb-2" >
            <span class="white--text">Tank: Cylindrical</span>
        </div>
      <v-row dense>
        <v-col cols="6">
           <v-card>
            <v-card-title class="text-h5">
              Volume (L)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold">{{ volume.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
          </v-card>
        </v-col>
        <v-col cols="6">
           <v-card>
            <v-card-title class="text-h5">
              Height (cm)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold">{{ height.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
          </v-card>
        </v-col>
      </v-row>
      <v-row dense>
        <v-col cols="6">
           <v-card>
            <v-card-title class="text-h5">
              Diameter (cm)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold">{{ diameter.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
          </v-card>
        </v-col>
        <v-col cols="6">
           <v-card>
            <v-card-title class="text-h5">
              Surface Area (cm&sup2;)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold">{{ surfaceArea.toLocaleString() }}</v-card-subtitle>
          </v-card>
        </v-col>
      </v-row>
  </v-container>
</template>
<script>
import Localbase from 'localbase'

let db = new Localbase('tank_db')

export default{
    name: 'CylindricalSummary',
    data: () => ({
        volume: 0,
        height: 0,
        diameter: 0,
        surfaceArea: 0,
        tankType: ''
    }),
    created: function() {
        db.collection('tank_data').get().then(tank_data => {
            this.volume = tank_data[0].volume
            this.diameter = tank_data[0].diameter
            this.height = tank_data[0].height
            this.surfaceArea = tank_data[0].surfaceArea
            this.tankType = tank_data[0].tank_type
        })
    }
}
</script>

<template>
    <v-container fluid>
        <div class="blue lighten-1 text-h5  text-center mb-2">
            <span class="white--text">Tank: Rectangular</span>
        </div>
      <v-row dense> 
        <v-col cols="6">
           <v-card>
            <v-card-title class="text-h5">
              Volume (L)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold">{{ volume.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
            <!-- <v-card-actions>
              <template>
                <div class="text-center">
                  <v-dialog
                    v-model="dialog"
                    width="500"
                  >
                    <v-tooltip left>
                      <template v-slot:activator="{ on,attrs }">
                        <v-btn 
                          color="warning"
                          v-bind="attrs"
                          v-on="on"
                        >
                          <v-icon>mdi-pencil</v-icon>
                        </v-btn>
                      </template>
                      <span>Edit</span>
                    </v-tooltip>
                  </v-dialog>
                </div>

              </template>
            </v-card-actions> -->
          </v-card>
        </v-col>
        <v-col cols="6">
           <v-card>
            <v-card-title class="text-h5">
              Length (cm)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold">{{ length.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
          </v-card>
        </v-col>
      </v-row>
      <v-row dense>
        <v-col cols="6">
           <v-card>
            <v-card-title class="text-h5">
              Width (cm)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold">{{ width.toLocaleString({maximumFractionDigits:2}) }}</v-card-subtitle>
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
        tankType: '',
        dialog: false
    }),
    created: function() {
        db.collection('tank_data').get().then(tank_data => {
            // console.log(typeof tank_data[0].volume);
            this.volume = tank_data[0].volume
            this.length = tank_data[0].length
            this.width = tank_data[0].width
            this.height = tank_data[0].height
            this.tankType = tank_data[0].tank_type
            // console.log(this.surfaceArea);
        })
    },
    methods:{
      // editValue(value){
      //   switch (value) {
      //     case "volume":
      //       db.collection('users').doc({ tank_type: "rectangular" }).update({
      //         volume: 'William'
      //       })
      //       break;
        
      //     default:
      //       break;
      //   }

      //   // console.log(value);
      // }
    }
}
</script>
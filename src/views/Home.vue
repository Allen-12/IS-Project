<template>
    <v-container fluid>
      <v-row dense>
        <v-col cols="6">
           <v-card>
            <v-card-title class="text-h5">
              Volume (L)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold">{{ availableVolume }}</v-card-subtitle>
          </v-card>
        </v-col>
        <v-col cols="6">
           <v-card>
            <v-card-title class="text-h5">
              Flow Rate (L/min)
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold">{{ flowRate }}</v-card-subtitle>
          </v-card>
        </v-col>
      </v-row>
      <v-row dense>
        <v-col cols="12">
          <v-card>
            <v-card-title class="text-h6">
              Time (in minutes) left for water to be depleted
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold" v-if="timeLeft === Infinity">&#8734;</v-card-subtitle>
            <v-card-subtitle class="text-h6 font-weight-bold" v-else>{{ timeLeft }}</v-card-subtitle>
          </v-card>
        </v-col>
      </v-row>
      <v-row>
        <v-col cols="12">
          <v-card>
            <v-card-title class="text-h6">
              Estimated Date and Time of Depletion
            </v-card-title>

            <v-card-subtitle class="text-h6 font-weight-bold" v-if="timeLeft === Infinity">&#8734;</v-card-subtitle>
            <v-card-subtitle class="text-h6 font-weight-bold" v-else>{{ timeLeft }}</v-card-subtitle>
          </v-card>
        </v-col>
      </v-row>
    </v-container>
</template>

<script>
import Localbase from 'localbase'
import moment from 'moment'

let db = new Localbase('tank_db')

const axios = require('axios')

export default {
  name: 'Home',
  data: () => ({
    tankWaterHeight: 0,
    flowRate: 0,
    surfaceArea: 0,
    height: 0,
    availableVolume: 0,
    timeLeft: 0,
    time: 0,
    responseData: []

  }),
  created: function() {
    db.collection('tank_data').get().then(tank_data => {
      this.height = tank_data[0].height
      this.surfaceArea = tank_data[0].surfaceArea
      // console.log(this.surfaceArea);
    })
  },
  mounted: function(){
    this.getAllAPIData()
    setInterval(this.getMostRecentAPIData,30000)
    
  },
  methods: {
    // Get all API Data at when page is loaded
    async getAllAPIData(){
      try
      {
        const response = await axios.get('https://api.thingspeak.com/channels/1575729/feeds.json?api_key=XGIU5VOHC9Y03Q9O')
        this.responseData = response.data.feeds

        this.setTankData(this.responseData)
        console.log(this.responseData.length);
      }
      catch (error)
      {
        console.log(error);
      }
    },
    // Get most recent API Data and add it to the array with all the API Data
    async getMostRecentAPIData(){ 
      try
      {
        const response = await axios.get('https://api.thingspeak.com/channels/1575729/feeds.json?api_key=XGIU5VOHC9Y03Q9O&results=1')
        if (response.data.feeds[0].entry_id > this.responseData.at(-1).entry_id)
        {
          this.responseData.push(response.data.feeds[0])
          this.setTankData(this.responseData)
        }
        console.log(this.responseData.length);
      }
      catch (error)
      {
        console.log(error);
      }
    },
    setTankData(data)
    {
      this.tankWaterHeight = parseFloat(data.at(-1).field1).toFixed(2)
      this.flowRate = parseFloat(data.at(-1).field2).toFixed(2)

      this.availableVolume = parseFloat((this.surfaceArea * (this.height - this.tankWaterHeight))/1000).toFixed(2)

      this.timeLeft = this.availableVolume/this.flowRate
      let today = moment()
      this.time = today.add(this.timeLeft, 'm')._d
      // console.log(data);
    }
  }
}
</script>

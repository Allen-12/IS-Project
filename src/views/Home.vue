<template>
  <v-container v-if="setup" fluid>
    <v-row dense>
      <v-col cols="6">
        <v-card>
          <v-card-title class="text-h5"> Volume (L) </v-card-title>

          <v-card-subtitle class="text-h6 font-weight-bold">{{
            availableVolume.toFixed(2)
          }}</v-card-subtitle>
        </v-card>
      </v-col>
      <v-col cols="6">
        <v-card>
          <v-card-title class="text-h5"> Flow Rate (L/min) </v-card-title>

          <v-card-subtitle class="text-h6 font-weight-bold">{{
            flowRate.toFixed(2)
          }}</v-card-subtitle>
        </v-card>
      </v-col>
    </v-row>
    <v-row dense>
      <v-col cols="12">
        <v-card>
          <v-card-title class="text-h6">
            Time left for water to be depleted
          </v-card-title>

          <v-card-subtitle
            class="text-h6 font-weight-bold"
            v-if="timeLeft === Infinity"
            >&#8734;</v-card-subtitle
          >
          <v-card-subtitle class="text-h6 font-weight-bold" v-else
            >{{ timeLeft }} minutes</v-card-subtitle
          >
        </v-card>
      </v-col>
    </v-row>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title class="text-h6">
            Estimated Date and Time of Depletion
          </v-card-title>

          <v-card-subtitle
            class="text-h6 font-weight-bold"
            v-if="timeLeft === Infinity"
            >&#8734;</v-card-subtitle
          >
          <v-card-subtitle class="text-h6 font-weight-bold" v-else>{{
            time
          }}</v-card-subtitle>
        </v-card>
      </v-col>
    </v-row>
    <v-divider class="mt-4 mb-4"></v-divider>
    <v-row>
      <v-col cols="12">
        <bar-chart
          v-if="loadedData"
          :volume="availableVolume"
          :maxVolume="maxVolume"
        ></bar-chart>
      </v-col>
    </v-row>
  </v-container>

  <v-container v-else>
    <v-card class="mx-auto" outlined>
      <v-list-item three-line>
        <v-list-item-content>
          <div class="text-overline mb-4">WELCOME!</div>
          <v-list-item-title class="text-h5 mb-1">
            Initial Tank Setup Awaits...
          </v-list-item-title>
          <v-list-item-subtitle>Please click on "Initial Setup" button below to input your initial tank dimensions</v-list-item-subtitle>
        </v-list-item-content>
      </v-list-item>

      <v-card-actions>
        <v-btn outlined rounded color="indigo" :to="{ name: 'Initial Setup' }" link>Go To Initial Setup</v-btn>
      </v-card-actions>
    </v-card>
  </v-container>
</template>

<script>
import Localbase from "localbase";
import moment from "moment";
import BarChart from "../components/Charts/BarChart.vue";

let db = new Localbase("tank_db");

const axios = require("axios");

export default {
  name: "Home",
  components: {
    BarChart,
  },
  data: () => ({
    setup: false,
    tankWaterHeight: 0,
    flowRate: 0,
    surfaceArea: 0,
    height: 0,
    availableVolume: 0,
    maxVolume: 0,
    timeLeft: 0,
    time: 0,
    responseData: [],
    loadedData: false,
  }),
  created: function () {
    db.collection("tank_data")
      .get()
      .then((tank_data) => {
        if (tank_data.length !== 0) {
          this.setup = true;
        }
        this.height = tank_data[0].height;
        this.surfaceArea = tank_data[0].surfaceArea;
        this.maxVolume = tank_data[0].volume;
      });
  },
  mounted: function () {
    this.getAllAPIData();
    setInterval(this.getMostRecentAPIData, 60000);
  },
  methods: {
    // Get all API Data at when page is loaded
    async getAllAPIData() {
      try {
        console.log("Making API Call");
        this.loadedData = false;
        const response = await axios.get(
          "https://api.thingspeak.com/channels/1575729/feeds.json?api_key=XGIU5VOHC9Y03Q9O"
        );
        this.responseData = response.data.feeds;
        console.log("Finished making API call");
        this.loadedData = true;

        this.setTankData(this.responseData);
        // console.log(this.responseData);
      } catch (error) {
        console.error(error);
      }
    },
    // Get most recent API Data and add it to the array with all the API Data
    async getMostRecentAPIData() {
      try {
        this.loadedData = false;
        console.log("Getting most recent data...");
        const response = await axios.get(
          "https://api.thingspeak.com/channels/1575729/feeds.json?api_key=XGIU5VOHC9Y03Q9O&results=1"
        );
        if (
          response.data.feeds[0].entry_id > this.responseData.at(-1).entry_id
        ) {
          this.responseData.push(response.data.feeds[0]);
          this.setTankData(this.responseData);
        }
        console.log("Gotten most recent data");
        this.loadedData = true;
      } catch (error) {
        console.error(error);
      }
    },
    setTankData(data) {
      this.tankWaterHeight = parseFloat(data.at(-1).field1);
      this.flowRate = parseFloat(data.at(-1).field2);

      this.availableVolume =
        parseFloat(this.surfaceArea * (this.height - this.tankWaterHeight)) /
        1000;

      this.timeLeft = parseFloat(this.availableVolume / this.flowRate).toFixed(
        0
      );
      let today = moment();
      this.time = today
        .add(this.timeLeft, "m")
        .format("dddd, MMMM Do YYYY, h:mm:ss a");
      // console.log(this.time);
    },
  },
};
</script>

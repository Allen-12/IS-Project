<template>
  <v-container v-if="setup" fluid>
    <v-row dense class="mb-3">
      <v-col cols="6">
        <v-card>
          <v-card-title class="text-h5">Average Volume Per Day (L)</v-card-title>

          <v-card-subtitle class="text-h6 font-weight-bold">{{averageVolume.toFixed(2)}}</v-card-subtitle>
        </v-card>
      </v-col>
      <v-col cols="6">
        <v-card>
          <v-card-title class="text-h5"> Average Flow Rate Per Day (L/min) </v-card-title>

          <v-card-subtitle class="text-h6 font-weight-bold">{{ averageFlowRate.toFixed(2) }}</v-card-subtitle>
        </v-card>
      </v-col>
    </v-row>
    <v-divider></v-divider>
    <v-row dense class="mt-1">
      <v-col cols="6" class="mb-3">
        <line-chart
          v-if="volumeLoaded"
          :chartData="volumeData"
          :chartLabels="volumeLabels"
          :datasetLabel="'Volume'"
          :titleText="'Volume (L)'"
          :yAxisLabelString="'Volume (L)'"
        >
        </line-chart>
      </v-col>
      <v-divider vertical class="mt-1 mb-1"></v-divider>
      <v-col cols="6">
        <line-chart
          v-if="flowRateLoaded"
          :chartData="flowRateData"
          :chartLabels="flowRateLabels"
          :datasetLabel="'Flow rate'"
          :titleText="'Flow Rate (L/min)'"
          :yAxisLabelString="'Flow Rate (L/minute)'"
        >
        </line-chart>
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
          <v-list-item-subtitle
            >Please click on "Initial Setup" button below to input your initial
            tank dimensions</v-list-item-subtitle
          >
        </v-list-item-content>
      </v-list-item>

      <v-card-actions>
        <v-btn
          outlined
          rounded
          class="blue darken-2 white--text"
          :to="{ name: 'Initial Setup' }"
          link
          >Go To Initial Setup</v-btn
        >
      </v-card-actions>
    </v-card>
  </v-container>
</template>
<script>
import axios from "axios";
import moment from "moment";
import Localbase from "localbase";
import LineChart from "../components/Charts/LineChart.vue";

let db = new Localbase("tank_db");
export default {
  name: "Visualisations",
  components: {
    LineChart,
  },
  data: () => ({
    setup: false,
    height: 0,
    surfaceArea: 0,
    volumeLabels: [],
    volumeData: [],
    volumeLoaded: false,
    flowRateLabels: [],
    flowRateData: [],
    flowRateLoaded: false,
    volumeData2: [],
    averageVolume: 0,
    flowRateData2: [],
    averageFlowRate: 0,
  }),
  created: function () {
    db.collection("tank_data").get().then((tank_data) => {
        if (tank_data.length !== 0) {
          this.setup = true;
        }
        this.height = tank_data[0].height;
        this.surfaceArea = tank_data[0].surfaceArea;
      });
    this.getVolumeData();
    this.getFlowRateData();
    this.getDailyFlowRateData();
    this.getDailyVolumeData();
  },
  methods: {
    async getVolumeData() {
      this.volumeLoaded = false;
      const volData = await axios.get("https://api.thingspeak.com/channels/1575729/fields/1.json?api_key=XGIU5VOHC9Y03Q9O&average=10&round=2");
      this.volumeData = volData.data.feeds.map((data) => parseFloat((this.surfaceArea * (this.height - parseFloat(data.field1))) / 1000).toFixed(2));
      this.volumeLabels = volData.data.feeds.map((data) => moment(data.created_at).format("ddd, MMM Do, h:mm a"));
      this.volumeLoaded = true;
      // console.log(this.volumeData);
    },
    async getFlowRateData() {
      this.flowRateLoaded = false;
      const flowData = await axios.get("https://api.thingspeak.com/channels/1575729/fields/2.json?api_key=XGIU5VOHC9Y03Q9O&average=10&round=2");
      this.flowRateData = flowData.data.feeds.map((data) => parseFloat(data.field2));
      this.flowRateLabels = flowData.data.feeds.map((data) => moment(data.created_at).format("ddd, MMM Do, h:mm a"));
      this.flowRateLoaded = true;
      // console.log(this.flowRateData);
    },
    async getDailyVolumeData() {
      const dailyVolumeData = await axios.get("https://api.thingspeak.com/channels/1575729/fields/1.json?api_key=XGIU5VOHC9Y03Q9O&days=1");
      this.volumeData2 = dailyVolumeData.data.feeds;
      let totalVolume = this.volumeData2.reduce((previous, current) => ({field1: parseFloat(previous.field1) + parseFloat(current.field1)}));
      this.averageVolume = (this.surfaceArea * (this.height - totalVolume.field1 / this.volumeData2.length)) / 1000;
      console.log(this.averageVolume.toFixed(2));
    },
    async getDailyFlowRateData() {
      const dailyFlowData = await axios.get("https://api.thingspeak.com/channels/1575729/fields/2.json?api_key=XGIU5VOHC9Y03Q9O&days=1");
      this.flowRateData2 = dailyFlowData.data.feeds;
      let totalFlowRate = this.flowRateData2.reduce((previous, current) => ({field2: parseFloat(previous.field2) + parseFloat(current.field2)}));
      this.averageFlowRate = totalFlowRate.field2 / this.flowRateData2.length;
      console.log(this.averageFlowRate.toFixed(2));
    },
  },
};
</script>

<template>
    <v-container fluid>
        <v-row>
            <v-col cols="12" class="mb-3">
                <line-chart 
                    v-if="volumeLoaded"
                    :chartData="volumeData"
                    :chartLabels="volumeLabels"
                    :datasetLabel="'Volume'"
                    :titleText="'Trend in Water Volume'"
                    :yAxisLabelString="'Volume (L)'"
                >
                </line-chart>
            </v-col>
            <v-divider class="mt-2 mb-2"></v-divider>
            <v-col cols="12">
                <line-chart 
                    v-if="flowRateLoaded"
                    :chartData="flowRateData"
                    :chartLabels="flowRateLabels"
                    :datasetLabel="'Flow rate'"
                    :titleText="'Trend in Flow Rate'"
                    :yAxisLabelString="'Flow Rate (L/minute)'"
                >
                </line-chart>
            </v-col>
        </v-row>
    </v-container>
</template>
<script>
import axios from 'axios'
import moment from 'moment'
import Localbase from 'localbase'
import LineChart from '../components/Charts/LineChart.vue'

let db = new Localbase('tank_db')
export default {
    name: 'Visualisations',
    components:{
        LineChart
    },
    data: () => ({
        height: 0,
        surfaceArea: 0,
        volumeLabels: [],
        volumeData: [],
        volumeLoaded: false,
        flowRateLabels: [],
        flowRateData: [],
        flowRateLoaded: false
    }),
    created: function(){
        db.collection('tank_data').get().then(tank_data => {
            this.height = tank_data[0].height
            this.surfaceArea = tank_data[0].surfaceArea
        })
        this.getVolumeData()
        this.getFlowRateData()
    },
    methods:{
        async getVolumeData(){
            this.volumeLoaded = false
            const volData = await axios.get('https://api.thingspeak.com/channels/1575729/fields/1.json?api_key=XGIU5VOHC9Y03Q9O&average=10&round=2')
            this.volumeData = volData.data.feeds.map(data => parseFloat((this.surfaceArea * (this.height - parseFloat(data.field1)))/1000).toFixed(2))
            this.volumeLabels = volData.data.feeds.map(data => moment(data.created_at).format('ddd, MMM Do, h:mm a'))
            this.volumeLoaded = true
            console.log(this.volumeData);
        },
        async getFlowRateData(){
            this.flowRateLoaded = false
            const flowData = await axios.get('https://api.thingspeak.com/channels/1575729/fields/2.json?api_key=XGIU5VOHC9Y03Q9O&average=10&round=2')
            this.flowRateData = flowData.data.feeds.map(data => parseFloat(data.field2))
            this.flowRateLabels = flowData.data.feeds.map(data => moment(data.created_at).format('ddd, MMM Do, h:mm a'))
            this.flowRateLoaded = true
            // console.log(this.flowRateData);
        }
    }
}
</script>

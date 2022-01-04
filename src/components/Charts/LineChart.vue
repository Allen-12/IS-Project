<script>
  import { Line } from 'vue-chartjs'

  export default {
    extends: Line,
    props: {
        chartData: {
            type: Array | Object,
            required: false
        },
        chartLabels: {
            type: Array,
            required: true
        },
        datasetLabel: String,
        yAxisLabelString: String,
        titleText: String
    },
    data() {
      return {
        options: {
          scales: {
            yAxes: [{
              ticks: {
                beginAtZero: true,
                // suggestedMax: this.maxVolume
              },
              gridLines: {
                display: true
              },
              scaleLabel:{
                  display: true,
                  labelString: this.yAxisLabelString,
                  fontColor: '#000000'
              }
            }],
            xAxes: [{
              gridLines: {
                display: false
              },
            }]
          },
          legend: {
            display: false
          },
          title: {
              display: true,
              position: 'top',
              text: this.titleText,
              fontSize: 14,
              padding: 12,
              fontColor: '#000000'
          },
          responsive: true,
          maintainAspectRatio: false
        }
      }
    },
    mounted() {
        this.renderChart({
            labels: this.chartLabels,
            datasets: [{
                label: this.datasetLabel,
                borderColor: '#1E88E5',
                pointBackgroundColor: 'white',
                borderWidth: 2,
                pointBorderColor: '#1E88E5',
                backgroundColor: 'transparent',
                data: this.chartData
            }]
        }, this.options)
    },
    updated(){
        this.renderChart(this.chartData, this.options)
    }
  }
</script>
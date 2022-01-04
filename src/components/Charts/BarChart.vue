<script>
  import { Bar } from 'vue-chartjs'

  export default {
    extends: Bar,
    props: ["volume","maxVolume"],
    data() {
      return {
        chartData: {
          labels: ['Volume'],
          datasets: [{
            label: 'Water Volume',
            borderWidth: 1,
            backgroundColor: ['#1ca3ec'],
            borderColor: ['#0f5e9c'],
            pointBorderColor: '#2554FF',
            data: [this.volume.toFixed(2)]
          }]
        },
        options: {
          scales: {
            yAxes: [{
              ticks: {
                beginAtZero: true,
                suggestedMax: this.maxVolume
              },
              gridLines: {
                display: true
              },
              scaleLabel:{
                  display: true,
                  labelString: "Volume (L)",
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
            display: true,
            position: 'right',
            labels: {
                fontColor: '#000000'
            }
          },
          title: {
              display: true,
              position: 'top',
              text: 'Water Level',
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
        this.renderChart(this.chartData, this.options)
    },
    updated(){
        this.renderChart(this.chartData, this.options)
    }
  }
</script>
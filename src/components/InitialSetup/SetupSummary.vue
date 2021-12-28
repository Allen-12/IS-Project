<template>
    <CylindricalSummary v-if="tankType === 'cylindrical'"></CylindricalSummary>
    <RectangularSummary v-else></RectangularSummary>
</template>

<script>
import Localbase from 'localbase'
import CylindricalSummary from '../Cylindrical/CylindricalSummary.vue'
import RectangularSummary from '../Rectangular/RectangularSummary.vue'

let db = new Localbase('tank_db')

export default {
    name: "SetupSummary",
    components: {
      CylindricalSummary,
      RectangularSummary
    },
    data: () => ({
      tankType: ''
    }),
    created: function(){
      db.collection('tank_data').get().then(tank_data => {
          this.tankType = tank_data[0].tank_type
      })
    }
}
</script>

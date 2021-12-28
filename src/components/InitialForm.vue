<template>
  <v-container fluid>
      <v-select
        v-model="tankType"
        :items="tanks"
        label="Select a tank type"
        outlined
        @change="setTankType"
        >
      </v-select>

      <CylindricalForm v-if="tankType === 'Cylindrical'"></CylindricalForm>
      <RectangularForm v-if="tankType === 'Rectangular'"></RectangularForm>
  </v-container>
</template>

<script>
import CylindricalForm from '../components/CylindricalForm.vue'
import RectangularForm from '../components/RectangularForm.vue'

export default {
    name: "InitialForm",
    components: {
      CylindricalForm,
      RectangularForm
    },
    data: () => ({
      valid: true,
      tanks: [
        'Cylindrical',
        'Rectangular'
      ],
      tankType: '',
    }),

    methods: {
      setTankType()
      {
          console.log(this.tankType)
      }
    },
}
</script>
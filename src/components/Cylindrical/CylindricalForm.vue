<template>
    <v-form
      ref="form.v"
      v-model="valid"
      lazy-validation
      >
      <v-text-field
        v-model="volume"
        :counter="20"
        :rules="volumeRules"
        label="Volume (L)"
        required
        clearable
      ></v-text-field>

      <v-text-field
        v-model="height"
        :counter="20"
        :rules="heightRules"
        label="Height (cm)"
        required
        clearable
      ></v-text-field>

      <v-text-field
        v-model="diameter"
        :counter="20"
        :rules="diameterRules"
        label="Diameter (cm)"
        required
        clearable
      ></v-text-field>

      <v-btn
        color="success"
        class="mr-4"
        @click="saveSetupData"
      >
        Complete Setup
      </v-btn>

      <v-btn
        color="error"
        class="mr-4"
        @click="reset"
      >
        Reset
      </v-btn>
    </v-form>
</template>

<script>
import Localbase from 'localbase'
import {v4 as uuidv4} from 'uuid';

let db = new Localbase('tank_db')

export default {
    name: 'CylindricalForm',
    data: () => ({
      valid: true,
      volume: '',
      volumeRules: [
        v => !!v || 'Volume is required',
        v => (v && !isNaN(Number(v))) || 'Volume must be a number',
        v => (v && v > 0) || 'Volume must be greater than 0',
      ],
      height: '',
      heightRules: [
        v => !!v || 'Height is required',
        v => (v && !isNaN(Number(v))) || 'Height must be a number',
        v => (v && v > 0) || 'Height must be greater than 0',
      ],
      diameter: '',
      diameterRules: [
        v => !!v || 'Diameter is required',
        v => (v && !isNaN(Number(v))) || 'Diameter must be a number',
        v => (v && v > 0) || 'Diameter must be greater than 0',
      ],
    }),

    methods: {
      validate () 
      {
        this.$refs.form.validate()
      },
      reset ()
      {
        this.$refs.form.reset()
      },
      resetValidation ()
      {
        this.$refs.form.resetValidation()
      },
      saveSetupData()
      {
          let setupData =
          {
              id: uuidv4(),
              volume: Number(this.volume),
              diameter: Number(this.diameter),
              height: Number(this.height),
              surfaceArea: (this.volume * 1000) / this.height,
              tank_type: 'cylindrical'
          }
          // console.log(setupData)
          db.collection('tank_data').add(setupData).then(response => {
            this.added = response.success
            // console.log(this.added);
          })
          this.$router.push({name: 'Home'})
      },
    },
}
</script>
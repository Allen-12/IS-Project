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
        v-model="length"
        :counter="20"
        :rules="lengthRules"
        label="Length (cm)"
        required
        clearable
      ></v-text-field>

      <v-text-field
        v-model="width"
        :counter="20"
        :rules="widthRules"
        label="Width (cm)"
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
    name: 'RectangularForm',
    data: () => ({
      valid: true,
      volume: '',
      volumeRules: [
        v => !!v || 'Volume is required',
        v => (v && !isNaN(Number(v))) || 'Volume must be a number',
        v => (v && v > 0) || 'Volume must be greater than 0',
      ],
      length: '',
      lengthRules: [
        v => !!v || 'Length is required',
        v => (v && !isNaN(Number(v))) || 'Length must be a number',
        v => (v && v > 0) || 'Length must be greater than 0',
      ],
      width: '',
      widthRules: [
        v => !!v || 'Width is required',
        v => (v && !isNaN(Number(v))) || 'Width must be a number',
        v => (v && v > 0) || 'Width must be greater than 0',
      ],
      height: '',
      heightRules: [
        v => !!v || 'Height is required',
        v => (v && !isNaN(Number(v))) || 'Height must be a number',
        v => (v && v > 0) || 'Height must be greater than 0',
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
              length: Number(this.length),
              width: Number(this.width),
              height: Number(this.height),
              tank_type: 'rectangular'
          }
          console.log(setupData)
          db.collection('tank_data').add(setupData).then(response => {
            this.added = response.success
            console.log(this.added);
            this.$router.push({name: 'Home'})
          })
      },
    },
}
</script>
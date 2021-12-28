<template>
    <SetupSummary v-if="added"></SetupSummary>
    <InitialForm v-else></InitialForm>
</template>

<script>
import Localbase from 'localbase'
import InitialForm from "../components/InitialSetup/InitialForm.vue"
import SetupSummary from "../components/InitialSetup/SetupSummary.vue"

let db = new Localbase('tank_db')

export default {
    name: "InitialSetup",
    
    components:
    {
      InitialForm,
      SetupSummary
    },
    data: () => ({
      added: false,
    }),
    created(){
      db.collection('tank_data').get().then(tank_data => {
        this.added = !!tank_data.length
      })
    }
}
</script>
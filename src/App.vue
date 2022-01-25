<template>
  <v-app id="inspire">
    <v-navigation-drawer
        v-model="drawer"
        app
        class="blue darken-2"
    >
      <v-list-item>
        <v-list-item-content>
          <v-list-item-title class="text-h6 white--text">
            Dashboard
          </v-list-item-title>
        </v-list-item-content>
      </v-list-item>

      <v-divider></v-divider>

      <v-list
          dense
          nav
      >
        <v-list-item 
              :to="'/'"
              link>
          <v-list-item-icon>
            <v-icon color="white">mdi-home</v-icon>
          </v-list-item-icon>

          <v-list-item-content>
            <v-list-item-title class="white--text">Home</v-list-item-title>
          </v-list-item-content>
        </v-list-item>
        <v-list-item 
              :to="{ name: 'Initial Setup' }"
              link>
          <v-list-item-icon>
            <v-icon color="white">mdi-cogs</v-icon>
          </v-list-item-icon>

          <v-list-item-content>
            <v-list-item-title class="white--text">Initial Setup</v-list-item-title>
          </v-list-item-content>
        </v-list-item>

        <v-list-item 
        :to="{ name: 'Visualisations' }"
        link>
          <v-list-item-icon>
            <v-icon color="white">mdi-chart-areaspline</v-icon>
          </v-list-item-icon>

          <v-list-item-content>
            <v-list-item-title class="white--text">Visualizations</v-list-item-title>
          </v-list-item-content>
        </v-list-item>

        <!-- <v-list-item
          :to="{ name: 'Statistics' }"
          link>
          <v-list-item-icon>
            <v-icon color="white">mdi-google-analytics</v-icon>
          </v-list-item-icon>

          <v-list-item-content>
            <v-list-item-title class="white--text">Statistics</v-list-item-title>
          </v-list-item-content>
        </v-list-item> -->
      </v-list>
    </v-navigation-drawer>

    <v-app-bar 
    app
    class="blue darken-2"
    >
      <v-app-bar-nav-icon @click="drawer = !drawer"></v-app-bar-nav-icon>

      <v-toolbar-title class="white--text">Dashboard</v-toolbar-title>
    </v-app-bar>

    <v-main>
      <v-container fluid>
        <router-view></router-view>
      </v-container>
    </v-main>
  </v-app>
</template>

<script>
export default {
  data: () => ({ drawer: null }),
}
</script>

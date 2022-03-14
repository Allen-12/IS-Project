# Final Year Project Dashboard

This repository contains all the source code that I used to build the dashboard for my final year project. The goal of my project was to predict when the water in a tank would be depleted based on the volume of water in the tank and the flow rate of water out of the tank.

The project had two main parts: the hardware part and the software part.

## Hardware Part
This part consisted mostly of two sensors: an ultrasonic sensor that was used to measure the volume of water in a tank, and a water flow sensor that was used to measure the flow rate of water flowing out of the tank. The data collected from these two sensors was streamed to a Thingspeak channel.

## Software Part
This consisted of a dashboard that was built using VueJS and Vuetify. The dashboard displays the level of water in the tank, the flow rate of water flowing out from the tank and the time it will take for the water to be depleted.

## Technologies used:
1. NodeMCU
2. HC-SR04 Ultrasonic Sensor
3. YF-S201 1/2 inch Waterflow Sensor
4. Thingspeak Platform
5. VueJS
6. Vuetify
7. Vue ChartJS
8. Axios

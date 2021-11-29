#include "ThingSpeak.h"
#include "secrets.h"
#include <ESP8266WiFi.h>

// WiFi Credentials 
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
String myStatus = "Ultrasonic and Wateflow sensor status";
WiFiClient  client;

// Thingspeak Credentials
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Waterflow sensor definitions
#define LED_BUILTIN 16
#define WATERFLOW_SENSOR  4     // D2

// Waterflow sensor variables
long currentMillis = 0;
long previousMillis = 0;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;

// Ultrasonic sensor definitions
#define TRIG_PIN  2     // D4
#define ECHO_PIN  0     // D3

// Initialise 3 variables to store the duration of the US pulse, the distance to the object in centimetres and in inches
long duration;
float height;

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup()
{
  Serial.begin(9600);

  // Initialize ThingSpeak
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);

  delay(10);
  
  // Waterflow sensor pin initialisations
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(WATERFLOW_SENSOR, INPUT_PULLUP);

  // Ultrasonic sensor pin initialisations
  pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input

  pulseCount = 0;
  flowRate = 0.0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(WATERFLOW_SENSOR), pulseCounter, FALLING);
}

void loop()
{
  ultrasonicSensor();
  waterflowSensor();

  // Prints the distance on the Serial Monitor
  Serial.print("Height (in cm): ");
  Serial.println(height);
  
  // Print the flow rate for this second in litres / minute
  Serial.print("Flow rate: ");
  Serial.print(float(flowRate));  // Print the integer part of the variable
  Serial.println("L/min");

  // Connecting to WiFi and sending data to Thingspeak
  
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  // Set the status
  ThingSpeak.setStatus(myStatus);
  
  // Set the fields with the flow rate and water height values
  ThingSpeak.setField(1, height);
  ThingSpeak.setField(2, flowRate);

  // Write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200)
  {
    Serial.println("Channel update successful.");
  }
  else
  {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  delay(20000);
}

// Ultrasonic sensor logic
void ultrasonicSensor()
{
  // Clear HC-SR04
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Set trigger pin to send out US pulse every 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Duration shows how long it takes (in ms) for the US pulse to travel to an object and get back to the echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Distances between sensor and object in both centimetres and inches
  height = (0.0343 * duration) / 2;
  Serial.println(height);
}

// Waterflow sensor logic
void waterflowSensor()
{
  currentMillis = millis();

  pulse1Sec = pulseCount;
  pulseCount = 0;

  // Because this loop may not complete in exactly 1 second intervals we calculate
  // the number of milliseconds that have passed since the last execution and use
  // that to scale the output. We also apply the calibrationFactor to scale the output
  // based on the number of pulses per second per units of measure (litres/minute in
  // this case) coming from the sensor.
  flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
  Serial.println(flowRate);
  previousMillis = millis();
}

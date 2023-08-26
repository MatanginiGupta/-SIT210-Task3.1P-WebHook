#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include "DHT.h"

char wifiName[] = "matangini gupta's iphone"; 
char wifiPassword[] = "Matangini@1811";       
unsigned long channelId = 2251550;
const char *APIkey = "63JVT5V94HBI6PPL";     

WiFiClient client; 
DHT dht(2, DHT11);// DHT sensor connected to digital pin 2

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connection in process to Wifi...... ");
    Serial.println(wifiName);
    WiFi.begin(wifiName, wifiPassword);
    delay(1000);
  }

  Serial.println("successfully connected!");

  // Initialize ThingSpeak communication
  ThingSpeak.begin(client);
}

void loop() {
  // Read temperature from DHT sensor
  float tempCelsius = dht.readTemperature();
  Serial.print("Temperature reading: ");
  Serial.print(tempCelsius);
  Serial.println("C");

  // Send temperature data to ThingSpeak channel
  ThingSpeak.writeField(channelId, 1, tempCelsius, APIkey); 
  Serial.println("Data transmission to ThingSpeak complete!!!");

  // Delay before sending next data
  delay(30000); // 30 seconds
}

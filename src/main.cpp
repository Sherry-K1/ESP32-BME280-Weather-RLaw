// Read values from the sensor and print them in the console.
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

void refresh_readings();  // Declare in the header so that the compiler knows about it before it is called in loop()

#ifndef LED_BUILTIN
#define LED_BUILTIN 2   // This is valid for the nodemcu-32S
#endif

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  bool status;

  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  refresh_readings();
  delay(4000);
}

void refresh_readings() {
  float f_temperature;
  float f_humidity;
  float f_pressure;
  float f_altitude;

  digitalWrite(LED_BUILTIN, HIGH);
  // bme is global to this file only
  f_temperature = bme.readTemperature();
  f_humidity = bme.readHumidity();
  f_pressure = bme.readPressure() / 100.0F;
  f_altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

  // Temperature
  Serial.print(f_temperature);
  Serial.println(" °C");

  // Humidity
  Serial.print(f_humidity);
  Serial.println(" %");

  // Pressure
  Serial.print(f_pressure);
  Serial.println(" hPa");

  // Appx altitude
  Serial.print(f_altitude);
  Serial.println(" m");   
  
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("-----v1-----");   
}
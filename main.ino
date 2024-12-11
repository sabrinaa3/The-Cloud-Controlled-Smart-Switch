#include <WiFi.h>
#include <WebServer.h>
#include "gpio_init.h"
#include "wifi_init.h"
#include "page_main.h"

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
// const char* ssid = "SHAW-DE8A";
// const char* password = "earth2356candid";

#define pin12 12 // Pin for NO 5V relay
#define pin14 14 // Pin for Pushbutton 
#define pin32 32 // ADC1 Pin for V/I measurement
#define pin33 33 // ADC1 Pin for V/I measurement
#define pin34 34 // ADC1 Pin for V/I measurement
#define pin35 35 // ADC1 Pin for V/I measurement
#define pin36 36 // ADC1 Pin for V/I measurement
#define pin39 39 // ADC1 Pin for V/I measurement
#define pin25 25 // ADC1 Pin for V/I measurement
#define pin26 26 // ADC1 Pin for V/I measurement

// const float adcFactor = 0.0008058608059;

float vRead;
float IRead;
float lowI;
float highI;
float lowV;
float highV;
float avgI;
float realI;
float avgV;
float realV;
float power;
// float const voltCali = 4.230; // Ajeet's lamp
// float const currCali = 0.001934; // Ajeet's lamp
float const voltCali = 13.333; // Basant's lamp
float const currCali = 6000; // Basant's lamp

unsigned long startTime = millis();


int const sample = 1000;

// Set web server port number to 80
WebServer server(80);

volatile bool state = LOW; // Initial state of the relay 


void setup() {
    // Set baud rate for serial monitor
    Serial.begin(115200);
    delay(3000);
    // Initialize relay (pin39) to low 
    pinMode(pin12, OUTPUT);

    // Initialize push button
    // pinMode(pin14, INPUT_PULLUP);
    
    // attachInterrupt(pin14, buttonPress, FALLING); // Interrupt executes when button goes (falls) from high to low

    // Initialize WiFi network
    wifi_startup(ssid, password);

    // Set up routes. These routes are accessed from the browser once the IP address is accessed

    server.on("/", handleRoot); // TODO: Replace with function that will be executed on the server

    server.on("/relay/on", handleOn); // dir to turn on the push button

    server.on("/relay/off", handleOff); // dir to turn off the push button
    
    server.on("/getpowerUsage", HTTP_GET, handleGetPower); // reoute for voltage reading

    server.on("/getStatus", HTTP_GET, handleGetStatus);

    // Initialize HTTP server
    server.begin();
}

void loop() {
  server.handleClient();
    
}

void handleRoot() {
  server.send_P(200, "text/html", PAGE_MAIN);
}

void handleOn() {
  state = HIGH;
  digitalWrite(pin12, state);
  server.send_P(200, "text/html", PAGE_MAIN);
}

void handleOff() {
  state = LOW;
  digitalWrite(pin12, state);
  server.send_P(200, "text/html", PAGE_MAIN); 
}

void handleGetPower() {
  while (millis() - startTime < 100) {
    IRead = analogRead(pin39);
    if (IRead < lowI) {
      lowI = IRead;
    }
    if (IRead > highI) {
      highI = IRead;
    }
    avgI = (lowI+highI) / 2;
  }
  startTime = millis();

  if (highI > 30) {
    // realI = 172.228 / avgI;
    realI = avgI/currCali;
  }

  // Measure voltage

  while (millis() - startTime < 100) {
    vRead = analogRead(pin36);
    if (vRead < lowV) {
      lowV = vRead;
    }
    if (vRead > highV) {
      highV = vRead;
    }
    avgV = (lowV+highV) / 2;
  }
  startTime = millis();


    if (highV > 30) {
      // realI = 172.228 / avgI;
      realV = avgV / voltCali;
    }
  // Serial.println(realV);
  power = realV*realI;
  
  // Serial.println(power);
  String powerStr = String(power, 2);  // Format to 2 decimal places
  // String powerStr = String(40.35,2);
  server.send(200, "text/plain", powerStr);  // Send the voltage value to the client
}

// to return the state of the appliance (connected or not)
void handleGetStatus() {
  String status = (state == HIGH) ? "on" : "off";
  server.send(200, "text/plain", status);
}



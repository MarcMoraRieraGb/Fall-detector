//
 //
 // Desarrolladores de este código:
 //
 // - Xavier Vilanova Barrio - 2022
 //
 // - Marc Mora Riera - 2022
 //
 //
 // Este programa utiliza de base el Programa Sensores de: 
 // - JUAN PALOMARES MOYANO - 2019
 // No se permite la distribución, la utilización o la venta de este código
 // sin el permiso de los desarrolladores
 //
 // Micro: ESP32 Dev Module
 // MPU6500 - Bus I2C
 // Boto Generic
 
 
 #include <WiFi.h>
 #include <HTTPClient.h>
 
 const char* ssid = "ESP32-Access-Point";
 const char* password = "123456789";
 
 //Your IP address or domain name with URL path
 const char* serverNameAccelerometre = "http://192.168.4.1/accelerometre";
 
 #include <Wire.h>
 
 
 //String Acceleracio;
 String Acceleracio;
 
 
 unsigned long previousMillis = 0;
 const long interval = 50;
 
 void setup() {
 Serial.begin(115200);
 
 
 WiFi.begin(ssid, password);
 //IPAddress IP(192, 168, 1, 184);
 Serial.println("Connecting");
 while(WiFi.status() != WL_CONNECTED) {
 delay(50);
 Serial.print(".");
 }
 Serial.println("");
 Serial.print("Connected to WiFi network with IP Address: ");
 Serial.println(WiFi.localIP());
 }
 
 void loop() {
 unsigned long currentMillis = millis();
 
 if(currentMillis - previousMillis >= interval) {
 // Check WiFi connection status
 if(WiFi.status()== WL_CONNECTED ){
 humidity = httpGETRequest(serverNameAcceleracio);
 Serial.println( Acceleracio);
 
 // save the last HTTP GET Request
 previousMillis = currentMillis;
 }
 else {
 Serial.println("WiFi Disconnected");
 }
 }
 }
 
 
 
 
 String httpGETRequest(const char* serverName) {
 WiFiClient client;
 HTTPClient http;
 
 // Your Domain name with URL path or IP address with path
 http.begin(client, serverName);
 
 // Send HTTP POST request
 int httpResponseCode = http.GET();
 
 String payload = "--";
 
 if (httpResponseCode>0) {
 // Serial.print("HTTP Response code: ");
 // Serial.println(httpResponseCode);
 payload = http.getString();
 }
 else {
 // Serial.print("Error code: ");
 // Serial.println(httpResponseCode);
 }
 // Free resources
 http.end();
 
 return payload;
 }

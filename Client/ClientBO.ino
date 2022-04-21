#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverNameTemp = "http://192.168.4.1/humi";
const char* serverNameHumi = "http://192.168.4.1/mostra";


#include <Wire.h>
//#include <Adafruit_GFX.h>

int Temp_int;
int Humidi_int;


//String temperature;
String humidity;


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
     // temperature = httpGETRequest(serverNameTemp);
      humidity = httpGETRequest(serverNameHumi);

      //Serial.println("Temperature: " + temperature + " *C - Humidity: " + humidity );
     // Temp_int=temperature.toInt();
     // Humidi_int=humidity.toInt();
     // Serial.println(Temp_int + Humidi_int );
       Serial.println( humidity);
      

      
    
      
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
//    Serial.print("HTTP Response code: ");
//    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
//    Serial.print("Error code: ");
//    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

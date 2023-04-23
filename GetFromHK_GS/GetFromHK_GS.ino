/*
 *  ESP8266 JSON Decode of server response
 *  -Manoj R. Thkuar
 *  https://circuits4you.com
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>//  server net
#include <ArduinoJson.h>//lib (5.13.3)  json read

const char* wifiName = "myhome6";
const char* wifiPass = "LiFiPass61";

//Web Server address to read/write from 


void setup() {
  
  Serial.begin(115200);
  delay(10);
  Serial.println();
  
  Serial.print("Connecting to ");
  Serial.println(wifiName);

  WiFi.begin(wifiName, wifiPass);
  Serial.println(WiFi.macAddress()); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 Serial.print("ESP8266 MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  HTTPClient http;    //Declare object of class HTTPClient

  Serial.print("Request Link:");
 
  http.addHeader("Content-Type", "application/json; charset=utf-8"); 

   Serial.println("http://hoshikala.ir/iot/loglastjson.php?tkn=S0650ini0RtRSP5S5RSP&id=220"); 
  http.begin("http://hoshikala.ir/iot/loglastjson.php?tkn=S0650ini0RtRSP5S5RSP&id=220");     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload from server

  Serial.print("Response Code:"); //200 is OK
  Serial.println(httpCode);   //Print HTTP return code

  Serial.print("Returned data from Server:");
  Serial.println(payload);    //Print request response payload
  
  if(httpCode == 200)
  {
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    DynamicJsonBuffer jsonBuffer(capacity);
  
   // Parse JSON object
    JsonObject& root = jsonBuffer.parseObject(payload);
    if (!root.success()) {
      Serial.println(F("Parsing failed!"));
      return;
    }
  
    // Decode JSON/Extract values
     Serial.println("----------------------------------------------------------------");
    Serial.println(F("Response:"));
     Serial.print("inA= ");
    Serial.println(root["ina"].as<char*>());
   if(root["ina"]==0){
    digitalWrite(LED_BUILTIN, HIGH); //off
   }
   else
   {
    digitalWrite(LED_BUILTIN, LOW); //on
   }

    Serial.print("inB= ");
    Serial.println(root["inb"].as<char*>());
  
  }
  else
  {
    Serial.println("Error in response");
  }

  http.end();  //Close connection
  
  delay(10000);  //GET Data at every 5 seconds
}

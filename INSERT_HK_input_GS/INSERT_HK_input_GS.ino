// ---------------------------------------
//------How to use insert and send data to Hooshi platform?
// 
// you need  esp8266 version 2.7.0 and ArduinoJson.h version (5.13.5). 
// -----------------Insert to HoshiKala Platform --------------
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
// config paramiter from hoshikala Platform 

//ENTER YOUR WIFI SETTINGS
// Modem SSID and Password 
const char *ssid = "yourssid";  
const char *password = "yourpassword";
// ------------------------- Variabales 
int counter=0;
int reset_counter_loop=0;
//---------------------------- SetUp --------------------
void setup() 
{
 //--------- Serial Setup
  Serial.begin(115200);
  Serial.println();
  Serial.println("--- HoshiKalaPlatform --- ");
  delay(10);
//--------- WiFi Connection Setup
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
//---------  Wait to connect WiFi Modem
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
//---------  ESP connected to WiFi Modem 
  Serial.println("");
  Serial.println("WiFi connected");
//---------  IP Address which Modem give to ESP 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
}
//---------  Loop ---------------------------------------------------- 
void loop()
{
  //---------  Counter  
  counter++;
  if(counter>50) 
     counter=0;
  //--------- Prepare URL  
  //http://hoshikala.ir/iot/insert.php?id=1&ina=469&tkn=xxxxxxxxxxxxx
  String url =  "http://hoshikala.ir/iot/insert.php?id=100" ;
  url += "&ina=";
  url += String(counter);
  url += "&inb=";
  url += String(counter+10);
  url += "&tkn=xxxxxxxxxxxxxxxxxxxx";
  //--------- send url   ---------------
  HTTPClient http; //Declare object of class HTTPClient

  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //2-Specify content-type header
  Serial.println();
  Serial.println();
  Serial.print("Request Link:");
  Serial.println(url);

  http.begin(url); //Specify request destination

  int httpCode = http.GET();         //Send the request
  String payload = http.getString(); //Get the response payload from server
  Serial.print("Response Code:"); //200 is OK
  Serial.println(httpCode);   //Print HTTP return code
  Serial.print("Returned data from Server:");
  Serial.println(payload);    //Print request response payload
  if (httpCode == 200)
  {
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    // DynamicJsonBuffer jsonBuffer(capacity);
    StaticJsonBuffer<1100> jsonBuffer;
    // Parse JSON object
    JsonObject &root = jsonBuffer.parseObject(payload);


  }
  else
  {
    Serial.println("Error in response");
  }

  http.end();  //Close connection

  delay(10000);  //GET Data at every 10 seconds
 

}
//----------------- END 

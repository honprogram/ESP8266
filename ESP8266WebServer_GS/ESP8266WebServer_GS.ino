/*
ESP8266WebServer Getting Started
*/

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "yourssid";  //ENTER YOUR WIFI SETTINGS
const char *password = "yourpassword";

ESP8266WebServer server(80);
int x=0;

/* Just a little test message.  Go to http://192.168.x.1 in a web browser
   connected to this access point to see it.
*/
// -------------handleRoot()---------------------------
void handleRoot() {
  String str;
  str+="<h1>X is= ";
  str+=String(x);
  str+=" hi class </h1>";
  server.send(200, "text/html", str);
}
// -------------setup()---------------------------
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
//------------- Stay until connect to wifi -----------
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
//------------- If esp connect to wifi, go to this line. -----------
  Serial.println();
  Serial.println(F("WiFi connected"));
// Start the server
  Serial.println(F("Server started"));
// Print the IP address
  Serial.println(WiFi.localIP());
//------------- Setup server -----------
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  //------------- Listen to client -----------
  server.handleClient();
  x=50;
  
}

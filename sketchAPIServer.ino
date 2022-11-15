#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
const char* ssid = "";
const char* password  = "";
 
ESP8266WebServer server(80);   //Instancia servidor na porta 80
 
String page = "";
int LEDPin = 13;

void setup(void){
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
  bool LED = false;
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "application/json", "{ 'server': true }");
  });
  server.on("/LEDOn", [](){
    server.send(200, "application/json", "{ 'led': true }");
    digitalWrite(LEDPin, HIGH);
    LED = true;
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "application/json", "{ 'led': false }");
    digitalWrite(LEDPin, LOW);
    LED = false;
    delay(1000); 
  });
  server.on("/LEDCheck", [](){
    if (LED){
        server.send(200, "application/json", "{ 'led': true }")
    }else{
        server.send(200, "application/json", "{ 'led': false }")
    }
  })
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}
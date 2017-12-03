#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ultrasonic.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

 
//Define os pinos para o trigger e echo
#define pino_trigger 4 
#define pino_echo 5
Ultrasonic ultrasonic(pino_trigger, pino_echo);

#define myPeriodic 120; 

const char* MY_SSID = "MAFX"; 
const char* MY_PWD = "edwijes70hp";
int sent = 0;

void setup() {
  Serial.begin(115200);
  connectWifi();
  Serial.println("Lendo dados do sensor...");
}

void loop() {
   //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  int result = convertToPercent(cmMsec);

  Serial.print(cmMsec);
  Serial.print("Distancia em %: ");
  Serial.print(result);
  Serial.println("\n\n");

  sendResultTS(result);

  int count = myPeriodic;
  while(count--)
  delay(1000);
}

void connectWifi()
{
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");  
}//end connect

int convertToPercent(float cmMsec){  
   int roundSensorDistante = cmMsec;
   int resultPercent = (((roundSensorDistante - 20) * (-1.25)) + 100);
   return resultPercent;
}

void sendResultTS(int percent)
{  
    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject(); 
 
    JSONencoder["value"] = percent;

//    JsonArray& values = JSONencoder.createNestedArray("values"); //JSON array
//    values.add(20); //Add value to array
//    values.add(21); //Add value to array
//    values.add(23); //Add value to array
// 
//    JsonArray& timestamps = JSONencoder.createNestedArray("timestamps"); //JSON array
//    timestamps.add("10:10"); //Add value to array
//    timestamps.add("10:20"); //Add value to array
//    timestamps.add("10:30"); //Add value to array
 
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http;
 
    http.begin("http://ltmyapis.herokuapp.com/api/v1/iot/devices/CX_BIA");     
    http.addHeader("Content-Type", "application/json");  
 
    int httpCode = http.POST(JSONmessageBuffer);   
    String payload = http.getString();             
 
    Serial.println(httpCode); 
    Serial.println(payload);
 
    http.end();  //Close connection

    delay(1000);
}


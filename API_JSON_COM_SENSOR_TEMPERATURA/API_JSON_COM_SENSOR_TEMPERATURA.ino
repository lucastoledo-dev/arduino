/* 
  This a simple example of the aREST Library for Arduino (Uno/Mega/Due/Teensy)
  using the Ethernet library (for example to be used with the Ethernet shield). 
  See the README file for more details.
 
  Written in 2014 by Marco Schwartz under a GPL license. 
*/

// Libraries
#include <DHT.h>
#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>
#include <avr/wdt.h>

// DHT11 sensor pins
#define DHTPIN 7 
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


// Definicoes dos pinos ligados ao sensor gas
int pin_glp = A2;
int nivel_sensor = 250;

// Enter a MAC address for your controller below.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192,168,1,55);
EthernetServer server(80);

// Create aREST instance
aREST rest = aREST();

float temperature;
float humidity;
int glp;

void setup(void)
{  
  // Start Serial
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // Expose variables to REST API
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
  //rest.variable("glp",&glp);

  // Function to be exposed
  //rest.function("led",ledControl);
  
   // Set name
  rest.set_id("1");
  rest.set_name("home_station");

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  dht.begin();
  // Start watchdog
  wdt_enable(WDTO_4S);
  
}

void loop() {  


  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature();
  
  //glp = analogRead(pin_glp);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  
  // listen for incoming clients
  EthernetClient client = server.available();
  rest.handle(client);
  wdt_reset();
  
}

// Custom function accessible by the API
int ledControl(String command) {
  
  // Get state from command
  int state = command.toInt();
  
  digitalWrite(6,state);
  return 1;
}

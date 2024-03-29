#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include "basicOTA.h"

//set Wifi credentials 
#define WIFI_SSID "Bildungsresistent"
#define WIFI_PASS "Prokastination"


////SONO STUFF

// constants won't change. Used here to set a pin number:
const int relaisPin = 12;//                 NUMBER D6
const int trigger = 13;  //trigger pin number  NUMBER D8
const int echo = 15;   //echo pin number       NUMBER D7


// Variables will change:
int relaisState = LOW;             // ledState used to set the LED
long dauer = 0;                 //traveltime 
long dist = 0;                  // distance

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long triggerMillis = 0;

// constants won't change:
const long interval = 7000;           // interval at which to shut down and up 1800000 = 30 Minuten
const long distT = 140;             // distance range at which to trigger

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

  // Setup serial port
  Serial.begin(9600);
  Serial.println();
  
  //Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Setup Firmware update over the air (OTA)
  setup_OTA();


  // set the digital pin as output:
  pinMode(relaisPin, OUTPUT);
  pinMode(trigger, OUTPUT);                // Trigger Pin als Ausgang definieren
  pinMode(echo, INPUT);                    // Echo Pin als Eingang defnieren

  
}



int ultra()

{

    digitalWrite(trigger, LOW);              // Den Trigger auf LOW setzen um

                                             // ein rauschfreies Signal

                                             // senden zu können

    delay(5);                                // 5 Millisekunden warten

    digitalWrite(trigger, HIGH);             // Den Trigger auf HIGH setzen um eine 

                                             // Ultraschallwelle zu senden

    delay(10);                               // 10 Millisekunden warten

    digitalWrite(trigger, LOW);              // Trigger auf LOW setzen um das 

                                             // Senden abzuschließen

    dauer = pulseIn(echo, HIGH);             // Die Zeit messen bis die 

                                             // Ultraschallwelle zurückkommt

    dist = (dauer/2) / 29.1;           // Die Zeit in den Weg in Zentimeter umrechnen

     delay(10);                             // Nach einer Hunderstelsekunde wiederholen
    return dist;

 

}


int sense() {
  int zwerg = 0;
  for(int i = 0; i<= 9; i++){
    zwerg = zwerg + ultra();
    delay (100);
  }
  zwerg= zwerg/10;
  Serial.print(zwerg);            // Den Weg in Zentimeter ausgeben
  Serial.println(" cm");            
  return zwerg;
}

// the loop function runs over and over again forever
void loop() {
  // Check for OTA updates
  ArduinoOTA.handle();
    
   unsigned long currentMillis = millis();
  dist = sense();
  if (dist<= distT) {
    // save the last time you trigger the sono 
    triggerMillis = currentMillis;
    relaisState = HIGH;
    }

  if (dist>=distT && currentMillis - triggerMillis <= interval){
    relaisState = HIGH;
  }
  if (dist>=distT && currentMillis - triggerMillis >= interval){
    relaisState = LOW;
    
  }
  
  Serial.print(" ");
  //LSerial.print(currentMillis - triggerMillis);
  Serial.print(" ");
  
  digitalWrite(relaisPin, relaisState);
  
}


// constants won't change. Used here to set a pin number:
const int relaisPin =  6;// the number of the LED pin
const int trigger = 9;  //trigger pin number
const int echo = 8;   //echo pin number


// Variables will change:
int relaisState = LOW;             // ledState used to set the LED
long dauer = 0;                 //traveltime 
long dist = 0;                  // distance

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long triggerMillis = 0;

// constants won't change:
const long interval = 1800;           // interval at which to shut down and up 1800000 = 30 Minuten
const long distT = 200;             // 

void setup() {
  // set the digital pin as output:
  pinMode(relaisPin, OUTPUT);
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);                // Trigger Pin als Ausgang definieren
  pinMode(echo, INPUT);                    // Echo Pin als Eingang defnieren

}

int sense()

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

 

        Serial.print(dist);            // Den Weg in Zentimeter ausgeben

        Serial.println(" cm");               //

 

    delay(10);                             // Nach einer Hunderstelsekunde wiederholen
    return dist;

 

}
void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();
  dist = sense();
  if (dist<= distT) {
    // save the last time you trigger the sono 
    triggerMillis = currentMillis;
    relaisState = HIGH;
 
    }
  if (dist>=distT && currentMillis - triggerMillis >= interval){
    relaisState = LOW;
    
  }
  if (dist>=distT && currentMillis - triggerMillis <= interval){
    relaisState = HIGH;
  }
  Serial.print(" ");
  Serial.print(currentMillis - triggerMillis);
  Serial.print(" ");
  
  digitalWrite(relaisPin, relaisState);

}

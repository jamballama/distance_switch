int trigger=9;                               // Der Trigger Pin

int echo=8;                                  // Der Echo Pin

long dauer=0;                                // Hier wird die Zeitdauer abgespeichert

                                             // die die Ultraschallwelle braucht

                                             // um zum Sensor zurückzukommen

long entfernung=0;                           // Hier wird die Entfernung vom 

                                             // Hindernis abgespeichert

 

void setup()

 

{

    Serial.begin(9600);                      // Die serielle Kommunikation starten

    pinMode(trigger, OUTPUT);                // Trigger Pin als Ausgang definieren

    pinMode(echo, INPUT);                    // Echo Pin als Eingang defnieren

}

 

void loop()

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

    entfernung = (dauer/2) / 29.1;           // Die Zeit in den Weg in Zentimeter umrechnen

 

        Serial.print(entfernung);            // Den Weg in Zentimeter ausgeben

        Serial.println(" cm");               //

 

    delay(10);                             // Nach einer Sekunde wiederholen

 

}

 

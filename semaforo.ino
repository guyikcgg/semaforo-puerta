#include <HCSR04.h>

byte triggerPin = 11;
byte echoPin = 12;
const int ledPin =  5;
int sensorPin = A0;
int sensorValue = 0;

void setup () {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
  pinMode(ledPin, OUTPUT);
}

void loop () {
  sensorValue = analogRead(sensorPin);

  Serial.print("2: ");
  Serial.print(sensorValue);
  
  Serial.println("---");

  if (sensorValue > 800) {
    /* The door is closed */

    double* distances = HCSR04.measureDistanceCm();
      
    Serial.print("1: ");
    Serial.print(distances[0]);
    Serial.println(" cm");
    
    if ((distances[0] > 4.0) && (distances[0] < 15.0)) {
      /* The closet's door is open */
      digitalWrite(ledPin, HIGH);
    }
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  delay(250);
}
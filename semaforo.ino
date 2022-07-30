#include <HCSR04.h>
#include "LowPower.h"

byte triggerPin = 11;
byte echoPin = 12;
const int ledPin =  5;
int sensorPin = 10;
int sensorValue = 0;

void setup () {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop () {
  sensorValue = digitalRead(sensorPin);

  Serial.print("2: ");
  Serial.print(sensorValue);
  
  Serial.println("---");

  if (sensorValue) {
    /* The door is closed */

    double* distances = HCSR04.measureDistanceCm();
      
    Serial.print("1: ");
    Serial.print(distances[0]);
    Serial.println(" cm");
    
    if ((distances[0] > 4.0) && (distances[0] < 15.0)) {
      /* The closet's door is open */
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    delay(333);
  } else {
    digitalWrite(ledPin, LOW);
    //LowPower.idle(SLEEP_1S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
    //            SPI_OFF, USART0_OFF, TWI_OFF);
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  }
}

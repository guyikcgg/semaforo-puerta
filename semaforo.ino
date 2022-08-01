#include <HCSR04.h>
#include "LowPower.h"

#define DEBUG false

const byte sr04TriggerPin = 11;
const byte sr04EchoPin = 12;
const byte sr04GndPin = 8;
const byte ledPin =  5;
const byte cny70Pin = 10;
const byte cny70GndPin = 9;

void setup () {
#if DEBUG
  Serial.begin(9600);
#endif
  HCSR04.begin(sr04TriggerPin, sr04EchoPin);
  pinMode(ledPin, OUTPUT);
  pinMode(cny70Pin, INPUT);
  pinMode(cny70GndPin, INPUT);
  pinMode(sr04GndPin, INPUT);
}

void loop () {
  bool cny70Value = LOW;
  
  // Turn on the cny70 and read the value
  pinMode(cny70GndPin, OUTPUT);
  digitalWrite(cny70GndPin, LOW);
  delay(1);
  cny70Value = digitalRead(cny70Pin);
  pinMode(cny70GndPin, INPUT);

#if DEBUG
  Serial.print("cny70: ");
  Serial.print(cny70Value);
#endif

  if (cny70Value) {
    /* The door is closed */
    double* distances = NULL;

    pinMode(sr04GndPin, OUTPUT);
    digitalWrite(sr04GndPin, LOW);
    delay(1);
    distances = HCSR04.measureDistanceCm();
    pinMode(sr04GndPin, INPUT);

#if DEBUG
    Serial.print("sr04: ");
    Serial.print(distances[0]);
    Serial.println(" cm");
#endif
    
    if ((distances[0] > 4.0) && (distances[0] < 15.0)) {
      /* The closet's door is open */
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  } else {
    digitalWrite(ledPin, LOW);
    //LowPower.idle(SLEEP_1S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
    //            SPI_OFF, USART0_OFF, TWI_OFF);
  }
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
}

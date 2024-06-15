#include <Servo.h>
#include <LowPower.h>

const int soilMoisturePin = A0;
const int thresholdPotPin = A1;
const int pumpPin = 9;
const int buttonPin = 2;
const int buzzerPin = 3;
const int ledPin = 4;

Servo servoMotor;
int customThreshold = 300;

void setup() {
  pinMode(soilMoisturePin, INPUT);
  pinMode(thresholdPotPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  servoMotor.attach(10);
  servoMotor.write(0);

  attachInterrupt(digitalPinToInterrupt(buttonPin), wakeUp, FALLING);
}

void loop() {
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

  int soilMoisture = analogRead(soilMoisturePin);
  int potValue = analogRead(thresholdPotPin);
  customThreshold = map(potValue, 0, 1023, 200, 800);

  if (soilMoisture < customThreshold) {
    digitalWrite(pumpPin, HIGH);
    servoMotor.write(90);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(5000);           // Watering duration
    digitalWrite(pumpPin, LOW);
    servoMotor.write(0);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(1000); // Check soil moisture every second
}

void wakeUp() {
  // Interrupt service routine to wake up the microcontroller
}

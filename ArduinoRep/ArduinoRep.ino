#include <Wire.h>
#include "ultrasonicSensor.h"

const int trigPin1 = 3;
const int echoPin1 = 2;

const int trigPin2 = 5;
const int echoPin2 = 4;

long duration1,duration2;
int distanceCm1,distanceCm2;

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  Serial.begin(9600);
  Serial.println();
  Serial.println("Start program");
  Serial.println();
}
void loop() {
  duration1 = checkDuration(trigPin1, echoPin1);
  duration2 = checkDuration(trigPin2, echoPin2);
  
  
  distanceCm1 = checkDistance(duration1);
  distanceCm2 = checkDistance(duration2);

  printDistanceConsole(distanceCm1 , 1);
  printDistanceConsole(distanceCm2 , 2);
  
  delay(1000);
}

long checkDuration(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

int checkDistance(int duration){
  return duration *  0.0340 / 2;
}

void printDistanceConsole(int printVal, int sensorNr){
  Serial.print("Distance of sensor" + String(sensorNr) + " : ");
  Serial.print(printVal);
  Serial.println(" cm");
  Serial.println();
}

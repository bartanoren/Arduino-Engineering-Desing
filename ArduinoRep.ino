#include <Wire.h>

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
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  
  distanceCm1 = duration1 * 0.0340 / 2;
  distanceCm2 = duration2 * 0.0340 / 2;
  Serial.print("Distance of sensor 1: ");
  Serial.print(distanceCm1);
  Serial.println(" cm");
  Serial.print("Distance of sensor 2: ");
  Serial.print(distanceCm2);
  Serial.println(" cm");
  Serial.println();
  delay(1000);
}

#include <Wire.h>
#include "ultrasonicSensor.h"
#include "HX711.h"
#include <LiquidCrystal.h>

#define calibration_factor -39000

#define DOUTR  3
#define CLKR  2

#define DOUTL  5
#define CLKL  4

HX711 scaleL;
HX711 scaleR;

const int trigPin1 = 0;
const int echoPin1 = 1;

const int trigPin2 = 6;
const int echoPin2 = 7;

long duration1,duration2;
long distanceCm1,distanceCm2;

long leftBot;
long rightBot;

bool debug = false;

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int Contrast=1;
long distancePrev1 = 0;
long distancePrev2 = 0;

bool stopBool = true;
bool startVar = true;


void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  scaleL.begin(DOUTL, CLKL);
  scaleL.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scaleL.tare();
  
  scaleR.begin(DOUTR, CLKR);
  scaleR.set_scale(calibration_factor);
  scaleR.tare();

  analogWrite(6,Contrast); 
  lcd.begin(16, 2);


  
  Serial.begin(9600);
  Serial.println();
  Serial.println("Start program");
  Serial.println();
}



void loop() {

/* leftbot is the left bottom of the user while sitting and rightBot is the right */
  leftBot = scaleR.get_units();
  rightBot = scaleL.get_units();

  if (startVar){
    while ((leftBot < 5) and (rightBot < 5)){
      lcd.print("Please sit on the chair");
      leftBot = scaleR.get_units();
      rightBot = scaleL.get_units();
    }
    lcd.clear();
    startVar = false;
  }

  while (abs(leftBot - rightBot) > 1.5) {
    checkBottom(leftBot, rightBot);
    leftBot = scaleR.get_units();
    rightBot = scaleL.get_units();
  }
  lcd.clear();
  
  distanceCm1 = measure(trigPin1, echoPin1);
  distanceCm2 = measure(trigPin2, echoPin2);

  if (stopBool) {
    distancePrev1 = distanceCm1;
    distancePrev2 = distanceCm2;
    stopBool = false;
    }
    
    while (distanceCm1 > distancePrev1) {
      checkDistance1(distanceCm1, distancePrev1);
      distancePrev1 = distanceCm1;
      distanceCm1 = measure(trigPin1, echoPin1);
      
    }
    lcd.clear();

    while (distanceCm2 > distancePrev2) {
      checkDistance2(distanceCm2, distancePrev2);
      distancePrev2 = distanceCm2;
      distanceCm2 = measure(trigPin2, echoPin2);
    }
    lcd.clear();
    
    if (debug){
    printDebug();
    }
}


void checkBottom(float left, float right){
   if (left > (right + 1.5)){
    /*
     * lcd display to say too much pressure to the left so sit to the right
     */
       lcd.clear();
     lcd.print("Please sit more to the right");
  }
  
  if (right > (left + 1.5)){
    /*
     * lcd display to say too much pressure to the right so sit to the left
     */
       lcd.clear();
     lcd.print("Please sit more to the left");
  }

}

void checkDistance1(long current, long prev){
    while (current > (prev * 2)){
      /*
       * lcd display to say put your shoulders a bit to the back
       */
       lcd.clear();
       lcd.print("Put your shoulders a bit back");
    }
    while (current > (prev * 5)){
      /*
       * lcd display to say your shoulders are too much to the front
       */
       lcd.clear();
     lcd.print("Shoulders are too forward");
    }
}

void checkDistance2(long current, long prev){
    while (current > (prev * 2)){
       lcd.clear();
       lcd.print("Put your back closer to chair");
    }
    while (current > (prev * 5)){
       lcd.clear();
     lcd.print("Stop lying on the chair");
    }
}

long measure(int trigPin, int echoPin){
  return checkDistance(checkDuration(trigPin, echoPin));
}




void printDebug(){
  
  printDistanceConsole(distanceCm1 , 1);
  printDistanceConsole(distanceCm2 , 2);

  Serial.println("");
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
  Serial.print("Distance of sensor " + String(sensorNr) + " : ");
  Serial.print(printVal);
  Serial.print(" cm");
  Serial.println();
}

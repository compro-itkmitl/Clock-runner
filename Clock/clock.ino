#include <LiquidCrystal_I2C.h>
#include "Wire.h"
#include "SPI.h"
#include "RTClib.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 RTC;

/*////////////////////*/

/*ตั้งชื่อ PIN ให้จำได้*/

//ของultrasonic

const int trigPin = 9; 
const int echoPin = 10;
long duration;
int distance;

/*//////////////////*/

/*//////////////////*/

//ของมอเตอร์

// Motor A

int backwardA = 2;
int forwardA = 3;
int speedPinA = 6;
// Motor B
int backwardB = 4;
int forwardB = 5;
int speedPinB = 7;

/*///////////////////*/
//ลำโพง
/*///////////////////*/
const int buzzer = 13;
void timer(DateTime now);


void setup () {
  /*sonic+motor*/
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
pinMode(backwardA,OUTPUT);
pinMode(forwardA,OUTPUT);
pinMode(speedPinA,OUTPUT);
pinMode(backwardB,OUTPUT);
pinMode(forwardB,OUTPUT);
pinMode(speedPinB,OUTPUT);
  /*sonic+motor*/
 

  /*buzzer setup */
  pinMode(buzzer, OUTPUT);
  /*buzzer setup */
 
  lcd.begin();
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  //RTC.adjust(DateTime(__DATE__, __TIME__)); /*เอาไว้ตั้งเวลาใหม่*/

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  DateTime now = RTC.now();
  /* ตั้งเวลา ในตัวอย่างนี้ เซตค่าเป็นเวลา 23:09 ถ้าถึงเวลานี้จะให้ทำงานที่ฟังก์ชัน */
    RTC.setAlarm1Simple(18, 9);
   if (RTC.checkIfAlarm(1)) {
   Serial.println("Alarm Triggered");
   }
  RTC.setAlarm1Simple(18, 9);

  RTC.turnOnAlarm(1);

  if (RTC.checkAlarmEnabled(1)) {
    Serial.println("Alarm Enabled");
  }

}

void loop () {
  DateTime now = RTC.now();
  timer(now);
  
  if (RTC.checkIfAlarm(1)){
    while(1){
      DateTime now = RTC.now();
  timer(now);
    /*buzzer*/
  tone(buzzer, 1000);
  delay(500);
  noTone(buzzer);
  tone(buzzer, 500);
  delay(500);
  noTone(buzzer);
  tone(buzzer, 700);
  delay(500);
  noTone(buzzer);
  tone(buzzer, 1000);
  delay(500);
  noTone(buzzer);
  /*buzzer*/
      /*sonic+motor*/
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  Serial.print(distance);
    /*sonic+motor*/
    Serial.print("a");
    if (distance > 60)
  {
  // Motor A

    analogWrite(speedPinA, 255);
    digitalWrite(backwardA, LOW);
    digitalWrite(forwardA, HIGH);


  // Motor B

    analogWrite(speedPinB, 255);
    digitalWrite(backwardB, LOW);
    digitalWrite(forwardB, HIGH);
  }

   if (distance <= 60)
  {
      // Motor A

    analogWrite(speedPinA, 255);
    digitalWrite(backwardA, HIGH);
    digitalWrite(forwardA, LOW);


  // Motor B

    analogWrite(speedPinB, 255);
    digitalWrite(backwardB, LOW);
    digitalWrite(forwardB, HIGH);
  }
    delay(400);
}
}
}

void timer(DateTime now){
  lcd.setCursor(0,0);
  lcd.print("Date: ");
  lcd.print(now.year(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.day(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
}


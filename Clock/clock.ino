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
long durationfront, durationleft, durationright;
int distancefront, distanceleft, distanceright;


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

/*//////////////////////////*/
void clock();
void clock(){
  RTC.begin();
  //RTC.adjust(DateTime(__DATE__, __TIME__)); /*เอาไว้ตั้งเวลาใหม่*/
  DateTime now = RTC.now();
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
    RTC.setAlarm1Simple(21, 53);
   if (RTC.checkIfAlarm(1)) {
   Serial.println("Alarm Triggered");
   }
  RTC.setAlarm1Simple(21, 53);

  RTC.turnOnAlarm(1);

  if (RTC.checkAlarmEnabled(1)) {
    Serial.println("Alarm Enabled");
  }

}

void loop () {
  clock();
  if (RTC.checkIfAlarm(1)){
    while(1){
  clock();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationfront = pulseIn(echoPin, HIGH);
  distancefront= durationfront*0.034/2;
  
  durationleft = pulseIn(echoPin, HIGH);
  distanceleft= distanceleft*0.034/2;
  
  durationright = pulseIn(echoPin, HIGH);
  distanceright= distanceright*0.034/2;

    if (distancefront > 70)
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

   if (distancefront <= 70)
  {
    if (distanceleft > distanceright){
      // Motor A

    analogWrite(speedPinA, 255);
    digitalWrite(backwardA, HIGH);
    digitalWrite(forwardA, LOW);


      // Motor B

    analogWrite(speedPinB, 255);
    digitalWrite(backwardB, LOW);
    digitalWrite(forwardB, HIGH);
  }
   if (distanceright > distanceleft){
    analogWrite(speedPinA, 255);
    digitalWrite(backwardA, LOW);
    digitalWrite(forwardA, HIGH);


      // Motor B

    analogWrite(speedPinB, 255);
    digitalWrite(backwardB, HIGH);
    digitalWrite(forwardB, LOW);
    }
   }
    delay(400);
}
}
}

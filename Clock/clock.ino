#include <LiquidCrystal_I2C.h>
#include "Wire.h"
#include "SPI.h"
#include "RTClib.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 RTC;

// ตั้งค่าตัวแปล buzzer เป็ น pin 13

const int buzzer1 = 13;
const int buzzer2 = 12;

// เซ็ต pin ultrasound

const int trig = 9; 
const int echo = 10;
long duration;
int distance;

// เซ็ต pin มอเตอร์

int backwardA = 2; // ล้อ A ไปข้างหลัง
int forwardA = 3; // ล้อ A ไปข้างหน้า
int speedPinA = 6; //ความเร็วล้อ A
int backwardB = 4; // ล้อ B ไปข้างหลัง
int forwardB = 5; // ล้อ B ไปข้างหน้า
int speedPinB = 7; //ความเร็วล้อ B


void timer(DateTime now); //ประกาศสร้างฟังก์ชั่นเพื่อ print เวลากับวันที่ ท่ LCD


void setup () {
pinMode(trig, OUTPUT); // pin นี้เป็นตัวส่งคลื่น
pinMode(echo, INPUT); // pin นี้เป็นตัวรับคลื่นที่สะท้อนกลับมา
Serial.begin(115200); // ประกาศเริ่ม Serial Monitor เพื่อเช็คค่าม หรือสถานะบางค่า
lcd.begin();
Wire.begin();
RTC.begin();

// มอเตอร์ A ตั้งเป็น pin ปล่อยไฟ
pinMode(backwardA,OUTPUT);
pinMode(forwardA,OUTPUT);
pinMode(speedPinA,OUTPUT);
pinMode(backwardB,OUTPUT);
pinMode(forwardB,OUTPUT);
pinMode(speedPinB,OUTPUT);

// ตั้ง pin buzzer เป็นตัวปล่อยไฟ
pinMode(buzzer1, OUTPUT);
pinMode(buzzer2, OUTPUT);

//RTC.adjust(DateTime(__DATE__, __TIME__)); //ใช้เพื่อตั้งเวลาใหม่ พอตั้งเสร็จให้ Code ลงบอร์ด แล้วปิดคำสั่งนี้แล้วอัพ code อีกครั้ง

DateTime now = RTC.now();
RTC.setAlarm1Simple(23, 46); // ตั้งเวลาปลุก(ชั่วโมง, นาที)
RTC.turnOnAlarm(1); // เปิด-ปิด นาฬิกาปลุก (1: เปิด, 2: ปิด)
}

void loop () {
  DateTime now = RTC.now(); 
  timer(now); // แสดงเวลาและวันที่

  //ถ้าถึงเวลาปลุก ทำ condition นี้
  
  if (RTC.checkIfAlarm(1)){
    while(1){ //ทำไปเรื่อยๆจนกว่าจะยอมลุกมาปิดนาฬิกา 
      DateTime now = RTC.now();
      timer(now);
      tone(buzzer1, 1000);
      tone(buzzer2, 1000);
      //digitalWrite(buzzer1, LOW);
      //noTone(buzzer2);
      //digitalWrite(buzzer1, HIGH);
      //tone(buzzer2, 500);
      //digitalWrite(buzzer1, LOW);
      //noTone(buzzer2);
      //digitalWrite(buzzer1, HIGH);
      //tone(buzzer2, 700);
      //digitalWrite(buzzer1, LOW);
      //noTone(buzzer2);
      
      //กำหนดความยาวคลื่น

      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
      duration = pulseIn(echo, HIGH); // คำนวณช่วงเวลาไป-กลับของคลื่น
      distance= duration*0.034/2; // นำช่วงเวลามาคำนวณระยะทาง

        if (distance > 60) // ถ้าด้านหน้ามีระยะทางมากพอ ให้วิ่งไปต่อ
      {

      // ล้อ A
        analogWrite(speedPinA, 255);
        digitalWrite(backwardA, LOW);
        digitalWrite(forwardA, HIGH);


      // ล้อ B
        analogWrite(speedPinB, 255);
        digitalWrite(backwardB, LOW);
        digitalWrite(forwardB, HIGH);
      }

       if (distance <= 60) // ถ้าด้านหน้ามีระยะทางไม่พอ ให้หมุนทางทางใหม่
      {

       // ล้อ A
        analogWrite(speedPinA, 255);
        digitalWrite(backwardA, HIGH);
        digitalWrite(forwardA, LOW);


      // ล้อ B
        analogWrite(speedPinB, 255);
        digitalWrite(backwardB, LOW);
        digitalWrite(forwardB, HIGH);
      }

    delay(400);
}
}
}

// ฟังก์ชั่น print เวลาและวันที่

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


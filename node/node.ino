#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define WIFI_SSID "SSID ของ WIFI "
#define WIFI_PASSWORD "Password ของ WIFI "
#define FIREBASE_HOST "clock-runner.firebaseio.com"
#define FIREBASE_AUTH "3vo55UtUfzJURQhGPNBeDvxkDznAHa4T5IsaWWvS"
void setup() {
Serial.begin(9600);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
pinMode(D1, OUTPUT);
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
RTC.setAlarm1Simple(Firebase.getInt("hour"), Firebase.getInt("min"));
RTC.turnOnAlarm(Firebase.getInt("onoff"));
}
void loop() {
}


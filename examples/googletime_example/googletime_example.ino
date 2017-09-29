#include <ESP8266WiFi.h>
#include "GoogleTime.h"

// optional timeout
// #define GOOGLETIME_TIMEOUT 1000

#define MY_SSID "......"
#define PASSWORD "......"

void setup() {
  Serial.begin(115200);
  WiFi.begin(MY_SSID, PASSWORD);
}//setup

const char* weekDays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void loop() {
  int weekDay, day, month, year, hour, minute, second;
  Serial.println("updating time...");
  if (googleTime(weekDay, day, month, year, hour, minute, second)) {
    Serial.println(String("It is ") + hour + (minute < 10 ? ":0" : ":") + minute + (second < 10 ? ":0" : ":") + second
                   + " GMT on " + weekDays[weekDay - 1] + ", " + months[month - 1] + " " + day + ", " + year);           
  } else {
    Serial.println("update failed");
  }//endif

  delay(15000);
}//loop

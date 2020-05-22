// Date, Time and Alarm functions using a DS3231 RTC connected via I2C and Wire lib

#include "Wire.h"
#include "SPI.h"  // not used here, but needed to prevent a RTClib compile error
#include "RTClib.h"


#include <LiquidCrystal_I2C.h>

RTC_DS3231 RTC;
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void display_time(){
    DateTime now = RTC.now();
    int year_now = now.year();
    int month_now = now.month();
    int day_now = now.day();
    int hour_now = now.hour();
    int minute_now = now.minute();
    int second_now = now.second();
    float temp_now = RTC.getTemperature();
 
  lcd.setCursor(0, 3);
  lcd.print(hour_now, DEC);
  lcd.print(":");

  if (minute_now < 10)
  {
    Serial.print("0");
  }

  lcd.print(minute_now, DEC);
  lcd.print(":");
  if (second_now < 10)
  {
    Serial.print("0");
  }
  lcd.print(second_now, DEC);
  lcd.print(" ");
  lcd.print(day_now, DEC);
  lcd.print("/");
  lcd.print(month_now, DEC);
  lcd.print("/");
  lcd.print(year_now, DEC);

  lcd.setCursor(15, 0);
  lcd.print(temp_now, 1);
  lcd.print("C");
}



void setup () {

  Serial.begin(9600);
  
  Wire.begin();
  
  RTC.begin();

  lcd.begin();
  lcd.print(" Welcome To System  ");
  lcd.setCursor(0, 1);
  lcd.print(" Designed By B.S.E  ");
  delay(3000);
  lcd.clear();

  
//  RTC.adjust(DateTime(__DATE__, __TIME__));
//  if (! RTC.isrunning()) {
//    Serial.println("RTC is NOT running!");
//    // following line sets the RTC to the date & time this sketch was compiled
//    RTC.adjust(DateTime(__DATE__, __TIME__));
//  }

}

void loop () {
  
  DateTime now = RTC.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);

  Serial.println();
  Serial.print("Tempeature = ");
  Serial.print(RTC.getTemperature()); // คำสั่งดึงอุณหภูมิออกมาแสดง
  Serial.println(" C");

  Serial.println("By ArduinoALL");
  Serial.println();

  display_time();

  delay(1000);
}

#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);

RTC_DS3231 RTC;

unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 250;           // interval at which to blink (milliseconds)

int year_now = 0;//now.year();
int month_now = 0;//now.month();
int day_now = 0;//now.day();
int hour_now = 0;//now.hour();
int minute_now = 0;//now.minute();
int second_now = 0;//now.second();

char program1_ctl_bit = 0;
char program2_ctl_bit = 0;
char program3_ctl_bit = 0;
char program4_ctl_bit = 0;

char ry1_status_bit = 0;
char ry2_status_bit = 0;
char ry3_status_bit = 0;
char ry4_status_bit = 0;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program1_on_hour = 4;
int program1_on_minute = 19;
int program1_on_second = 0;
//----------------------------------//
int program1_off_hour = 4;
int program1_off_minute = 22;
int program1_off_second = 0;
//----------------------------------//
int program1_ctl_op = 4;
//*********************************//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program2_on_hour = 3;
int program2_on_minute = 14;
int program2_on_second = 15;
//----------------------------------//
int program2_off_hour = 3;
int program2_off_minute = 16;
int program2_off_second = 17;
//----------------------------------//
int program2_ctl_op = 2;
//*********************************//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program3_on_hour = 3;
int program3_on_minute = 14;
int program3_on_second = 15;
//----------------------------------//
int program3_off_hour = 3;
int program3_off_minute = 16;
int program3_off_second = 17;
//----------------------------------//
int program3_ctl_op = 3;
//*********************************//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program4_on_hour = 3;
int program4_on_minute = 14;
int program4_on_second = 15;
//----------------------------------//
int program4_off_hour = 3;
int program4_off_minute = 16;
int program4_off_second = 17;
//----------------------------------//
int program4_ctl_op = 1;
//*********************************//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void control_relay(){
  Serial.print(hour_now);
  Serial.print(":");
  Serial.print(minute_now);
  Serial.print(":");
  Serial.print(second_now);
  Serial.println("");
  
  if((hour_now==program1_on_hour) && (minute_now==program1_on_minute) && (second_now >= program1_on_second) && (program1_ctl_bit == 0)){
    Serial.print("Program 1 Control Output ");
    switch(program1_ctl_op){
      case 1: Serial.println("RY 1 ON"); ry1_status_bit = 1; break;
      case 2: Serial.println("RY 2 ON"); ry2_status_bit = 1;  break;
      case 3: Serial.println("RY 3 ON"); ry3_status_bit = 1;  break;
      case 4: Serial.println("RY 4 ON"); ry4_status_bit = 1;  break;
    }
    program1_ctl_bit = 1;
  }

  if( (hour_now==program1_off_hour) && (minute_now==program1_off_minute) && (second_now >= program1_off_second) && (program1_ctl_bit == 1)){
    Serial.print("Program 1 Control Output ");
    switch(program1_ctl_op){
      case 1: Serial.println("RY 1 OFF"); ry1_status_bit = 0; break;
      case 2: Serial.println("RY 2 OFF"); ry2_status_bit = 0; break;
      case 3: Serial.println("RY 3 OFF"); ry3_status_bit = 0; break;
      case 4: Serial.println("RY 4 OFF"); ry4_status_bit = 0; break;
    }
    program1_ctl_bit = 0;
  }

  if(ry1_status_bit == 1){
    lcd.setCursor(0, 1);
    lcd.print("RY1:ON    ");
  }else if (ry1_status_bit == 0){
    lcd.setCursor(0, 1);
    lcd.print("RY1:OFF   ");
  }
  if(ry2_status_bit == 1){
    lcd.setCursor(0, 2);
    lcd.print("RY2:ON    ");
  }else if (ry2_status_bit == 0){
    lcd.setCursor(0, 2);
    lcd.print("RY2:OFF   ");
  }
  if(ry3_status_bit == 1){
    lcd.setCursor(10, 1);
    lcd.print("RY3:ON    ");
  }else if (ry3_status_bit == 0){
    lcd.setCursor(10, 1);
    lcd.print("RY3:OFF   ");
  }
  if(ry4_status_bit == 1){
    lcd.setCursor(10, 2);
    lcd.print("RY4:ON    ");
  }else if (ry4_status_bit == 0){
    lcd.setCursor(10, 2);
    lcd.print("RY4:OFF   ");
  }
  
}


void display_time(){
  DateTime now = RTC.now();
  year_now = now.year();
  month_now = now.month();
  day_now = now.day();
  hour_now = now.hour();
  minute_now = now.minute();
  second_now = now.second();
    
  float temp = RTC.getTemperature();
  lcd.setCursor(0, 0);
  lcd.print(" SMART PUMPs ");
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C");

  
  lcd.setCursor(0, 3);
  if (hour_now < 10)
  {
    lcd.print("0");
  }
  lcd.print(hour_now, DEC);
  lcd.print(":");
  if (minute_now < 10)
  {
    lcd.print("0");
  }
  lcd.print(minute_now, DEC);
  lcd.print(":");
  if (second_now < 10)
  {
    lcd.print("0");
  }
  lcd.print(second_now, DEC);
  lcd.print("  ");
  if (day_now < 10)
  {
    lcd.print("0");
  }
  lcd.print(day_now, DEC);
  lcd.print("/");
  if (month_now < 10)
  {
    lcd.print("0");
  }
  lcd.print(month_now, DEC);
  lcd.print("/");
  lcd.print(year_now, DEC);
//  delay(500);
}

void setup()
{
	// initialize the LCD
	lcd.begin();
	lcd.print(" Welcome To System  ");
  lcd.setCursor(0, 1);
  lcd.print(" Designed By B.S.E  ");
  Serial.begin(9600);
  Serial.println("");
  Serial.println(" Welcome To System  ");
  Serial.println(" Designed By B.S.E  ");
  Wire.begin();
  delay(1000);
  RTC.begin(); // Init RTC
  delay(1000);

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
  }else{
    Serial.println("Now RTC is running!");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  delay(1000);
  lcd.clear();
}

void loop(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    display_time();
    control_relay();
  }
}

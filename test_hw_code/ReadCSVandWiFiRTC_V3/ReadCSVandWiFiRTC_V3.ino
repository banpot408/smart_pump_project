#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h> //DN_ADD
#define BLYNK_PRINT Serial //DN_ADD

#define RY_4 D0
#define RY_3 D3
#define RY_2 D4
#define RY_1 10

LiquidCrystal_I2C lcd(0x3F, 20, 4);
RTC_DS3231 RTC;
File myFile;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   Config Blynk 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//char auth[] = "fC9Cdjcoj0JzlBcDjTd6IG86Mh3QRkDX"; //DN_ADD
char auth_Debug[] = "fC9Cdjcoj0JzlBcDjTd6IG86Mh3QRkDX"; //DN_ADD Debug
char ssid_Debug[] = "MonOTioN"; //DN_ADD Debug
char pass_Debug[] = "123456789"; //DN_ADD Debug

int nodeState = 0;

WidgetLED STAUS_RY_1(V0);
WidgetLED STAUS_RY_2(V1);
WidgetLED STAUS_RY_3(V2);
WidgetLED STAUS_RY_4(V3);

WidgetLED STATUS_Node(V5);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   variable for Config WiFi
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool WiFiConnected = false;
String WiFi_Config ;
String Timer_Config ;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   Millis variable for using state maching code function
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned long previousMillis = 0;
const long interval = 250;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   RTC Variable
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int year_now = 0;//now.year();
int month_now = 0;//now.month();
int day_now = 0;//now.day();
int hour_now = 0;//now.hour();
int minute_now = 0;//now.minute();
int second_now = 0;//now.second();
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

char program1_ctl_bit = 0;
char program2_ctl_bit = 0;
char program3_ctl_bit = 0;
char program4_ctl_bit = 0;
char program5_ctl_bit = 0;
char program6_ctl_bit = 0;
char program7_ctl_bit = 0;
char program8_ctl_bit = 0;

char ry1_status_bit = 0;
char ry2_status_bit = 0;
char ry3_status_bit = 0;
char ry4_status_bit = 0;

char program1_relay1_output_bit = 0;
char program1_relay2_output_bit = 0;
char program1_relay3_output_bit = 0;
char program1_relay4_output_bit = 0;

char program2_relay1_output_bit = 0;
char program2_relay2_output_bit = 0;
char program2_relay3_output_bit = 0;
char program2_relay4_output_bit = 0;

char program3_relay1_output_bit = 0;
char program3_relay2_output_bit = 0;
char program3_relay3_output_bit = 0;
char program3_relay4_output_bit = 0;

char program4_relay1_output_bit = 0;
char program4_relay2_output_bit = 0;
char program4_relay3_output_bit = 0;
char program4_relay4_output_bit = 0;

char program5_relay1_output_bit = 0;
char program5_relay2_output_bit = 0;
char program5_relay3_output_bit = 0;
char program5_relay4_output_bit = 0;

char program6_relay1_output_bit = 0;
char program6_relay2_output_bit = 0;
char program6_relay3_output_bit = 0;
char program6_relay4_output_bit = 0;

char program7_relay1_output_bit = 0;
char program7_relay2_output_bit = 0;
char program7_relay3_output_bit = 0;
char program7_relay4_output_bit = 0;

char program8_relay1_output_bit = 0;
char program8_relay2_output_bit = 0;
char program8_relay3_output_bit = 0;
char program8_relay4_output_bit = 0;





//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Set Variable for Program Working
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program1_on_hour = 0;
int program1_on_minute = 0;
int program1_on_second = 0;
//----------------------------------//
int program1_off_hour = 0;
int program1_off_minute = 0;
int program1_off_second = 0;
//----------------------------------//
int program1_ctl_op = 0;
//----------------------------------//
int program1_enable = 0;
//*********************************//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program2_on_hour = 0;
int program2_on_minute = 0;
int program2_on_second = 0;
//----------------------------------//
int program2_off_hour = 0;
int program2_off_minute = 0;
int program2_off_second = 0;
//----------------------------------//
int program2_ctl_op = 0;
//----------------------------------//
int program2_enable = 0;
//*********************************//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program3_on_hour = 0;
int program3_on_minute = 0;
int program3_on_second = 0;
//----------------------------------//
int program3_off_hour = 0;
int program3_off_minute = 0;
int program3_off_second = 0;
//----------------------------------//
int program3_ctl_op = 0;
//----------------------------------//
int program3_enable = 0;
//*********************************//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program4_on_hour = 0;
int program4_on_minute = 0;
int program4_on_second = 0;
//----------------------------------//
int program4_off_hour = 0;
int program4_off_minute = 0;
int program4_off_second = 0;
//----------------------------------//
int program4_ctl_op = 0;
//----------------------------------//
int program4_enable = 0;
//*********************************//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program5_on_hour = 0;
int program5_on_minute = 0;
int program5_on_second = 0;
//----------------------------------//
int program5_off_hour = 0;
int program5_off_minute = 0;
int program5_off_second = 0;
//----------------------------------//
int program5_ctl_op = 0;
//----------------------------------//
int program5_enable = 0;
//*********************************//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program6_on_hour = 0;
int program6_on_minute = 0;
int program6_on_second = 0;
//----------------------------------//
int program6_off_hour = 0;
int program6_off_minute = 0;
int program6_off_second = 0;
//----------------------------------//
int program6_ctl_op = 0;
//----------------------------------//
int program6_enable = 0;
//*********************************//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program7_on_hour = 0;
int program7_on_minute = 0;
int program7_on_second = 0;
//----------------------------------//
int program7_off_hour = 0;
int program7_off_minute = 0;
int program7_off_second = 0;
//----------------------------------//
int program7_ctl_op = 0;
//----------------------------------//
int program7_enable = 0;
//*********************************//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*********************************//
int program8_on_hour = 0;
int program8_on_minute = 0;
int program8_on_second = 0;
//----------------------------------//
int program8_off_hour = 0;
int program8_off_minute = 0;
int program8_off_second = 0;
//----------------------------------//
int program8_ctl_op = 0;
//----------------------------------//
int program8_enable = 0;
//*********************************//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

String progran_num = "";
int comma_posi_1 = 0;
int comma_posi_2 = 0;
int comma_posi_3 = 0;
int comma_posi_4 = 0;
int comma_posi_5 = 0;
int comma_posi_6 = 0;
int comma_posi_7 = 0;
int comma_posi_8 = 0;
int comma_posi_9 = 0;


//********************************************************************************************************//
//********************************************************************************************************//
//********************************************************************************************************//



//********************************************************************************************************//
// Prototype Function
//********************************************************************************************************//
void control_relay();
void display_time();
bool readLine(File &f, char* line, size_t maxLen);
//********************************************************************************************************//

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  lcd.begin();
  lcd.print(" Welcome To System  ");
  lcd.setCursor(0, 1);
  lcd.print(" Designed By B.S.E  ");
  Serial.begin(9600);
  Serial.println("");
  Serial.println(" Welcome To System  ");
  Serial.println(" Designed By B.S.E  ");
  delay(1000);

/*
#define RY_1 D0
#define RY_2 D3
#define RY_3 D4
#define RY_4 10
*/

  pinMode(RY_1, OUTPUT);
  pinMode(RY_2, OUTPUT);
  pinMode(RY_3, OUTPUT);
  pinMode(RY_4, OUTPUT);

  digitalWrite(RY_1, HIGH);
  digitalWrite(RY_2, HIGH);
  digitalWrite(RY_3, HIGH);
  digitalWrite(RY_4, HIGH);

  Wire.begin();
  delay(1000);
  RTC.begin(); // Init RTC
  lcd.clear();
  lcd.print("Initial RTC DS3231  ");
  delay(1000);

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    lcd.clear();
    lcd.print("RTC is NOT running! ");
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
  }else{
    Serial.println("Now RTC is running!");
    lcd.clear();
    lcd.print("Now RTC is running! ");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  delay(1000);
  lcd.clear();
  lcd.print("Initial SD card.... ");
  delay(1000);
// long x, y;
  Serial.println();
  Serial.println();
  Serial.print("Initializing SD card...");
  if (!SD.begin(D8)) {
    Serial.println("initialization failed!");
    lcd.clear();
    lcd.print("init SD Card failed!");
    while(1);
    return;
  }
  Serial.println("initialization done.");
  lcd.clear();
  lcd.print("initialization done.");
  delay(1000);
  lcd.clear();
  lcd.print("Reading Config File ");

  // re-open the file for reading:
  myFile = SD.open("sys_config.csv", FILE_READ);
  if (!myFile) {
    Serial.println("error open file sys_config.csv");
    delay(1000);
    lcd.clear();
    lcd.print("error open sys_config.csv ");
    while(1);
    return;
  }
  delay(1000);
  lcd.clear();
  lcd.print("Read file complete! ");
  char line[150];
  
  Serial.print("line 1 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  
  Serial.print("line 2 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  
  WiFi_Config = line;
  
  Serial.print("WiFi_Config Value : ");
  Serial.println(WiFi_Config);
  
  Serial.print("WiFi_Config comma_posi_1 : ");
  comma_posi_1 = WiFi_Config.indexOf(",");
  Serial.println(comma_posi_1);
  Serial.println(WiFi_Config.substring(0, comma_posi_1));
  const String ssid = WiFi_Config.substring(0, comma_posi_1);

  Serial.print("WiFi_Config comma_posi_2 : ");
  comma_posi_2 = WiFi_Config.indexOf(",", comma_posi_1+1);
  Serial.println(comma_posi_2);

  Serial.println(WiFi_Config.substring(comma_posi_1+1, comma_posi_2));  
  const String pass = WiFi_Config.substring(comma_posi_1+1, comma_posi_2);

  delay(1000);
  lcd.clear();
  lcd.print("  Read WiFi Config  ");

  Serial.print("line 3 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);



/////////////////////////////////////////////////////////////////////////////////////////////// Read Line 4
  Serial.print("Config Timer Program 1 line 4 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  Timer_Config = line;
  Serial.print("Timer_Config Value : ");
  Serial.println(Timer_Config);
  comma_posi_1 = Timer_Config.indexOf(",");
  comma_posi_2 = Timer_Config.indexOf(",", comma_posi_1+1);
  comma_posi_3 = Timer_Config.indexOf(",", comma_posi_2+1);
  comma_posi_4 = Timer_Config.indexOf(",", comma_posi_3+1);
  comma_posi_5 = Timer_Config.indexOf(",", comma_posi_4+1);
  comma_posi_6 = Timer_Config.indexOf(",", comma_posi_5+1);
  comma_posi_7 = Timer_Config.indexOf(",", comma_posi_6+1);
  comma_posi_8 = Timer_Config.indexOf(",", comma_posi_7+1);
  comma_posi_9 = Timer_Config.indexOf(",", comma_posi_8+1);

  progran_num = Timer_Config.substring(0, comma_posi_1);
  String program1_on_hour_st = Timer_Config.substring(comma_posi_1+1, comma_posi_2);
  String program1_on_minute_st = Timer_Config.substring(comma_posi_2+1, comma_posi_3);
  String program1_on_second_st = Timer_Config.substring(comma_posi_3+1, comma_posi_4);
  String program1_off_hour_st = Timer_Config.substring(comma_posi_4+1, comma_posi_5);
  String program1_off_minute_st = Timer_Config.substring(comma_posi_5+1, comma_posi_6);
  String program1_off_second_st = Timer_Config.substring(comma_posi_6+1, comma_posi_7);
  String program1_ctl_op_st = Timer_Config.substring(comma_posi_7+1, comma_posi_8);
  String program1_enable_st = Timer_Config.substring(comma_posi_8+1, comma_posi_9);

  program1_on_hour = program1_on_hour_st.toInt();
  program1_on_minute = program1_on_minute_st.toInt();
  program1_on_second = program1_on_second_st.toInt();
  program1_off_hour = program1_off_hour_st.toInt();
  program1_off_minute = program1_off_minute_st.toInt();
  program1_off_second = program1_off_second_st.toInt();
  program1_ctl_op = program1_ctl_op_st.toInt();
  program1_enable = program1_enable_st.toInt();
/////////////////////////////////////////////////////////////////////////////////////////////// End Read Line 4

/////////////////////////////////////////////////////////////////////////////////////////////// Read Line 5
  Serial.print("Config Timer Program 2 line 5 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  Timer_Config = line;
  Serial.print("Timer_Config Value : ");
  Serial.println(Timer_Config);
  comma_posi_1 = Timer_Config.indexOf(",");
  comma_posi_2 = Timer_Config.indexOf(",", comma_posi_1+1);
  comma_posi_3 = Timer_Config.indexOf(",", comma_posi_2+1);
  comma_posi_4 = Timer_Config.indexOf(",", comma_posi_3+1);
  comma_posi_5 = Timer_Config.indexOf(",", comma_posi_4+1);
  comma_posi_6 = Timer_Config.indexOf(",", comma_posi_5+1);
  comma_posi_7 = Timer_Config.indexOf(",", comma_posi_6+1);
  comma_posi_8 = Timer_Config.indexOf(",", comma_posi_7+1);
  comma_posi_9 = Timer_Config.indexOf(",", comma_posi_8+1);

  progran_num = Timer_Config.substring(0, comma_posi_1);
  String program2_on_hour_st = Timer_Config.substring(comma_posi_1+1, comma_posi_2);
  String program2_on_minute_st = Timer_Config.substring(comma_posi_2+1, comma_posi_3);
  String program2_on_second_st = Timer_Config.substring(comma_posi_3+1, comma_posi_4);
  String program2_off_hour_st = Timer_Config.substring(comma_posi_4+1, comma_posi_5);
  String program2_off_minute_st = Timer_Config.substring(comma_posi_5+1, comma_posi_6);
  String program2_off_second_st = Timer_Config.substring(comma_posi_6+1, comma_posi_7);
  String program2_ctl_op_st = Timer_Config.substring(comma_posi_7+1, comma_posi_8);
  String program2_enable_st = Timer_Config.substring(comma_posi_8+1, comma_posi_9);

  program2_on_hour = program2_on_hour_st.toInt();
  program2_on_minute = program2_on_minute_st.toInt();
  program2_on_second = program2_on_second_st.toInt();
  program2_off_hour = program2_off_hour_st.toInt();
  program2_off_minute = program2_off_minute_st.toInt();
  program2_off_second = program2_off_second_st.toInt();
  program2_ctl_op = program2_ctl_op_st.toInt();
  program2_enable = program2_enable_st.toInt();
/////////////////////////////////////////////////////////////////////////////////////////////// End Read Line 5

/////////////////////////////////////////////////////////////////////////////////////////////// Read Line 6
  Serial.print("Config Timer Program 3 line 6 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  Timer_Config = line;
  Serial.print("Timer_Config Value : ");
  Serial.println(Timer_Config);
  comma_posi_1 = Timer_Config.indexOf(",");
  comma_posi_2 = Timer_Config.indexOf(",", comma_posi_1+1);
  comma_posi_3 = Timer_Config.indexOf(",", comma_posi_2+1);
  comma_posi_4 = Timer_Config.indexOf(",", comma_posi_3+1);
  comma_posi_5 = Timer_Config.indexOf(",", comma_posi_4+1);
  comma_posi_6 = Timer_Config.indexOf(",", comma_posi_5+1);
  comma_posi_7 = Timer_Config.indexOf(",", comma_posi_6+1);
  comma_posi_8 = Timer_Config.indexOf(",", comma_posi_7+1);
  comma_posi_9 = Timer_Config.indexOf(",", comma_posi_8+1);

  progran_num = Timer_Config.substring(0, comma_posi_1);
  String program3_on_hour_st = Timer_Config.substring(comma_posi_1+1, comma_posi_2);
  String program3_on_minute_st = Timer_Config.substring(comma_posi_2+1, comma_posi_3);
  String program3_on_second_st = Timer_Config.substring(comma_posi_3+1, comma_posi_4);
  String program3_off_hour_st = Timer_Config.substring(comma_posi_4+1, comma_posi_5);
  String program3_off_minute_st = Timer_Config.substring(comma_posi_5+1, comma_posi_6);
  String program3_off_second_st = Timer_Config.substring(comma_posi_6+1, comma_posi_7);
  String program3_ctl_op_st = Timer_Config.substring(comma_posi_7+1, comma_posi_8);
  String program3_enable_st = Timer_Config.substring(comma_posi_8+1, comma_posi_9);

  program3_on_hour = program3_on_hour_st.toInt();
  program3_on_minute = program3_on_minute_st.toInt();
  program3_on_second = program3_on_second_st.toInt();
  program3_off_hour = program3_off_hour_st.toInt();
  program3_off_minute = program3_off_minute_st.toInt();
  program3_off_second = program3_off_second_st.toInt();
  program3_ctl_op = program3_ctl_op_st.toInt();
  program3_enable = program3_enable_st.toInt();
/////////////////////////////////////////////////////////////////////////////////////////////// End Read Line 6

/////////////////////////////////////////////////////////////////////////////////////////////// Read Line 7
  Serial.print("Config Timer Program 4 line 7 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  Timer_Config = line;
  Serial.print("Timer_Config Value : ");
  Serial.println(Timer_Config);
  comma_posi_1 = Timer_Config.indexOf(",");
  comma_posi_2 = Timer_Config.indexOf(",", comma_posi_1+1);
  comma_posi_3 = Timer_Config.indexOf(",", comma_posi_2+1);
  comma_posi_4 = Timer_Config.indexOf(",", comma_posi_3+1);
  comma_posi_5 = Timer_Config.indexOf(",", comma_posi_4+1);
  comma_posi_6 = Timer_Config.indexOf(",", comma_posi_5+1);
  comma_posi_7 = Timer_Config.indexOf(",", comma_posi_6+1);
  comma_posi_8 = Timer_Config.indexOf(",", comma_posi_7+1);
  comma_posi_9 = Timer_Config.indexOf(",", comma_posi_8+1);

  progran_num = Timer_Config.substring(0, comma_posi_1);
  String program4_on_hour_st = Timer_Config.substring(comma_posi_1+1, comma_posi_2);
  String program4_on_minute_st = Timer_Config.substring(comma_posi_2+1, comma_posi_3);
  String program4_on_second_st = Timer_Config.substring(comma_posi_3+1, comma_posi_4);
  String program4_off_hour_st = Timer_Config.substring(comma_posi_4+1, comma_posi_5);
  String program4_off_minute_st = Timer_Config.substring(comma_posi_5+1, comma_posi_6);
  String program4_off_second_st = Timer_Config.substring(comma_posi_6+1, comma_posi_7);
  String program4_ctl_op_st = Timer_Config.substring(comma_posi_7+1, comma_posi_8);
  String program4_enable_st = Timer_Config.substring(comma_posi_8+1, comma_posi_9);

  program4_on_hour = program4_on_hour_st.toInt();
  program4_on_minute = program4_on_minute_st.toInt();
  program4_on_second = program4_on_second_st.toInt();
  program4_off_hour = program4_off_hour_st.toInt();
  program4_off_minute = program4_off_minute_st.toInt();
  program4_off_second = program4_off_second_st.toInt();
  program4_ctl_op = program4_ctl_op_st.toInt();
  program4_enable = program4_enable_st.toInt();
/////////////////////////////////////////////////////////////////////////////////////////////// End Read Line 7


/////////////////////////////////////////////////////////////////////////////////////////////// Read Line 8
  Serial.print("Config Timer Program 5 line 8 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  Timer_Config = line;
  Serial.print("Timer_Config Value : ");
  Serial.println(Timer_Config);
  comma_posi_1 = Timer_Config.indexOf(",");
  comma_posi_2 = Timer_Config.indexOf(",", comma_posi_1+1);
  comma_posi_3 = Timer_Config.indexOf(",", comma_posi_2+1);
  comma_posi_4 = Timer_Config.indexOf(",", comma_posi_3+1);
  comma_posi_5 = Timer_Config.indexOf(",", comma_posi_4+1);
  comma_posi_6 = Timer_Config.indexOf(",", comma_posi_5+1);
  comma_posi_7 = Timer_Config.indexOf(",", comma_posi_6+1);
  comma_posi_8 = Timer_Config.indexOf(",", comma_posi_7+1);
  comma_posi_9 = Timer_Config.indexOf(",", comma_posi_8+1);

  progran_num = Timer_Config.substring(0, comma_posi_1);
  String program5_on_hour_st = Timer_Config.substring(comma_posi_1+1, comma_posi_2);
  String program5_on_minute_st = Timer_Config.substring(comma_posi_2+1, comma_posi_3);
  String program5_on_second_st = Timer_Config.substring(comma_posi_3+1, comma_posi_4);
  String program5_off_hour_st = Timer_Config.substring(comma_posi_4+1, comma_posi_5);
  String program5_off_minute_st = Timer_Config.substring(comma_posi_5+1, comma_posi_6);
  String program5_off_second_st = Timer_Config.substring(comma_posi_6+1, comma_posi_7);
  String program5_ctl_op_st = Timer_Config.substring(comma_posi_7+1, comma_posi_8);
  String program5_enable_st = Timer_Config.substring(comma_posi_8+1, comma_posi_9);

  program5_on_hour = program5_on_hour_st.toInt();
  program5_on_minute = program5_on_minute_st.toInt();
  program5_on_second = program5_on_second_st.toInt();
  program5_off_hour = program5_off_hour_st.toInt();
  program5_off_minute = program5_off_minute_st.toInt();
  program5_off_second = program5_off_second_st.toInt();
  program5_ctl_op = program5_ctl_op_st.toInt();
  program5_enable = program5_enable_st.toInt();
/////////////////////////////////////////////////////////////////////////////////////////////// End Read Line 8


/////////////////////////////////////////////////////////////////////////////////////////////// Read Line 9
  Serial.print("Config Timer Program 6 line 9 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  Timer_Config = line;
  Serial.print("Timer_Config Value : ");
  Serial.println(Timer_Config);
  comma_posi_1 = Timer_Config.indexOf(",");
  comma_posi_2 = Timer_Config.indexOf(",", comma_posi_1+1);
  comma_posi_3 = Timer_Config.indexOf(",", comma_posi_2+1);
  comma_posi_4 = Timer_Config.indexOf(",", comma_posi_3+1);
  comma_posi_5 = Timer_Config.indexOf(",", comma_posi_4+1);
  comma_posi_6 = Timer_Config.indexOf(",", comma_posi_5+1);
  comma_posi_7 = Timer_Config.indexOf(",", comma_posi_6+1);
  comma_posi_8 = Timer_Config.indexOf(",", comma_posi_7+1);
  comma_posi_9 = Timer_Config.indexOf(",", comma_posi_8+1);

  progran_num = Timer_Config.substring(0, comma_posi_1);
  String program6_on_hour_st = Timer_Config.substring(comma_posi_1+1, comma_posi_2);
  String program6_on_minute_st = Timer_Config.substring(comma_posi_2+1, comma_posi_3);
  String program6_on_second_st = Timer_Config.substring(comma_posi_3+1, comma_posi_4);
  String program6_off_hour_st = Timer_Config.substring(comma_posi_4+1, comma_posi_5);
  String program6_off_minute_st = Timer_Config.substring(comma_posi_5+1, comma_posi_6);
  String program6_off_second_st = Timer_Config.substring(comma_posi_6+1, comma_posi_7);
  String program6_ctl_op_st = Timer_Config.substring(comma_posi_7+1, comma_posi_8);
  String program6_enable_st = Timer_Config.substring(comma_posi_8+1, comma_posi_9);

  program6_on_hour = program6_on_hour_st.toInt();
  program6_on_minute = program6_on_minute_st.toInt();
  program6_on_second = program6_on_second_st.toInt();
  program6_off_hour = program6_off_hour_st.toInt();
  program6_off_minute = program6_off_minute_st.toInt();
  program6_off_second = program6_off_second_st.toInt();
  program6_ctl_op = program6_ctl_op_st.toInt();
  program6_enable = program6_enable_st.toInt();
/////////////////////////////////////////////////////////////////////////////////////////////// End Read Line 9


/////////////////////////////////////////////////////////////////////////////////////////////// Read Line 10
  Serial.print("Config Timer Program 7 line 10 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  Timer_Config = line;
  Serial.print("Timer_Config Value : ");
  Serial.println(Timer_Config);
  comma_posi_1 = Timer_Config.indexOf(",");
  comma_posi_2 = Timer_Config.indexOf(",", comma_posi_1+1);
  comma_posi_3 = Timer_Config.indexOf(",", comma_posi_2+1);
  comma_posi_4 = Timer_Config.indexOf(",", comma_posi_3+1);
  comma_posi_5 = Timer_Config.indexOf(",", comma_posi_4+1);
  comma_posi_6 = Timer_Config.indexOf(",", comma_posi_5+1);
  comma_posi_7 = Timer_Config.indexOf(",", comma_posi_6+1);
  comma_posi_8 = Timer_Config.indexOf(",", comma_posi_7+1);
  comma_posi_9 = Timer_Config.indexOf(",", comma_posi_8+1);

  progran_num = Timer_Config.substring(0, comma_posi_1);
  String program7_on_hour_st = Timer_Config.substring(comma_posi_1+1, comma_posi_2);
  String program7_on_minute_st = Timer_Config.substring(comma_posi_2+1, comma_posi_3);
  String program7_on_second_st = Timer_Config.substring(comma_posi_3+1, comma_posi_4);
  String program7_off_hour_st = Timer_Config.substring(comma_posi_4+1, comma_posi_5);
  String program7_off_minute_st = Timer_Config.substring(comma_posi_5+1, comma_posi_6);
  String program7_off_second_st = Timer_Config.substring(comma_posi_6+1, comma_posi_7);
  String program7_ctl_op_st = Timer_Config.substring(comma_posi_7+1, comma_posi_8);
  String program7_enable_st = Timer_Config.substring(comma_posi_8+1, comma_posi_9);

  program7_on_hour = program7_on_hour_st.toInt();
  program7_on_minute = program7_on_minute_st.toInt();
  program7_on_second = program7_on_second_st.toInt();
  program7_off_hour = program7_off_hour_st.toInt();
  program7_off_minute = program7_off_minute_st.toInt();
  program7_off_second = program7_off_second_st.toInt();
  program7_ctl_op = program7_ctl_op_st.toInt();
  program7_enable = program7_enable_st.toInt();
/////////////////////////////////////////////////////////////////////////////////////////////// End Read Line 10


/////////////////////////////////////////////////////////////////////////////////////////////// Read Line 11
  Serial.print("Config Timer Program 8 line 11 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);
  Timer_Config = line;
  Serial.print("Timer_Config Value : ");
  Serial.println(Timer_Config);
  comma_posi_1 = Timer_Config.indexOf(",");
  comma_posi_2 = Timer_Config.indexOf(",", comma_posi_1+1);
  comma_posi_3 = Timer_Config.indexOf(",", comma_posi_2+1);
  comma_posi_4 = Timer_Config.indexOf(",", comma_posi_3+1);
  comma_posi_5 = Timer_Config.indexOf(",", comma_posi_4+1);
  comma_posi_6 = Timer_Config.indexOf(",", comma_posi_5+1);
  comma_posi_7 = Timer_Config.indexOf(",", comma_posi_6+1);
  comma_posi_8 = Timer_Config.indexOf(",", comma_posi_7+1);
  comma_posi_9 = Timer_Config.indexOf(",", comma_posi_8+1);

  progran_num = Timer_Config.substring(0, comma_posi_1);
  String program8_on_hour_st = Timer_Config.substring(comma_posi_1+1, comma_posi_2);
  String program8_on_minute_st = Timer_Config.substring(comma_posi_2+1, comma_posi_3);
  String program8_on_second_st = Timer_Config.substring(comma_posi_3+1, comma_posi_4);
  String program8_off_hour_st = Timer_Config.substring(comma_posi_4+1, comma_posi_5);
  String program8_off_minute_st = Timer_Config.substring(comma_posi_5+1, comma_posi_6);
  String program8_off_second_st = Timer_Config.substring(comma_posi_6+1, comma_posi_7);
  String program8_ctl_op_st = Timer_Config.substring(comma_posi_7+1, comma_posi_8);
  String program8_enable_st = Timer_Config.substring(comma_posi_8+1, comma_posi_9);

  program8_on_hour = program8_on_hour_st.toInt();
  program8_on_minute = program8_on_minute_st.toInt();
  program8_on_second = program8_on_second_st.toInt();
  program8_off_hour = program8_off_hour_st.toInt();
  program8_off_minute = program8_off_minute_st.toInt();
  program8_off_second = program8_off_second_st.toInt();
  program8_ctl_op = program8_ctl_op_st.toInt();
  program8_enable = program8_enable_st.toInt();

  
/////////////////////////////////////////////////////////////////////////////////////////////// End Read Line 11
/*
  Serial.print("program1_on_hour Value : ");
  Serial.print(program1_on_hour);
  Serial.print(" program1_on_minute Value : ");
  Serial.print(program1_on_minute);
  Serial.print(" program1_on_second Value : ");
  Serial.print(program1_on_second);  
  Serial.print(" program1_off_hour Value : ");
  Serial.print(program1_off_hour);
  Serial.print(" program1_off_minute Value : ");
  Serial.print(program1_off_minute);
  Serial.print(" program1_off_second Value : ");
  Serial.print(program1_off_second);  
  Serial.print(" program1_ctl_op Value : ");
  Serial.print(program1_ctl_op);  
  Serial.print(" program1_enable Value : ");
  Serial.println(program1_enable);

  Serial.print("program2_on_hour Value : ");
  Serial.print(program2_on_hour);
  Serial.print(" program2_on_minute Value : ");
  Serial.print(program2_on_minute);
  Serial.print(" program2_on_second Value : ");
  Serial.print(program2_on_second);  
  Serial.print(" program2_off_hour Value : ");
  Serial.print(program2_off_hour);
  Serial.print(" program2_off_minute Value : ");
  Serial.print(program2_off_minute);
  Serial.print(" program2_off_second Value : ");
  Serial.print(program2_off_second);  
  Serial.print(" program2_ctl_op Value : ");
  Serial.print(program2_ctl_op);  
  Serial.print(" program2_enable Value : ");
  Serial.println(program2_enable);

  Serial.print("program3_on_hour Value : ");
  Serial.print(program3_on_hour);
  Serial.print(" program3_on_minute Value : ");
  Serial.print(program3_on_minute);
  Serial.print(" program3_on_second Value : ");
  Serial.print(program3_on_second);  
  Serial.print(" program3_off_hour Value : ");
  Serial.print(program3_off_hour);
  Serial.print(" program3_off_minute Value : ");
  Serial.print(program3_off_minute);
  Serial.print(" program3_off_second Value : ");
  Serial.print(program3_off_second);  
  Serial.print(" program3_ctl_op Value : ");
  Serial.print(program3_ctl_op);  
  Serial.print(" program3_enable Value : ");
  Serial.println(program3_enable);

  Serial.print("program4_on_hour Value : ");
  Serial.print(program4_on_hour);
  Serial.print(" program4_on_minute Value : ");
  Serial.print(program4_on_minute);
  Serial.print(" program4_on_second Value : ");
  Serial.print(program4_on_second);  
  Serial.print(" program4_off_hour Value : ");
  Serial.print(program4_off_hour);
  Serial.print(" program4_off_minute Value : ");
  Serial.print(program4_off_minute);
  Serial.print(" program4_off_second Value : ");
  Serial.print(program4_off_second);  
  Serial.print(" program4_ctl_op Value : ");
  Serial.print(program4_ctl_op);  
  Serial.print(" program4_enable Value : ");
  Serial.println(program4_enable);

  Serial.print("program5_on_hour Value : ");
  Serial.print(program5_on_hour);
  Serial.print(" program5_on_minute Value : ");
  Serial.print(program5_on_minute);
  Serial.print(" program5_on_second Value : ");
  Serial.print(program5_on_second);  
  Serial.print(" program5_off_hour Value : ");
  Serial.print(program5_off_hour);
  Serial.print(" program5_off_minute Value : ");
  Serial.print(program5_off_minute);
  Serial.print(" program5_off_second Value : ");
  Serial.print(program5_off_second);  
  Serial.print(" program5_ctl_op Value : ");
  Serial.print(program5_ctl_op);  
  Serial.print(" program5_enable Value : ");
  Serial.println(program5_enable);

  Serial.print("program6_on_hour Value : ");
  Serial.print(program6_on_hour);
  Serial.print(" program6_on_minute Value : ");
  Serial.print(program6_on_minute);
  Serial.print(" program6_on_second Value : ");
  Serial.print(program6_on_second);  
  Serial.print(" program6_off_hour Value : ");
  Serial.print(program6_off_hour);
  Serial.print(" program6_off_minute Value : ");
  Serial.print(program6_off_minute);
  Serial.print(" program6_off_second Value : ");
  Serial.print(program6_off_second);  
  Serial.print(" program6_ctl_op Value : ");
  Serial.print(program6_ctl_op);  
  Serial.print(" program6_enable Value : ");
  Serial.println(program6_enable);

  Serial.print("program7_on_hour Value : ");
  Serial.print(program7_on_hour);
  Serial.print(" program7_on_minute Value : ");
  Serial.print(program7_on_minute);
  Serial.print(" program7_on_second Value : ");
  Serial.print(program7_on_second);  
  Serial.print(" program7_off_hour Value : ");
  Serial.print(program7_off_hour);
  Serial.print(" program7_off_minute Value : ");
  Serial.print(program7_off_minute);
  Serial.print(" program7_off_second Value : ");
  Serial.print(program7_off_second);  
  Serial.print(" program7_ctl_op Value : ");
  Serial.print(program7_ctl_op);  
  Serial.print(" program7_enable Value : ");
  Serial.println(program7_enable);

  Serial.print("program8_on_hour Value : ");
  Serial.print(program8_on_hour);
  Serial.print(" program8_on_minute Value : ");
  Serial.print(program8_on_minute);
  Serial.print(" program8_on_second Value : ");
  Serial.print(program8_on_second);  
  Serial.print(" program8_off_hour Value : ");
  Serial.print(program8_off_hour);
  Serial.print(" program8_off_minute Value : ");
  Serial.print(program8_off_minute);
  Serial.print(" program8_off_second Value : ");
  Serial.print(program8_off_second);  
  Serial.print(" program8_ctl_op Value : ");
  Serial.print(program8_ctl_op);  
  Serial.print(" program8_enable Value : ");
  Serial.println(program8_enable);
*/

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  delay(1000);
  lcd.clear();
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  lcd.setCursor(0, 2);
  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, pass);
//  Blynk.begin(auth, ssid, pass); //DN_ADD Debug

  Blynk.begin(auth_Debug, ssid_Debug, pass_Debug, IPAddress(128,199,250,152), 8080);
  
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.print("WiFi Connected      ");
  lcd.setCursor(0, 1);
  lcd.print("IP address is       ");
  lcd.setCursor(0, 2);
  lcd.print(WiFi.localIP());
  delay(2000);
  Serial.println("Done");
  lcd.clear();
  lcd.print(" Init System Done!  ");
  delay(2000);
  lcd.clear();
}

void loop(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    display_time();
    control_relay();
    nodeState =! nodeState;
    Blynk.run();
  }
}

void control_relay(){
  Serial.print(hour_now);
  Serial.print(":");
  Serial.print(minute_now);
  Serial.print(":");
  Serial.print(second_now);
  Serial.println("");

  if(nodeState == 1){ // STATUS NODE Online
    STATUS_Node.on(); 
  }else{
    STATUS_Node.off();
  }
  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//  
  if((hour_now==program1_on_hour) && (minute_now==program1_on_minute) && (second_now >= program1_on_second) && (program1_ctl_bit == 0)){
    Serial.print("Program 1 Control Output ");
    switch(program1_ctl_op){
      case 1: Serial.println("RY 1 ON"); program1_relay1_output_bit = 1; break;
      case 2: Serial.println("RY 2 ON"); program1_relay2_output_bit = 1;  break;
      case 3: Serial.println("RY 3 ON"); program1_relay3_output_bit = 1;  break;
      case 4: Serial.println("RY 4 ON"); program1_relay4_output_bit = 1;  break;
    }
    program1_ctl_bit = 1;
  }
//---------------------------------------------------------------------------------------------------------------------------------------//
  if( (hour_now==program1_off_hour) && (minute_now==program1_off_minute) && (second_now >= program1_off_second) && (program1_ctl_bit == 1)){
    Serial.print("Program 1 Control Output ");
    switch(program1_ctl_op){
      case 1: Serial.println("RY 1 OFF"); program1_relay1_output_bit = 0; break;
      case 2: Serial.println("RY 2 OFF"); program1_relay2_output_bit = 0; break;
      case 3: Serial.println("RY 3 OFF"); program1_relay3_output_bit = 0; break;
      case 4: Serial.println("RY 4 OFF"); program1_relay4_output_bit = 0; break;
    }
    program1_ctl_bit = 0;
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//  
  if((hour_now==program2_on_hour) && (minute_now==program2_on_minute) && (second_now >= program2_on_second) && (program2_ctl_bit == 0)){
    Serial.print("Program 2 Control Output ");
    switch(program2_ctl_op){
      case 1: Serial.println("RY 1 ON"); program2_relay1_output_bit = 1; break;
      case 2: Serial.println("RY 2 ON"); program2_relay2_output_bit = 1;  break;
      case 3: Serial.println("RY 3 ON"); program2_relay3_output_bit = 1;  break;
      case 4: Serial.println("RY 4 ON"); program2_relay4_output_bit = 1;  break;
    }
    program2_ctl_bit = 1;
  }
//---------------------------------------------------------------------------------------------------------------------------------------//
  if( (hour_now==program2_off_hour) && (minute_now==program2_off_minute) && (second_now >= program2_off_second) && (program2_ctl_bit == 1)){
    Serial.print("Program 2 Control Output ");
    switch(program2_ctl_op){
      case 1: Serial.println("RY 1 OFF"); program2_relay1_output_bit = 0; break;
      case 2: Serial.println("RY 2 OFF"); program2_relay2_output_bit = 0; break;
      case 3: Serial.println("RY 3 OFF"); program2_relay3_output_bit = 0; break;
      case 4: Serial.println("RY 4 OFF"); program2_relay4_output_bit = 0; break;
    }
    program2_ctl_bit = 0;
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//  
  if((hour_now==program3_on_hour) && (minute_now==program3_on_minute) && (second_now >= program3_on_second) && (program3_ctl_bit == 0)){
    Serial.print("Program 3 Control Output ");
    switch(program3_ctl_op){
      case 1: Serial.println("RY 1 ON"); program3_relay1_output_bit = 1; break;
      case 2: Serial.println("RY 2 ON"); program3_relay2_output_bit = 1;  break;
      case 3: Serial.println("RY 3 ON"); program3_relay3_output_bit = 1;  break;
      case 4: Serial.println("RY 4 ON"); program3_relay4_output_bit = 1;  break;
    }
    program3_ctl_bit = 1;
  }
//---------------------------------------------------------------------------------------------------------------------------------------//
  if( (hour_now==program3_off_hour) && (minute_now==program3_off_minute) && (second_now >= program3_off_second) && (program3_ctl_bit == 1)){
    Serial.print("Program 3 Control Output ");
    switch(program3_ctl_op){
      case 1: Serial.println("RY 1 OFF"); program3_relay1_output_bit = 0; break;
      case 2: Serial.println("RY 2 OFF"); program3_relay2_output_bit = 0; break;
      case 3: Serial.println("RY 3 OFF"); program3_relay3_output_bit = 0; break;
      case 4: Serial.println("RY 4 OFF"); program3_relay4_output_bit = 0; break;
    }
    program3_ctl_bit = 0;
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//  
  if((hour_now==program4_on_hour) && (minute_now==program4_on_minute) && (second_now >= program4_on_second) && (program4_ctl_bit == 0)){
    Serial.print("Program 4 Control Output ");
    switch(program4_ctl_op){
      case 1: Serial.println("RY 1 ON"); program4_relay1_output_bit = 1; break;
      case 2: Serial.println("RY 2 ON"); program4_relay2_output_bit = 1;  break;
      case 3: Serial.println("RY 3 ON"); program4_relay3_output_bit = 1;  break;
      case 4: Serial.println("RY 4 ON"); program4_relay4_output_bit = 1;  break;
    }
    program4_ctl_bit = 1;
  }
//---------------------------------------------------------------------------------------------------------------------------------------//
  if( (hour_now==program4_off_hour) && (minute_now==program4_off_minute) && (second_now >= program4_off_second) && (program4_ctl_bit == 1)){
    Serial.print("Program 4 Control Output ");
    switch(program4_ctl_op){
      case 1: Serial.println("RY 1 OFF"); program4_relay1_output_bit = 0; break;
      case 2: Serial.println("RY 2 OFF"); program4_relay2_output_bit = 0; break;
      case 3: Serial.println("RY 3 OFF"); program4_relay3_output_bit = 0; break;
      case 4: Serial.println("RY 4 OFF"); program4_relay4_output_bit = 0; break;
    }
    program4_ctl_bit = 0;
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//  
  if((hour_now==program5_on_hour) && (minute_now==program5_on_minute) && (second_now >= program5_on_second) && (program5_ctl_bit == 0)){
    Serial.print("Program 5 Control Output ");
    switch(program5_ctl_op){
      case 1: Serial.println("RY 1 ON"); program5_relay1_output_bit = 1; break;
      case 2: Serial.println("RY 2 ON"); program5_relay2_output_bit = 1;  break;
      case 3: Serial.println("RY 3 ON"); program5_relay3_output_bit = 1;  break;
      case 4: Serial.println("RY 4 ON"); program5_relay4_output_bit = 1;  break;
    }
    program5_ctl_bit = 1;
  }
//---------------------------------------------------------------------------------------------------------------------------------------//
  if( (hour_now==program5_off_hour) && (minute_now==program5_off_minute) && (second_now >= program5_off_second) && (program5_ctl_bit == 1)){
    Serial.print("Program 5 Control Output ");
    switch(program5_ctl_op){
      case 1: Serial.println("RY 1 OFF"); program5_relay1_output_bit = 0; break;
      case 2: Serial.println("RY 2 OFF"); program5_relay2_output_bit = 0; break;
      case 3: Serial.println("RY 3 OFF"); program5_relay3_output_bit = 0; break;
      case 4: Serial.println("RY 4 OFF"); program5_relay4_output_bit = 0; break;
    }
    program5_ctl_bit = 0;
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//  
  if((hour_now==program6_on_hour) && (minute_now==program6_on_minute) && (second_now >= program6_on_second) && (program6_ctl_bit == 0)){
    Serial.print("Program 6 Control Output ");
    switch(program6_ctl_op){
      case 1: Serial.println("RY 1 ON"); program6_relay1_output_bit = 1; break;
      case 2: Serial.println("RY 2 ON"); program6_relay2_output_bit = 1;  break;
      case 3: Serial.println("RY 3 ON"); program6_relay3_output_bit = 1;  break;
      case 4: Serial.println("RY 4 ON"); program6_relay4_output_bit = 1;  break;
    }
    program6_ctl_bit = 1;
  }
//---------------------------------------------------------------------------------------------------------------------------------------//
  if( (hour_now==program6_off_hour) && (minute_now==program6_off_minute) && (second_now >= program6_off_second) && (program6_ctl_bit == 1)){
    Serial.print("Program 6 Control Output ");
    switch(program6_ctl_op){
      case 1: Serial.println("RY 1 OFF"); program6_relay1_output_bit = 0; break;
      case 2: Serial.println("RY 2 OFF"); program6_relay2_output_bit = 0; break;
      case 3: Serial.println("RY 3 OFF"); program6_relay3_output_bit = 0; break;
      case 4: Serial.println("RY 4 OFF"); program6_relay4_output_bit = 0; break;
    }
    program6_ctl_bit = 0;
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//  
  if((hour_now==program7_on_hour) && (minute_now==program7_on_minute) && (second_now >= program7_on_second) && (program7_ctl_bit == 0)){
    Serial.print("Program 7 Control Output ");
    switch(program7_ctl_op){
      case 1: Serial.println("RY 1 ON"); program7_relay1_output_bit = 1; break;
      case 2: Serial.println("RY 2 ON"); program7_relay2_output_bit = 1;  break;
      case 3: Serial.println("RY 3 ON"); program7_relay3_output_bit = 1;  break;
      case 4: Serial.println("RY 4 ON"); program7_relay4_output_bit = 1;  break;
    }
    program7_ctl_bit = 1;
  }
//---------------------------------------------------------------------------------------------------------------------------------------//
  if( (hour_now==program7_off_hour) && (minute_now==program7_off_minute) && (second_now >= program7_off_second) && (program7_ctl_bit == 1)){
    Serial.print("Program 3 Control Output ");
    switch(program7_ctl_op){
      case 1: Serial.println("RY 1 OFF"); program7_relay1_output_bit = 0; break;
      case 2: Serial.println("RY 2 OFF"); program7_relay2_output_bit = 0; break;
      case 3: Serial.println("RY 3 OFF"); program7_relay3_output_bit = 0; break;
      case 4: Serial.println("RY 4 OFF"); program7_relay4_output_bit = 0; break;
    }
    program7_ctl_bit = 0;
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//  
  if((hour_now==program8_on_hour) && (minute_now==program8_on_minute) && (second_now >= program8_on_second) && (program8_ctl_bit == 0)){
    Serial.print("Program 4 Control Output ");
    switch(program8_ctl_op){
      case 1: Serial.println("RY 1 ON"); program8_relay1_output_bit = 1; break;
      case 2: Serial.println("RY 2 ON"); program8_relay2_output_bit = 1;  break;
      case 3: Serial.println("RY 3 ON"); program8_relay3_output_bit = 1;  break;
      case 4: Serial.println("RY 4 ON"); program8_relay4_output_bit = 1;  break;
    }
    program8_ctl_bit = 1;
  }
//---------------------------------------------------------------------------------------------------------------------------------------//
  if( (hour_now==program8_off_hour) && (minute_now==program8_off_minute) && (second_now >= program8_off_second) && (program8_ctl_bit == 1)){
    Serial.print("Program 4 Control Output ");
    switch(program8_ctl_op){
      case 1: Serial.println("RY 1 OFF"); program8_relay1_output_bit = 0; break;
      case 2: Serial.println("RY 2 OFF"); program8_relay2_output_bit = 0; break;
      case 3: Serial.println("RY 3 OFF"); program8_relay3_output_bit = 0; break;
      case 4: Serial.println("RY 4 OFF"); program8_relay4_output_bit = 0; break;
    }
    program8_ctl_bit = 0;
  }
  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
  
  



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//    Control OUTPUT
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

  if(program1_relay1_output_bit || program2_relay1_output_bit || program3_relay1_output_bit || program4_relay1_output_bit || program5_relay1_output_bit || program6_relay1_output_bit || program7_relay1_output_bit || program8_relay1_output_bit){
    lcd.setCursor(0, 1);
    lcd.print("RY1:ON    ");
    digitalWrite(RY_1, LOW);
    STAUS_RY_1.on();
  }else{
    lcd.setCursor(0, 1);
    lcd.print("RY1:OFF   ");
    digitalWrite(RY_1, HIGH);
    STAUS_RY_1.off();
  }


  if(program1_relay2_output_bit || program2_relay2_output_bit || program3_relay2_output_bit || program4_relay2_output_bit || program5_relay2_output_bit || program6_relay2_output_bit || program7_relay2_output_bit || program8_relay2_output_bit){
    lcd.setCursor(0, 2);
    lcd.print("RY2:ON    ");
    digitalWrite(RY_2, LOW);
    STAUS_RY_2.on();
  }else{
    lcd.setCursor(0, 2);
    lcd.print("RY2:OFF   ");
    digitalWrite(RY_2, HIGH);
    STAUS_RY_2.off();
  }


  if(program1_relay3_output_bit || program2_relay3_output_bit || program3_relay3_output_bit || program4_relay3_output_bit || program5_relay3_output_bit || program6_relay3_output_bit || program7_relay3_output_bit || program8_relay3_output_bit){
    lcd.setCursor(10, 1);
    lcd.print("RY3:ON    ");
    digitalWrite(RY_3, LOW);
    STAUS_RY_3.on();
  }else{
    lcd.setCursor(10, 1);
    lcd.print("RY3:OFF   ");
    digitalWrite(RY_3, HIGH);
    STAUS_RY_3.off();
  }


  
  if(program1_relay4_output_bit || program2_relay4_output_bit || program3_relay4_output_bit || program4_relay4_output_bit || program5_relay4_output_bit || program6_relay4_output_bit || program7_relay4_output_bit || program8_relay4_output_bit){
    lcd.setCursor(10, 2);
    lcd.print("RY4:ON    ");
    digitalWrite(RY_4, LOW);
    STAUS_RY_4.on();
  }else{
    lcd.setCursor(10, 2);
    lcd.print("RY4:OFF   ");
    digitalWrite(RY_4, HIGH);
    STAUS_RY_4.off();
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

bool readLine(File &f, char* line, size_t maxLen) {
  for (size_t n = 0; n < maxLen; n++) {
    int c = f.read();
    if ( c < 0 && n == 0) return false;  // EOF
    if (c < 0 || c == '\n') {
      line[n] = 0;
      return true;
    }
    line[n] = c;
  }
  return false; // line too long
}

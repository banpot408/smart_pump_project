#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 20, 4);

#include <SPI.h>
#include <SD.h>

#include <ESP8266WiFi.h>

bool WiFiConnected = false;
File myFile;

String WiFi_Config ;
String Timer_Config ;

char* ssid;
char* pass;


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

bool readVals(long * v1, long * v2) {
  char line[200], *ptr, *str;
  if (!readLine(myFile, line, sizeof(line))) {
    return false;  // EOF or too long
  }
  Serial.print("Read Line Is ");
  Serial.println(line);
}

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
    return;
  }
  Serial.println("initialization done.");
  lcd.clear();
  lcd.print("initialization done.");
  delay(1000);
  lcd.clear();
  lcd.print("Reading Config File ");

  // re-open the file for reading:
  myFile = SD.open("test.csv", FILE_READ);
  if (!myFile) {
    Serial.println("error open file test.csv");
    delay(1000);
    lcd.clear();
    lcd.print("error open conf.csv ");
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
  int comma_posi_1 = WiFi_Config.indexOf(",");
  Serial.println(comma_posi_1);
  Serial.println(WiFi_Config.substring(0, comma_posi_1));
  const String ssid = WiFi_Config.substring(0, comma_posi_1);

  Serial.print("WiFi_Config comma_posi_2 : ");
  int comma_posi_2 = WiFi_Config.indexOf(",", comma_posi_1+1);
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

  Serial.print("line 4 Status : ");
  Serial.print(readLine(myFile, line, sizeof(line)));
  Serial.print(" Value : ");
  Serial.println(line);

  Timer_Config = line;
 
  Serial.print("Timer_Config Value : ");
  Serial.println(Timer_Config);

      comma_posi_1 = Timer_Config.indexOf(",");
      comma_posi_2 = Timer_Config.indexOf(",", comma_posi_1+1);
  int comma_posi_3 = Timer_Config.indexOf(",", comma_posi_2+1);
  int comma_posi_4 = Timer_Config.indexOf(",", comma_posi_3+1);
  int comma_posi_5 = Timer_Config.indexOf(",", comma_posi_4+1);
  int comma_posi_6 = Timer_Config.indexOf(",", comma_posi_5+1);
  int comma_posi_7 = Timer_Config.indexOf(",", comma_posi_6+1);
  int comma_posi_8 = Timer_Config.indexOf(",", comma_posi_7+1);
  int comma_posi_9 = Timer_Config.indexOf(",", comma_posi_8+1);

  String progran_num = Timer_Config.substring(0, comma_posi_1);
  String program1_on_hour_st = Timer_Config.substring(comma_posi_1+1, comma_posi_2);
  String program1_on_minute_st = Timer_Config.substring(comma_posi_2+1, comma_posi_3);
  String program1_on_second_st = Timer_Config.substring(comma_posi_3+1, comma_posi_4);
  String program1_off_hour_st = Timer_Config.substring(comma_posi_4+1, comma_posi_5);
  String program1_off_minute_st = Timer_Config.substring(comma_posi_5+1, comma_posi_6);
  String program1_off_second_st = Timer_Config.substring(comma_posi_6+1, comma_posi_7);
  String program1_ctl_op_st = Timer_Config.substring(comma_posi_7+1, comma_posi_8);
  String program1_enable_st = Timer_Config.substring(comma_posi_8+1, comma_posi_9);

   program1_on_hour = program1_on_minute_st.toInt();
   program1_on_minute = program1_on_minute_st.toInt();
   program1_on_second = program1_on_second_st.toInt();
   program1_off_hour = program1_off_hour_st.toInt();
   program1_off_minute = program1_off_minute_st.toInt();
   program1_off_second = program1_off_second_st.toInt();
   program1_ctl_op = program1_ctl_op_st.toInt();
   program1_enable = program1_enable_st.toInt();

  Serial.print("program1_on_hour Value : ");
  Serial.println(program1_on_hour);
  Serial.print("program1_on_minute Value : ");
  Serial.println(program1_on_minute);
  Serial.print("program1_on_second Value : ");
  Serial.println(program1_on_second);
  
  Serial.print("program1_off_hour Value : ");
  Serial.println(program1_off_hour);
  Serial.print("program1_off_minute Value : ");
  Serial.println(program1_off_minute);
  Serial.print("program1_off_second Value : ");
  Serial.println(program1_off_second);
  
  Serial.print("program1_ctl_op Value : ");
  Serial.println(program1_ctl_op);
  
  Serial.print("program1_enable Value : ");
  Serial.println(program1_enable);
  
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
  WiFi.begin(ssid, pass);
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

void loop() {
  // nothing happens after setup
}

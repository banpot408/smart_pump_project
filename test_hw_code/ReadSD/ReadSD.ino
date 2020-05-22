/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

File myFile;
char arlay[200];
String test_data ;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(D8)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  // re-open the file for reading:
  myFile = SD.open("test.csv");
  if (myFile) {
    Serial.println("test.csv:");
    // read from the file until there's nothing else in it:
    int loop_count = 0 ;
    while (myFile.available()) {
      char data = myFile.read();
      arlay[loop_count] = data;
      if(data=='\n')data ='*';
      if(data=='\r')data ='+';
      if(data=='\0')data ='-';
//      data.replace("\n", ",")
//      data.replace("\r", ",")
      Serial.print("data : *");
      Serial.print(data);
      Serial.print("*  hex of daata : ");
      Serial.println(data, HEX);
      loop_count++;
    }
    // close the file:   
    myFile.close();

    arlay[loop_count] = '\0';
    test_data = arlay;
    test_data.replace("\n", ",");
    test_data.replace("\r", ",");
    test_data.replace(",,", ",");
    Serial.print(" ");
    Serial.print("test_data.length()" ); 
    Serial.print(test_data.length());
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.csv");
  }
}

void loop() {
  // nothing happens after setup
}

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

 long x, y;

  
  Serial.print("Initializing SD card...");
  if (!SD.begin(D8)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // re-open the file for reading:
  myFile = SD.open("test.csv", FILE_READ);
  if (!myFile) {
    Serial.println("error open file test.csv:");
    return;
  }

  
//  while (readVals(&x, &y)) {
//  }

  readVals(&x, &y);
  readVals(&x, &y);
  readVals(&x, &y);
  readVals(&x, &y);
  readVals(&x, &y);
  readVals(&x, &y);
  readVals(&x, &y);
  readVals(&x, &y);

  
  Serial.println("Done");
}

void loop() {
  // nothing happens after setup
}

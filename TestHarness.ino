#include <Wire.h>
#include <LIDARlite.h>
#include <SPI.h>
#include <SD.h>

File outputLog;
LIDARlite lidar;
int readingCount = 0;
int distance = -1;

enum distanceSignal {
  far, 
  meduim, 
  near
}

distanceSignal currentSignal;

int findSignal(int distance) {
  if (distance < 50) {
    return distanceSignal.near;
  }
  else if (distance < 100) {
    return distanceSignal.medium;
  }
  else {
    return distanceSignal.far;
  }
}


void setup() {
  Serial.begin(9600);

  while (!Serial);
    Serial.print("Initializing SD card...");
    if (!SD.begin(10)) {
      Serial.println("initialization failed!");
      while (1);
  }

  Serial.println("initialization done.");

  if (SD.exists("testData.txt")) {

    Serial.println("testData.txt exists.");
    SD.remove("testData.txt");
    Serial.println("Clearing testData.txt");
  } else {
    Serial.println("example.txt doesn't exist.");
  }
  Serial.println("Opening new testData.txt");
  outputLog = SD.open("testData.txt", FILE_WRITE);

  lidarLite.begin(0, true);
  lidarLite.configure(0);
}

bool getDistance(bool firstValue) {
  int distance = -1;
  if (firstValue) {
    distance = lidar.distance();
  }
  else {
    distance = lidar.distance(false);
  }
  currentSignal = findSignal(distance);
  outputMessage += "Count: " + readingCount + "  Distance: " + distance + "  Signal: " + currentSignal;
  outputLog.write(outputMessage);    
  Serial.println(outputLog);
}

void loop() {
  char outputMessage[] = "";
  if (readingCount == 100) {
    outputLog.close();
    exit();
  }
  else if (readingCount == 0) {
    getDistance(true);
  }
  else {
    readingCount++;
    getDistance(false);
  }

  readingCount++;
  delay(10);
  }
  
}

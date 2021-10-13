#include <Arduino.h>
#include <LIDARLite.h>
#include <string.h>
#include <Wire.h>

using namespace std;

LIDARLite lidar;
uint16_t readingCount = 0;
uint16_t distance = -1;

String findSignal(int distance) {
  if (distance < 50) {
    return "close";
  }
  else if (distance < 100) {
    return "medium";
  }
  else {
    return "far";
  }
}


void setup() {
  Serial.begin(115200);

  lidar.begin(1, true); // 400 kHz
  lidar.configure(0);

}

bool getDistance(bool firstValue) {
  uint16_t distance = -1;
  if (firstValue) {
    distance = lidar.distance();
  }
  else {
    distance = lidar.distance(false);
  }
  String currentSignal = findSignal(distance);
  String outputMessage = "Count: " + readingCount;
  Serial.print("Count: ");
  Serial.print(readingCount);
  Serial.print("  Distance: ");
  Serial.print(distance);
  Serial.print(" Signal: ");
  Serial.print(currentSignal);
  Serial.println("");
}

void loop() {
  String outputMessage = "";
  if (readingCount == 100) {
    exit(0);
  }
  else if (readingCount == 0) {
    getDistance(true);
  }
  else {
    getDistance(false);
  }

  readingCount++;
  delay(1000);
}

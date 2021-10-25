/*------------------------------------------------------------------------------
  LIDARLite Arduino Library
  v3/GetDistancePwm
  This example shows how to read distance from a LIDAR-Lite connected over the
  PWM interface.
  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite Ground (black) to Arduino GND
  LIDAR-Lite Mode control (yellow) to Arduino digital input (pin 3)
  LIDAR-Lite Mode control (yellow) to 1 kOhm resistor lead 1
  1 kOhm resistor lead 2 to Arduino digital output (pin 2)
  (Capacitor recommended to mitigate inrush current when device is enabled)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND
  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf
------------------------------------------------------------------------------*/
#include <Sparkfun_DRV2605L.h> //SparkFun Haptic Motor Driver Library 
#include <Wire.h> //I2C library 

unsigned long pulseWidth;
unsigned long pulseWidth2;
unsigned long pulseWidth3;
int outputValue;


SFE_HMD_DRV2605L HMD; //Create haptic motor driver object 
void setup()
{
  Serial.begin(115200); // Start serial communications
  HMD.begin();
  HMD.Mode(0x03); //PWM INPUT 
  HMD.MotorSelect(0x0A);
  HMD.Library(7); //change to 6 for LRA motors 
  pinMode(8, OUTPUT); // Left HMD
  pinMode(9, OUTPUT); // middle HMD
  pinMode(10, OUTPUT); // right HMD
  digitalWrite(8, LOW); // Set trigger LOW for continuous read
  digitalWrite(9, LOW); // Set trigger LOW for continuous read
  digitalWrite(10, LOW); // Set trigger LOW for continuous read
  pinMode(2, OUTPUT);
  pinMode(3, INPUT); // Set pin 3 as monitor pin
  pinMode(4, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(4, LOW); // Set trigger LOW for continuous read

  pinMode(5, INPUT); // Set pin 3 as monitor pin
  pinMode(6, OUTPUT); // Set pin 2 as trigger pin
  digitalWrite(6, LOW); // Set trigger LOW for continuous read

  pinMode(7, INPUT); // Set pin 3 as monitor pin
}

void loop()
{
  pulseWidth = pulseIn(3, HIGH); // Count how long the pulse is high in microseconds

  // If we get a reading that isn't zero, let's print it
  if(pulseWidth != 0)
  {
    pulseWidth = pulseWidth / 10; // 10usec = 1 cm of distance
    Serial.println("Lidar 1 Reading:");
    Serial.println(pulseWidth
    ); // Print the distance
  }
  pulseWidth = pulseIn(3, LOW);
  pulseWidth2 = pulseIn(5, HIGH); // Count how long the pulse is high in microseconds

  // If we get a reading that isn't zero, let's print it
  if(pulseWidth2 != 0)
  {
    pulseWidth2 = pulseWidth2 / 10; // 10usec = 1 cm of distance
    Serial.println("Lidar 2 Reading:");
    Serial.println(pulseWidth2
    ); // Print the distance
  }
  pulseWidth2 = pulseIn(5, LOW);
  pulseWidth3 = pulseIn(7, HIGH); // Count how long the pulse is high in microseconds

  // If we get a reading that isn't zero, let's print it
  if(pulseWidth3 != 0)
  {
    pulseWidth3 = pulseWidth3 / 10; // 10usec = 1 cm of distance
    Serial.println("Lidar 3 Reading:");
    Serial.println(pulseWidth3
    ); // Print the distance
  }
  
  pulseWidth3 = pulseIn(7, LOW);
  
  if (pulseWidth > pulseWidth2 && pulseWidth > pulseWidth3) {
    outputValue = map(pulseWidth, 0, 1023, 0, 255);
    // change the analog out value:
    analogWrite(8, outputValue);
    
    digitalWrite(8, HIGH); // Set trigger LOW for continuous read
 
    delay(500);
    
    digitalWrite(8, LOW); // Set trigger LOW for continuous read
    
    }
  else if (pulseWidth2 > pulseWidth && pulseWidth2 > pulseWidth3) {
    outputValue = map(pulseWidth2, 0, 1023, 0, 255);
    analogWrite(9, outputValue);
    digitalWrite(9, HIGH); // Set trigger LOW for continuous read
    delay(500);
    digitalWrite(9, LOW); // Set trigger LOW for continuous read
  }
  else if (pulseWidth3 > pulseWidth && pulseWidth3 > pulseWidth2) {
    outputValue = map(pulseWidth3, 0, 1023, 0, 255);
    analogWrite(10, outputValue);
    digitalWrite(10, HIGH); // Set trigger LOW for continuous read
    delay(500);
    digitalWrite(10, LOW); // Set trigger LOW for continuous read
  }
  delay(2000);
}

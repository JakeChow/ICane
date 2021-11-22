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
unsigned long currentReading[3] = {0, 0, 0}
unsigned long previousReading[3] = {0, 0, 0}


/*
 * Signal Library Layout:
 * . = short puls, - = longpulse
 * output is an array in form [x, y, z] where:
 *    x represents the starting point of the signal where . is close and - is far
 *    y represents the where the signal has gone from the startingp point where . is close and - is far
 *    z represents the speed at which the jump occured where . is fast and - is slow.
 
 * 
 * constantFar: ---
 * constantClose: ...
 * slowFarToClose: -.-
 * fastFarToClose: -..
 * slowCloseToFar: .--
 * fastCloseToFar: .-.
 */
enum signals {
  constantFar, 
  constantClose,
  slowFarToClose,
  fastFarToClose,
  slowCloseToFar,
  fastCloseToFar,
  faulty,
  unknown
};

/* 
 * Updates the list of previous and current reading with a new read value
 */
void updateReadings(newValue, lidar) {
  switch (lidar) {
    case 0: 
      previousReading[0] = currentReading[0];
      currentReading[0] = newValue;
    }    
    case 1: 
      previousReading[1] = currentReading[1];
      currentReading[1] = newValue;
    }
    case 2: 
      previousReading[2] = currentReading[2];
      currentReading[2] = newValue;
    }
}

/*
 * Creates a new signal based off the previous and current reading of a lidar
 */
signals createSignal(lidar) {
    signed long distanceChange = abs(previousReading[lidar] - currentReading[lidar])
    signals newSignal = unknown;
    //Constant far
    if (currentReading > 150 and distanceChange < 30) {
      newSignal = constantFar;
    }
    //Constant close
    else if (currentReading < 150 and distanceChange < 30) {
      newSignal = constantClose;
    }
    //slowFarToClose
    else if () {
      newSignal = slowFarToClose;
    }
    //fastFarToClose
    else if () {
      newSignal = fastFarToClose;
    }
    //slowCloseToFar
    else if () {
      newSignal = slowCloseToFar;
    }
    //fastCloseToFar
    else if () {
      newSignal = fastCloseToFar;
    }
    //faulty
    else {
      newSignal = faulty;
    }

    return newSignal;
}

/*
 * A function that creates the signal output for a read from the LIDAR
 * @param readOutput : Represents a signal change calculated from a reading from the lidar
 * @param magnitude : Representa the distance that the LIDAR read
 * @returns : An array of the corresponding output signals for the haptic motor drivers.
 */
array createSignal(readOutput, magnitude) {
  map outputSignals[3];
  switch (readOutput) {
  case constantFar:
    outputValue[0] = map(magnitude, 0, 1023, 0, 255);
    outputValue[1] = map(magnitude, 0, 1023, 0, 255);
    outputValue[2] = map(magnitude, 0, 1023, 0, 255);
    break;
  case constantClose:
    outputValue[0] = map(magnitude, 0, 1023, 0, 255);
    outputValue[1] = map(magnitude, 0, 1023, 0, 255);
    outputValue[2] = map(magnitude, 0, 1023, 0, 255);
    break;
  case slowFarToClose:
    outputValue[0] = map(magnitude, 0, 1023, 0, 255);
    outputValue[1] = map(magnitude, 0, 1023, 0, 255);
    outputValue[2] = map(magnitude, 0, 1023, 0, 255);
    break;
  case fastFarToClose:
    outputValue[0] = map(magnitude, 0, 1023, 0, 255);
    outputValue[1] = map(magnitude, 0, 1023, 0, 255);
    outputValue[2] = map(magnitude, 0, 1023, 0, 255);
    break;
   case slowCloseToFar:
    outputValue[0] = map(magnitude, 0, 1023, 0, 255);
    outputValue[1] = map(magnitude, 0, 1023, 0, 255);
    outputValue[2] = map(magnitude, 0, 1023, 0, 255);
    break;
   case fastCloseToFar:
    outputValue[0] = map(magnitude, 0, 1023, 0, 255);
    outputValue[1] = map(magnitude, 0, 1023, 0, 255);
    outputValue[2] = map(magnitude, 0, 1023, 0, 255);
    break;
   case faulty: 
    outputValue[0] = map(magnitude, 0, 0, 0, 0);
    outputValue[1] = map(magnitude, 0, 0, 0, 0);
    outputValue[2] = map(magnitude, 0, 0, 0, 0);
  default:
    outputValue[0] = map(magnitude, 0, 0, 0, 0);
    outputValue[1] = map(magnitude, 0, 0, 0, 0);
    outputValue[2] = map(magnitude, 0, 0, 0, 0);
    break;
}
  return outputValue
}



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

//  if (pulseWidth > pulseWidth2 && pulseWidth > pulseWidth3) {
//    outputValue = map(pulseWidth, 0, 1023, 0, 255);
//    // change the analog out value:
//    analogWrite(8, outputValue);
//
//    digitalWrite(8, HIGH); // Set trigger LOW for continuous read
//
//    delay(500);
//
//    digitalWrite(8, LOW); // Set trigger LOW for continuous read
//
//    }
//  else if (pulseWidth2 > pulseWidth && pulseWidth2 > pulseWidth3) {
//    outputValue = map(pulseWidth2, 0, 1023, 0, 255);
//    analogWrite(9, outputValue);
//    digitalWrite(9, HIGH); // Set trigger LOW for continuous read
//    delay(500);
//    digitalWrite(9, LOW); // Set trigger LOW for continuous read
//  }
//  else if (pulseWidth3 > pulseWidth && pulseWidth3 > pulseWidth2) {
//    outputValue = map(pulseWidth3, 0, 1023, 0, 255);
//    analogWrite(10, outputValue);
//    digitalWrite(10, HIGH); // Set trigger LOW for continuous read
//    delay(500);
//    digitalWrite(10, LOW); // Set trigger LOW for continuous read
//  }
  delay(2000);
}

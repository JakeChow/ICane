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


unsigned long pulseWidth;
unsigned long pulseWidth2;
unsigned long pulseWidth3;
int outputValue;
unsigned long currentReading[3] = {0, 0, 0};
unsigned long previousReading[3] = {0, 0, 0};
signals signal1;
signals signal2;
signals signal3;
int pulse1[3];
int pulse2[3];
int pulse3[3];
int delays1[3];
int delays2[3];
int delays3[3];




/* 
 * Updates the list of previous and current reading with a new read value
 */
void updateReadings(int newValue, int lidar) {
  switch (lidar) {
    case 0: 
      previousReading[0] = currentReading[0];
      currentReading[0] = newValue;
      break;    
    case 1: 
      previousReading[1] = currentReading[1];
      currentReading[1] = newValue;
      break;
    case 2: 
      previousReading[2] = currentReading[2];
      currentReading[2] = newValue;
      break;
    case default:
     break;  
  }
}

/*
 * Creates a new signal based off the previous and current reading of a lidar
 */
signals createSignal(int lidar) {
    signed long distanceChange = abs(previousReading[lidar] - currentReading[lidar])
    signals newSignal = unknown;
    //Constant far
    if () {
      newSignal = constantFar;
      print(lidar + 1 + "had signaled ConstantFar");
    }
    //Constant close
    else if () {
      newSignal = constantClose;
      print(lidar + 1 + "had signaled ConstantClose");
    }
    //slowFarToClose
    else if () {
      newSignal = slowFarToClose;
      print(lidar + 1 + "had signaled SlowFarToClose");
    }
    //fastFarToClose
    else if () {
      newSignal = fastFarToClose;
      print(lidar + 1 + "had signaled FastFarToClose");
    }
    //slowCloseToFar
    else if () {
      newSignal = slowCloseToFar;
      print(lidar + 1 + "had signaled SlowCloseToFar");
    }
    //fastCloseToFar
    else if () {
      newSignal = fastCloseToFar;
      print(lidar + 1 + "had signaled FastCloseToFar");
    }
    //faulty
    else {
      newSignal = faulty;
      print(lidar + 1 + "had signaled Faulty");
    }

    return newSignal;
}

/*
 * A function that creates the signal delay for a read from the LIDAR
 * @param readOutput : Represents a signal change calculated from a reading from the lidar
 * @param magnitude : Represents the distance that the LIDAR read
 * @returns : An array of the corresponding output signals for the haptic motor drivers.
 */
int * createDelays(signals signalType) {
  int outputDelays[3];
  switch (signalType) {
    case constantFar:
      outputDelays[0] = 100;
      outputDelays[1] = 100;
      outputDelays[2] = 100;
      break;
    case constantClose:
      outputDelays[0] = 50;
      outputDelays[1] = 50;
      outputDelays[2] = 50;
      break;
    case slowFarToClose:
      outputDelays[0] = 100;
      outputDelays[1] = 50;
      outputDelays[2] = 100;
      break;
    case fastFarToClose:
      outputDelays[0] = 100;
      outputDelays[1] = 50;
      outputDelays[2] = 50;
      break;
    case slowCloseToFar:
      outputDelays[0] = 50;
      outputDelays[1] = 100;
      outputDelays[2] = 100;
      break;
    case fastCloseToFar:
      outputDelays[0] = 50;
      outputDelays[1] = 100;
      outputDelays[2] = 50;
      break;
    default: 
      outputDelays[0] = 5;
      outputDelays[1] = 5;
      outputDelays[2] = 5;
    }
  return outputDelays;
}


/*
 * A function that creates the signal output for a read from the LIDAR
 * @param readOutput : Represents a signal change calculated from a reading from the lidar
 * @param magnitude : Represents the distance that the LIDAR read
 * @returns : An array of the corresponding output signals for the haptic motor drivers.
 */
int * createPulse(signals signalType, int magnitude) {
  int outputSignals[3];
  switch (signalType) {
  case constantFar:
    outputValue[0] = map(magnitude, 0, 1023, 0, 1023);
    outputValue[1] = map(magnitude, 0, 1023, 0, 1023);
    outputValue[2] = map(magnitude, 0, 1023, 0, 1023);
    break;
  case constantClose:
    outputValue[0] = map(magnitude, 0, 1023, 0, 1023);
    outputValue[1] = map(magnitude, 0, 1023, 0, 1023);
    outputValue[2] = map(magnitude, 0, 1023, 0, 1023);
    break;
  case slowFarToClose:
    outputValue[0] = map(magnitude*2, 0, 1023, 0, 1023);
    outputValue[1] = map(magnitude, 0, 1023, 0, 1023);
    outputValue[2] = map(magnitude*2, 0, 1023, 0, 1023);
    break;
  case fastFarToClose:
    outputValue[0] = map(magnitude*2, 0, 1023, 0, 1023);
    outputValue[1] = map(magnitude, 0, 1023, 0, 1023);
    outputValue[2] = map(magnitude, 0, 1023, 0, 1023);
    break;
   case slowCloseToFar:
    outputValue[0] = map(magnitude, 0, 1023, 0, 1023);
    outputValue[1] = map(magnitude*2, 0, 1023, 0, 1023);
    outputValue[2] = map(magnitude*2, 0, 1023, 0, 1023);
    break;
   case fastCloseToFar:
    outputValue[0] = map(magnitude, 0, 1023, 0, 1023);
    outputValue[1] = map(magnitude*2, 0, 1023, 0, 1023);
    outputValue[2] = map(magnitude, 0, 1023, 0, 1023);
    break;
   case faulty: 
    outputValue[0] = map(magnitude, 0, 0, 0, 0);
    outputValue[1] = map(magnitude, 0, 0, 0, 0);
    outputValue[2] = map(magnitude, 0, 0, 0, 0);
    break;
  default:
    outputValue[0] = map(magnitude, 0, 0, 0, 0);
    outputValue[1] = map(magnitude, 0, 0, 0, 0);
    outputValue[2] = map(magnitude, 0, 0, 0, 0);
    break;
}
  return outputValue
}

void sendPulse(pulses, int lidar, delays) {
  switch(lidar) {
    case 0:
      for (int i = 0; i < 3; i++) {
        analogWrite(8, pulses[i]);
        digitalWrite(8, HIGH);
        delay(delays[i]);
        digitalWrite(8, LOW);
      }
      
      digitalWrite(8, LOW);
    case 1:
      for (int i = 0; i < 3; i++) {
        analogWrite(9, pulses[i]);
        digitalWrite(9, HIGH);
        delay(delays[i]);
        digitalWrite(9, LOW);
      }
      digitalWrite(9, LOW);
    case 2: 
      for (int i = 0; i < 3; i++) {
        analogWrite(10, pulses[i]);
        digitalWrite(10, HIGH);
        delay(delays[i]);
        digitalWrite(10, LOW);
      }
      digitalWrite(10, LOW);
  }
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

  updateReadings(pulseWidth, 0);
  updateReadings(pulseWidth2, 1);
  updateReadings(pulseWidth3, 2);

  signal1 = createSignal(0);
  signal2 = createSignal(1);
  signal3 = createSignal(2);

  pulse1 = createPulse(signal1, pulseWidth);
  pulse2 = createPulse(signal2, pulseWidth2);
  pulse3 = createPulse(signal3, pulseWidth3);

  delays1 = createDelays(signal1);
  delays2 = createDelays(signal2);
  delays3 = createDelays(signal3);
  

  sendPulse(pulse1, 0, delays1);
  sendPulse(pulse2, 1, delays2);
  sendPulse(pulse3, 2, delays3);
  
  delay(1000);
}

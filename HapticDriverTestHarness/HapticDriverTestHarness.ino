#include <Sparkfun_DRV2605L.h> //SparkFun Haptic Motor Driver Library 
#include <Wire.h> //I2C library 

SFE_HMD_DRV2605L HMD; //Create haptic motor driver object 

void setup() 
{
  HMD.begin();
  Serial.begin(9600);
  HMD.Mode(0); // Internal trigger input mode -- Must use the GO() function to trigger playback.
  HMD.MotorSelect(0x36); // ERM motor, 4x Braking, Medium loop gain, 1.365x back EMF gain
  HMD.Library(2); //1-5 & 7 for ERM motors, 6 for LRA motors 

}
void loop() 
{
  int seq = 0; //There are 8 sequence registers that can queue up to 8 waveforms
  for(int wave = 1; wave <=123; wave++) //There are 123 waveform effects 
  {
     HMD.Waveform(seq, wave);
     HMD.go();
     delay(600); //give enough time to play effect 
     Serial.print("Waveform Sequence:      ");
     Serial.println(seq);
     Serial.print("Effect No.:      ");
     Serial.println(wave);

    if (wave%8==0) //Each Waveform register can queue 8 effects
    {
        seq=seq+1;
    }
    if (wave%64==0) // After the last register is used start over 
    {
        seq=0;
    }
  }
 }

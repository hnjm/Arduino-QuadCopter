#include <Servo.h>

Servo motors[4];
#define NUM_MOTORS (4)
//                      N S W  E
int pins[NUM_MOTORS] = {5,6,11,9};
 
int throttlePin = 0;
void arm_motor(){
  for (int i=0; i<NUM_MOTORS; i++) {
  motors[i].attach(pins[i]);
  }
    Serial.print("Motores Armados");  
}
void setup()
{
  Serial.begin(19200);
  arm_motor();
}
void acel_motor(int throttle){
  Serial.print("Acelerando Motores... ");  
  for (int i=0; i<NUM_MOTORS; i++) {
    motors[i].write(throttle);
  }

}
void loop()
{
int throttle = analogRead(throttlePin);
throttle = map(throttle, 0, 1023, 0, 200);
acel_motor(throttle);
  Serial.print("Power ");
  Serial.println(throttle, DEC);
}

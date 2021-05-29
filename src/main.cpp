#include <Arduino.h>
#include <ESC.h>
#include "imu.h"
#include "pid.h"

#define DEBUG

#define SPEED_MIN (1000)
#define SPEED_MAX (2000)
#define SAFETY_PIN 3

ESC downR(9, SPEED_MIN, SPEED_MAX, 500); 

ESC downL(10, SPEED_MIN, SPEED_MAX, 500); 

IMU mpu6050;

PID x_axis;
PID y_axis;
PID z_axis;

float x_PID;
float y_PID;
float z_PID;

int throttle;

int m1_throttle;
int m2_throttle;

void setup() {
  pinMode(SAFETY_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  mpu6050.setup();

  #ifdef DEBUG
  Serial.begin(115200);
  #endif

  for (int i = 0; i >= 5; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }

}

void loop() {
  while (digitalRead(SAFETY_PIN))
  {
    downL.arm();
    downR.arm();
  }
  while (!digitalRead(SAFETY_PIN))
  {
    downL.stop();
    downR.stop();
  }

  x_PID = x_axis.calculatePID(mpu6050.getAngle('x'), 0);

  m1_throttle = throttle + x_PID;
  m2_throttle = throttle - x_PID;

  //Right
  if(m1_throttle < 1000)
  {
    m1_throttle = 1000;
  }
  if(m1_throttle > 2000)
  {
    m1_throttle =2000;
  }
  //Left
  if(m2_throttle < 1000)
  {
    m2_throttle = 1000;
  }
  if(m2_throttle > 2000)
  {
    m2_throttle =2000;
  }

  downL.speed(m1_throttle);
  downR.speed(m2_throttle);

  #ifdef DEBUG
  Serial.print("Left PWM: ");
  Serial.print(m1_throttle);
  Serial.print(", Right PWM: "); 
  Serial.println(m2_throttle);
  #endif
   
  delay(100);
}
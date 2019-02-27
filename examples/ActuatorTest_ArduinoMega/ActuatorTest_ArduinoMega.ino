
#include "BeltDrivenMotionSystem.h"
#include "DriveScrewMotionSystem.h"
#include "StepperDriver.h"
#include "TimerThree.h"

#define PWM_PERIOD 50
#define BAUD_RATE 9600

#define ENABLE_X_PIN 25//enable pin turns the stepper driver on
#define DIR_X_PIN 23//direction pin for x axis stepper motor driver
#define STEP_X_PIN 3 //step pin for x axis stepper motor driver

#define ENABLE_Y_PIN 22//enable pin turns the stepper driver on
#define DIR_Y_PIN 24//direction pin for y axis stepper motor driver
#define STEP_Y_PIN 5//step pin for y axis stepper motor driver

#define ENABLE_Z_PIN 27//enable pin turns the stepper driver on
#define DIR_Z_PIN 29//direction pin for z axis stepper motor driver
#define STEP_Z_PIN 2//step pin for z axis stepper motor driver

#define HOME_X_PIN 49 //home pin determines if the motor is in the home position
#define HOME_Y_PIN 47 //home pin determines if the motor is in the home position
#define HOME_Z_PIN 45 //home pin determines if the motor is in the home position


#define TRAVEL_LENGTH_X 300.0
#define NUMBER_STEPS_PER_TURN_X 200
#define MICROSTEPPING_X 32
#define DIAMETER_X 16.0


#define TRAVEL_LENGTH_Y 345.0
#define NUMBER_STEPS_PER_TURN_Y 200
#define MICROSTEPPING_Y 32
#define BELT_PITCH_Y 2
#define PULLEY_TOOTH_COUNT_Y 30

#define TRAVEL_LENGTH_Z 300.0
#define NUMBER_STEPS_PER_TURN_Z 200
#define MICROSTEPPING_Z 32
#define DIAMETER_Z 16.0

DriveScrewMotionSystem motionSystemX(TRAVEL_LENGTH_X, NUMBER_STEPS_PER_TURN_X, MICROSTEPPING_X, DIAMETER_X);
//BeltDrivenMotionSystem motionSystemY(TRAVEL_LENGTH_Y, NUMBER_STEPS_PER_TURN_Y, MICROSTEPPING_Y, BELT_PITCH_Y, PULLEY_TOOTH_COUNT_Y);
//DriveScrewMotionSystem motionSystemZ(TRAVEL_LENGTH_Z, NUMBER_STEPS_PER_TURN_Z, MICROSTEPPING_Z, DIAMETER_Z);

/** The stepper motor driver for the X-axis.*/
StepperDriver stepperX(ENABLE_X_PIN, DIR_X_PIN, STEP_X_PIN, HOME_X_PIN, &motionSystemX);

/** The stepper motor driver for the Y-axis.*/
//StepperDriver stepperY(ENABLE_Y_PIN, DIR_Y_PIN, STEP_Y_PIN, HOME_Y_PIN, &motionSystemY);

/** The stepper motor driver for the Z-axis.*/
//StepperDriver stepperZ(ENABLE_Z_PIN, DIR_Z_PIN, STEP_Z_PIN, HOME_Z_PIN, &motionSystemZ);

void timerISR() {
  stepperX.isr();
  //stepperY.isr();
  //stepperZ.isr();
}

void setup() {
  Timer3.initialize(PWM_PERIOD);
  Timer3.attachInterrupt(timerISR);
  stepperX.init();
  //stepperY.init();
  //stepperZ.init();

  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("ready");
}

void loop(){
   String receivedCommand = Serial.readStringUntil('\n');
   if (!receivedCommand.equals("")) {
    
   }
}

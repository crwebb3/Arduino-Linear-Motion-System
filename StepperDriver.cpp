/**



  @author  Christopher Webb
  @version 1.0
  @since   2018-12-1
*/
#include "math.h"

#include "StepperDriver.h"
#include "TimerThree.h"


StepperDriver::StepperDriver(int enablePin, int dirPin, int stepPin, int homePin, MotionSystem* motionSystem) {
  this->enablePin = enablePin;
  this->dirPin = dirPin;
  this->stepPin = stepPin;
  this->homePin = homePin;
  this->motionSystem = motionSystem;
  init();
}

void StepperDriver::init() {
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); //turns the stepper motor driver on when set low
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(homePin, INPUT);

  Timer3.disablePwm(stepPin);
  digitalWrite(stepPin, LOW);

  setDirection(DIR_FORWARD);
}

bool StepperDriver::isHome() {
#ifndef HOME_PINS_NOT_CONNECTED
  if (digitalRead(homePin) == HIGH) {
    return true;
  } else if (digitalRead(homePin) == LOW) {
    return false;
  }
#endif
#ifdef HOME_PINS_NOT_CONNECTED
  return (getStepPos() == 0);
#endif

}

unsigned int StepperDriver::getStepPos() {
  return stepPos;
}


unsigned int StepperDriver::getMaxStepPos() {
  return motionSystem->getMaxStepPos();
}


uint8_t StepperDriver::getDirection() {
  return dir;
}

void StepperDriver::setDirection(uint8_t dir) {
  if (dir == HIGH || dir == LOW) {
    if (getDirection() != dir) { //only write to the pin if the direction needs to be changed.
      digitalWrite(dirPin, dir);
      this->dir = dir;
    }
  } else {
    Serial.println("Not a valid Direction");
  }
}

void StepperDriver::flipDirection() {
  if (getDirection() == LOW) {
    setDirection(HIGH);
  } else {
    setDirection(LOW);
  }
}

void StepperDriver::setStepsRemaining(unsigned long stepsRemaining) {
  this->stepsRemaining = stepsRemaining;
}

void StepperDriver::setMoving(bool moving) {
  this->moving = moving;
}

void StepperDriver::disablePWM() {
  Timer3.disablePwm(stepPin);
  digitalWrite(stepPin, LOW);
}

void StepperDriver::enablePWM() {
  Timer3.pwm(stepPin, 512);   // setup pwm on pin 9, 50% duty cycle
}

bool StepperDriver::isMoving() {
  return moving;
}

void StepperDriver::incrementStepPos(){
  if (getDirection() == DIR_FORWARD) {
    stepPos++;
  } else if (getDirection() == DIR_BACK) {
    if(stepPos>0){
      stepPos--;
    }
  }
}

void StepperDriver::isr() {
  if (isMoving()) {
    incrementStepPos();
    if (--stepsRemaining==0) {
      disablePWM();
      setMoving(false);
    }
  } else {
    if (stoppedCountDown != 0) {
      stoppedCountDown--;
    } else if (isDelayed()) {
      flipDirection();
      startMovement();
    }
  }
}

float StepperDriver::getPos() {
  return motionSystem->convertStepCountToPos(getStepPos());
}

bool StepperDriver::isAbleToMoveTo(float pos) {
  return (pos>-0.1 && motionSystem->convertPosToStepCount(pos) <= getMaxStepPos());
}

void StepperDriver::setDestination(float pos) {
  unsigned long destination = motionSystem->convertPosToStepCount(pos);
  uint8_t nextDir;
  unsigned long currentStepPos;
  unsigned long newStepsRemaining;
  bool nextMoving;
  noInterrupts();
  currentStepPos = getStepPos();
  if(destination > getMaxStepPos()){
    destination=getMaxStepPos();  
  }
  if (destination > currentStepPos) {
    nextDir = DIR_FORWARD;
    newStepsRemaining = destination - currentStepPos;
  } else if (destination < currentStepPos) {
    nextDir = DIR_BACK;
    newStepsRemaining = currentStepPos - destination;
  } else {
    stopMoving();
    return;
  }
  
  setStepsRemaining(newStepsRemaining);
  if(getDirection()==nextDir){
    startMovement();
  }else{
    startDelayedMovement();//the movement is delayed so that the motor will only flip directions after comming to a complete stop.
  }
  interrupts();
}

void StepperDriver::startMovement(){
  stoppedCountDown=INITIAL_STOPPED_COUNT;//reset the stoppedCountDown after any movement starts
  setMoving(true);
  setDelay(false);
  enablePWM();  
}

void StepperDriver::startDelayedMovement(){
  setDelay(true);
  setMoving(false);//stop movement until the delay is over
}

void StepperDriver::stopMoving(){
  noInterrupts();
  setMoving(false);
  setDelay(false);
  setStepsRemaining(0);
  interrupts();
}



void StepperDriver::setDelay(bool delaying){
  this->delaying=delaying;  
}

bool StepperDriver::isDelayed(){
  return delaying;  
}

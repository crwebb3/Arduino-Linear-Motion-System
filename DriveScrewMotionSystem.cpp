#include "DriveScrewMotionSystem.h"

  
DriveScrewMotionSystem::DriveScrewMotionSystem(float travelLength, unsigned int numberStepsPerTurn, unsigned int microstepping, float diameter, float gearRatio){
  this->travelLength=travelLength;
  this->numberStepsPerTurn=static_cast<float>(numberStepsPerTurn);
  this->microstepping=static_cast<float>(microstepping);
  this->pitch=3.1415926535897932384626433832795*diameter;
  this->gearRatio=gearRatio;
  
}


unsigned long DriveScrewMotionSystem::convertPosToStepCount(float pos){
  return static_cast<unsigned long>((gearRatio*pos*numberStepsPerTurn*microstepping)/(pitch));
}

float DriveScrewMotionSystem::convertStepCountToPos(unsigned long stepCount){
  return static_cast<float>((stepCount*pitch)/(microstepping*numberStepsPerTurn*gearRatio));   
}

unsigned long DriveScrewMotionSystem::getMaxStepPos(){
  return convertPosToStepCount(travelLength);
}

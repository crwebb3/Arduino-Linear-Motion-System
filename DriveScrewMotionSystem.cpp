#include "DriveScrewMotionSystem.h"

  
DriveScrewMotionSystem::DriveScrewMotionSystem(double travelLength, unsigned int numberStepsPerTurn, unsigned int microstepping, double diameter, double gearRatio){
  this->travelLength=travelLength;
  this->numberStepsPerTurn=static_cast<double>(numberStepsPerTurn);
  this->microstepping=static_cast<double>(microstepping);
  this->pitch=3.1415926535897932384626433832795*diameter;
  this->gearRatio=gearRatio;
  
}


unsigned long DriveScrewMotionSystem::convertPosToStepCount(double pos){
  return static_cast<unsigned long>((gearRatio*pos*numberStepsPerTurn*microstepping)/(pitch));
}

double DriveScrewMotionSystem::convertStepCountToPos(unsigned long stepCount){
  return static_cast<double>((stepCount*pitch)/(microstepping*numberStepsPerTurn*gearRatio));   
}

unsigned long DriveScrewMotionSystem::getMaxStepPos(){
  return convertPosToStepCount(travelLength);
}

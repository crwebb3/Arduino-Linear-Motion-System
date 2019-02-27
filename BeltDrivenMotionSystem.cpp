#include "BeltDrivenMotionSystem.h"

BeltDrivenMotionSystem::BeltDrivenMotionSystem(double travelLength, unsigned int numberStepsPerTurn, unsigned int microstepping, unsigned int beltPitch, unsigned int pulleyToothCount,double gearRatio){
  this->travelLength=travelLength;
  this->numberStepsPerTurn=static_cast<double>(numberStepsPerTurn);
  this->microstepping=static_cast<double>(microstepping);
  this->beltPitch=static_cast<double>(beltPitch);
  this->pulleyToothCount=static_cast<double>(pulleyToothCount);
  this->gearRatio=gearRatio;
}

unsigned long BeltDrivenMotionSystem::convertPosToStepCount(double pos){
  return static_cast<unsigned long>((gearRatio*pos*numberStepsPerTurn*microstepping)/(beltPitch*pulleyToothCount));
}

double BeltDrivenMotionSystem::convertStepCountToPos(unsigned long stepCount){
  return static_cast<double>((stepCount*pulleyToothCount*beltPitch)/(microstepping*numberStepsPerTurn*gearRatio));   
}

unsigned long BeltDrivenMotionSystem::getMaxStepPos(){
  return convertPosToStepCount(travelLength);
}

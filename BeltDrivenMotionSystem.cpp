#include "BeltDrivenMotionSystem.h"

BeltDrivenMotionSystem::BeltDrivenMotionSystem(float travelLength, unsigned int numberStepsPerTurn, unsigned int microstepping, unsigned int beltPitch, unsigned int pulleyToothCount){
  this->travelLength=travelLength;
  this->numberStepsPerTurn=static_cast<float>(numberStepsPerTurn);
  this->microstepping=static_cast<float>(microstepping);
  this->beltPitch=static_cast<float>(beltPitch);
  this->pulleyToothCount=static_cast<float>(pulleyToothCount);
}

unsigned long BeltDrivenMotionSystem::convertPosToStepCount(float pos){
  //return static_cast<unsigned long>(pos);
  return static_cast<unsigned long>((pos*numberStepsPerTurn*microstepping)/(beltPitch*pulleyToothCount));
}

float BeltDrivenMotionSystem::convertStepCountToPos(unsigned long stepCount){
  //return static_cast<float>(stepCount);
  return static_cast<float>((stepCount*pulleyToothCount*beltPitch)/(microstepping*numberStepsPerTurn));   
}

unsigned long BeltDrivenMotionSystem::getMaxStepPos(){
  return convertPosToStepCount(travelLength);
}

#include "DriveScrewMotionSystem.h"

  
DriveScrewMotionSystem::DriveScrewMotionSystem(float travelLength, unsigned int numberStepsPerTurn, unsigned int microstepping, float diameter){
  this->travelLength=travelLength;
  this->numberStepsPerTurn=static_cast<float>(numberStepsPerTurn);
  this->microstepping=static_cast<float>(microstepping);
  this->pitch=3.1415926535897932384626433832795*diameter;
  
}

/*DriveScrewMotionSystem::DriveScrewMotionSystem(float travelLength, unsigned int numberStepsPerTurn, unsigned int microstepping, float pitch){
  this->travelLength=travelLength;
  this->numberStepsPerTurn=static_cast<float>(numberStepsPerTurn);
  this->microstepping=static_cast<float>(microstepping);
  this->pitch=pitch;
  
}*/

unsigned long DriveScrewMotionSystem::convertPosToStepCount(float pos){
  //return static_cast<unsigned long>(pos);
  return static_cast<unsigned long>((magicNumber*pos*numberStepsPerTurn*microstepping)/(pitch));
}

float DriveScrewMotionSystem::convertStepCountToPos(unsigned long stepCount){
  //return static_cast<float>(stepCount);
  return static_cast<float>((stepCount*pitch)/(microstepping*numberStepsPerTurn*magicNumber));   
}

unsigned long DriveScrewMotionSystem::getMaxStepPos(){
  return convertPosToStepCount(travelLength);
}

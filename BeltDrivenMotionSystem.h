#ifndef BELT_DRIVEN_MOTION_SYSTEM_H_
#define BELT_DRIVEN_MOTION_SYSTEM_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "MotionSystem.h"

class BeltDrivenMotionSystem: public MotionSystem{
  private:
  
  float travelLength;
  float numberStepsPerTurn;
  float microstepping;
  float beltPitch;
  float pulleyToothCount;
  
  public:
  BeltDrivenMotionSystem(float travelLength, unsigned int numberStepsPerTurn, unsigned int microstepping, unsigned int beltPitch, unsigned int pulleyToothCount);
  
   /**
   *@param pos the position in milimeters that needs to be converted to a stepCount;
   *@return the number of micro steps needed for the system to move by 1mm.
   */ 
  unsigned long convertPosToStepCount(float pos);

  /**
   * @param stepCount the number of steps that needs to be converted to a pos in milimeters
   */
  float convertStepCountToPos(unsigned long stepCount);

  /**
   * @return the maximum step position given the motion systems travel length
   */
  unsigned long getMaxStepPos();

};

#endif

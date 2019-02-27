#ifndef MOTION_SYSTEM_H_
#define MOTION_SYSTEM_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class MotionSystem{

  private:

  public:
  
  /**
   *@param pos the position in milimeters that needs to be converted to a stepCount;
   *@return the number of micro steps needed for the system to move by 1mm.
   */ 
  virtual unsigned long convertPosToStepCount(float pos) = 0;

  /**
   * @param stepCount the number of steps that needs to be converted to a pos in milimeters
   */
  virtual float convertStepCountToPos(unsigned long stepCount) = 0;

  /**
   * @return the maximum step position given the motion systems travel length
   */
  virtual unsigned long getMaxStepPos() = 0;
  
};



#endif

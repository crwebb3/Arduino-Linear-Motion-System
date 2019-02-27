#ifndef DRIVE_SCREW_MOTION_SYSTEM_H_
#define DRIVE_SCREW_MOTION_SYSTEM_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "MotionSystem.h"

class DriveScrewMotionSystem: public MotionSystem{
  private:
  
  double travelLength;
  double numberStepsPerTurn;
  double microstepping;
  double pitch;
  double gearRatio;
  
  
  public:
  DriveScrewMotionSystem(double travelLength, unsigned int numberStepsPerTurn, unsigned int microstepping, double diameter, double gearRatio);

  
   /**
   *@param pos the position in milimeters that needs to be converted to a stepCount;
   *@return the number of micro steps needed for the system to move by 1mm.
   */ 
  unsigned long convertPosToStepCount(double pos);

  /**
   * @param stepCount the number of steps that needs to be converted to a pos in milimeters
   */
  double convertStepCountToPos(unsigned long stepCount);
  
  /**
   * @return the maximum step position given the motion systems travel length
   */
  unsigned long getMaxStepPos();


};

#endif

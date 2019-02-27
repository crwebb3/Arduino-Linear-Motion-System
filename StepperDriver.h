/**



  @author  Christopher Webb
  @version 1.0
  @since   2018-12-1
*/

#ifndef STEPPER_DRIVER_BASE_H
#define STEPPER_DRIVER_BASE_H
#include <Arduino.h>
#include "TimerThree.h"
#include "MotionSystem.h"

class StepperDriver {
  private:
    int enablePin;
    int dirPin;
    int stepPin;
    int homePin;
    MotionSystem* motionSystem;

    const unsigned int INITIAL_STOPPED_COUNT = 10;
    const uint8_t DIR_FORWARD = HIGH;
	  const uint8_t DIR_BACK = LOW;

    uint8_t dir;

    /**
       The number of steps that the axis has moved away from the home position
    */
    volatile unsigned long stepPos;

    /**
       The number of steps needed to move the axis to the desired position.
    */
    unsigned long stepsRemaining;

    /**
       The amount of time since the axis has stopped moving
    */
    unsigned timeStopped;

    /**
      Is true if axis is currently moving.
    */
    bool moving;

    bool delaying;

    unsigned int stoppedCountDown;

    void setDelay(bool delaying);

   

    

    /**
       A setter for the direction of the stepper driver.
       @param dir uint8_t The direction that the direction pin will be set too.
       The value is either FOWARD or BACK which correlate to HIGH or LOW.
       @return Nothing.
    */
    void setDirection(uint8_t dir);

    /**
       Flips the current direction that the stepper driver is set to. If the
       driver is set to FORWARD, then it will be changed to BACK. If the
       driver is set to BACK, then it will be set to FORWARD.
       @return Nothing.
    */
    void flipDirection();

    /**
       setter for stepsRemaining
    */
    void setStepsRemaining(unsigned long stepsRemaining);

    /**
       setter for moving
    */
    void setMoving(bool moving);

    void incrementStepPos();

    void startMovement();

    void startDelayedMovement();

     /**

    */
    void disablePWM();

    /**

    */
    void enablePWM();

  public:
    /**
       Class constructor
       @param dirPin The pin number that controls the direction of the stepper driver.
       @param stepPin The pin number that controls the pwm of stepper driver.
       @param homePin The pin number that the home switch is connected to.
       @param maxPos The max position that the motor can drive rod.
    */
    StepperDriver(int enablePin, int dirPin, int stepPin, int homePin, MotionSystem* motionSystem);


    /**
      Initializes the pins
      @return Nothing.
    */
    void init();

    /**
       Determines if the home switch is pressed.
       return bool True if the home switch is pressed.
    */
    bool isHome();

    /**
       Getter for the pos class variable.
       @return unsigned int The pos class variable.
    */
    unsigned int getStepPos();

    unsigned int getMaxStepPos();

    /**
       A getter for the moving field
       @return true if the axis is currently moving
    */
    boolean isMoving();

     bool isDelayed();

    /**
       The function that needs called by the timer ISR
    */
    void isr();

    /**
       @return the pos in milimeters that the axis is currently in.
    */
    float getPos();

    /**
       @param pos the position along the axis in milimeters
       @return true if the axis can move to the specified position in milimeters;
    */
    boolean isAbleToMoveTo(float pos);

    /**

    */
    void setDestination(float pos);

    /**

    */
    void stopMoving();

    /**
       A getter for the direction of the stepper driver. Checks the direction
       pin to see if is configured for the motor to go forwards or backwards.
       @return uint8_t HIGH or LOW based on the value on the direction pin.
       These values correlate to the the macros FORWARD and BACK as dictated
       in the macros file.
    */
    uint8_t getDirection();
};

#endif

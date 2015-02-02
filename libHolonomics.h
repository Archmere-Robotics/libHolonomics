//include guard
#ifndef _LIBHOLO_H
#define _LIBHOLO_H


//some nice constants; this part should be in it's own file, but I'm lazy...
#if 0==1
//#ifndef INT_MIN
  #define INT_MIN -32767
  #define INT_MAX 32767
#endif
//macro for converting floats to ints. (convinence)
#if defined(LONG_MIN) && defined(LONG_MAX)
	#define lround(x) ((x) < LONG_MIN-0.5 || (x) > LONG_MAX+0.5 ?\error() : ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#else
	#define lround(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#endif
#if defined(INT_MIN) && defined(INT_MAX)
#define iround(x) ((x) < INT_MIN-0.5 || (x) > INT_MAX+0.5 ?\error() : ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))
#else
#define iround(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))
#endif
#define maxof2(a,b) (a>b?a:b)
#define maxof4(a,b,c,d) (maxof2(maxof2(a,b),maxof2(c,d)))



//define constants for motors
#define LIFT_DOWN -20
#define LIFT_UP_FAST 50
#define LIFT_UP_SLOW 25
#define LIFT_STOP 0
#define DUMPSERVO_FLAT 168//value for the PVC dump servo to be flat
#define DUMPSERVO_RIGHT 148
#define CONVEYOR_UP 30
#define CONVEYOR_STOP 0
#define CONVEYOR_DOWN -30
#define RIGHT_IR_UP 24 //0
#define LEFT_IR_UP 31
#define LEFT_IR_DOWN 245
#define RIGHT_IR_DOWN 210 //233
#define SWEEPER_POWER 75
#define HOOK_POWER	30
#define RIGHT_HOOK_UP 111
#define RIGHT_HOOK_DOWN 33
const float	MOTOR_MAX = 100.0;
//determines if the servos are active
int dumpservo_pos;
bool dumpActive;
int liftSpeed;
int conveyorSpeed;
bool conveyorActive;
bool leftIRActive;
bool rightIRActive;
unsigned int liftTarget;
bool liftAuto;
int rightHookPos;
float vecX;
float vecY;
float vecZ;
//functiondec
/**
 * Stops all motors. Note: Does NOT deactivate servos; you might want to see deactivateServos();
 */
void Stop();
/**
 * Moves motors immediately.
 * NOTE: you probably shouldn't be using this function, because it doesn't support more complex movement (i.e., turning while moving forward).
 * You should be using addVal(int wA, int wB, int wC, int wD);
 * @param (int)wA Motor power for wheel A
 * @param (int)wB Motor power for wheel B
 * @param (int)wC Motor power for wheel C
 * @param (int)wD Motor power for wheel D
 */
void cDir(int wA, int wB, int wC, int wD);
/**
 * Multiplies variables ra, rb, rc, and rd by (abs(mod2))/100f to normalize values over 100 while protecting ratios.
 * This should only really be called by loadVal().
 * @param mod2 percentage to modify values by.
 */
void addRotation(float dRotation);
void addRotation(int dRotation);
void addVector(float x, float y);
void addVector(int x, int y);
void addMovement(float x, float y, float dRotation);
void addMovement(int x, int y, int dRotation);
/**
 * Pushes motor values to motors.
 * Normalizes values over 100 or under -100, and perserves ratios by using normalize()
 * Also outputs motor values to 1st 4 lines of display.
 * Finally resets vector variables
 */
void loadVal();

void updateServos();
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_igetLiftSpeed)
/**
 * Gets basket position as an integer. Note that the value returned are the theoretical values that are sent to the basket
 * servo, not the actual values.
 * @return (int) basket position
 */
int igetLiftSpeed();
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_bgetLiftSpeed)
/**
 * Gets the basket position as an boolean. True means the basket is up, false means it is down. Note that the value returned
 * are the theoretical values that are sent to the basket servo, not the actual values. Basically just a wrapper for
 * igetBasketPos();
 */
bool bgetLiftSpeed();
#endif
#if defined(USING_ALL) || defined(USING_setLiftSpeed)
/**TODO: document more
 * Sets the lift speed.
 * @param (int)i new servo position
 */
void setLiftSpeed(int i);
#endif
#if defined(USING_ALL) || defined(USING_setLiftPos)
/**TODO: document
 * Sets the basket position. If up==true, then it sets it the basket up, otherwise it sets the basket down.
 * @param (int)dir direction to move lift
 * @param (bool)fast speed to move lift
 */
void setLiftPos(int dir, bool fast);
#endif
#if  defined(USING_ALL) || defined(USING_moveConveyor)
bool moveConveyor(int speed);
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_deactivateServos)
void deactivateServos();
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_activateServos)
void activateServos();
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_getPos)
int getPos();
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_resetPos)
void resetPos();
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setDump)
void setDump(int pos);
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setLiftTarget)
void setLiftTarget(unsigned int target);
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setLiftAuto)
void setLiftAuto(bool aflag);
#endif
#if defined(USING_ALL) || defined(USING_setRightHook)
void setRightHook(int pos);
void setRightHook(bool up);
#endif
#endif

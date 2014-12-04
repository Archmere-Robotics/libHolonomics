//include guard
#ifndef _LIBHOLO_H
#define _LIBHOLO_H
//define constants for motors
#define LIFT_DOWN -15
#define LIFT_UP_FAST 100
#define LIFT_UP_SLOW 25
#define LIFT_STOP 0
#define DUMPSERVO_FLAT 180//value for the PVC dump servo to be balanced
#define DUMPSERVO_LEFT 200
#define DUMPSERVO_RIGHT 160
#define CONVEYOR_UP 30
#define CONVEYOR_STOP 0
#define CONVEYOR_DOWN -5
#define DOOR_OPEN 240
#define DOOR_CLOSED 75
const float	MOTOR_MAX = 100.0;
//determines if the servos are active
int dumpservo_pos;
bool dumpActive;
int liftSpeed;
int conveyorSpeed;
bool conveyorActive;
int doorservo_pos;
bool doorActive;
unsigned int liftTarget;
bool liftAuto;
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
 * Moves motors immediately, and sets basket position.
 * NOTE: you probably shouldn't be using this function, because it doesn't support more complex movement (i.e., turning while moving forward).
 * You should be using addVal(int wA, int wB, int wC, int wD);
 * @param (int)wA Motor power for wheel A
 * @param (int)wB Motor power for wheel B
 * @param (int)wC Motor power for wheel C
 * @param (int)wD Motor power for wheel D
 * @param (int)lPos Position to send basket servo
 */
void cDir(int wA, int wB, int wC, int wD, int lpos);
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_rotate)
/**
 * Rotates at speed p.
 * NOTE: you probably shouldn't be using this function, because it doesn't support more complex movement (i.e., turning while moving forward).
 * You should be using addVal(int wA, int wB, int wC, int wD);
 * @param (int)p Speed to rotate
 */
void rotate(int p);
#endif
/**
 * Wow... How do I describe this function?
 * @param (int)wA
 * @param (int)wB
 * @param (int)wC
 * @param (int)wD
 */
void addVal(int wA, int wB, int wC, int wD);
/**
 * Multiplies variables ra, rb, rc, and rd by (abs(mod2))/100f to normalize values over 100 while protecting ratios.
 * This should only really be called by loadVal().
 * @param mod2 percentage to modify values by.
 */
void normalize(int mod2);
/**
 * Pushes motor values to motors.
 * Normalizes values over 100 or under -100, and perserves ratios by using normalize()
 * Also outputs motor values to 1st 4 lines of display.
 * Finally resets ra-rd
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
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setLiftSpeed)
/**TODO: document more
 * Sets the lift speed.
 * @param (int)i new servo position
 */
void setLiftSpeed(int i);
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setLiftPos)
/**TODO: document
 * Sets the basket position. If up==true, then it sets it the basket up, otherwise it sets the basket down.
 * @param (int)dir direction to move lift
 * @param (bool)fast speed to move lift
 */
void setLiftPos(int dir, bool fast);
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_moveConveyor)
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
#endif

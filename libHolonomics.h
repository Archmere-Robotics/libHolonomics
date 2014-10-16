//include guard
#ifndef _LIBHOLO_H
#define _LIBHOLO_H

#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S3, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S4, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Drivetrain,     sensorI2CMuxController)
#pragma config(Sensor, S4,     Auxillary,      sensorI2CMuxController)
#pragma config(Motor,  mtr_S3_C1_1,     wheelA,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C1_2,     wheelB,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C2_1,     wheelC,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     wheelD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_1,     winch,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     hookLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_1,     conveyorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_2,     flagLift,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    hook,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_1,    basket,               tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    conveyorLift,         tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S4_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S4_C1_6,    servo12,              tServoNone)

//functiondef
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
/**
 * Rotates at speed p.
 * NOTE: you probably shouldn't be using this function, because it doesn't support more complex movement (i.e., turning while moving forward).
 * You should be using addVal(int wA, int wB, int wC, int wD);
 * @param (int)p Speed to rotate
 */
void rotate(int p);
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
/**
 * Gets basket position as an integer. Note that the value returned are the theoretical values that are sent to the basket
 * servo, not the actual values.
 * @return (int) basket position
 */
int igetBasketPos();
/**
 * Gets the basket position as an boolean. True means the basket is up, false means it is down. Note that the value returned
 * are the theoretical values that are sent to the basket servo, not the actual values. Basically just a wrapper for
 * igetBasketPos();
 */
bool bgetBasketPos();
/**
 * Sets the basket position. Note that this function will not actually move the basket immediately; you need to call
 * updateServos() a few times over a sec. to actually move the basket.
 * @param (int)i new servo position
 */
void setBasketPos(int i);
/**
 * Sets the basket position. If up==true, then it sets it the basket up, otherwise it sets the basket down. Note that this
 * function will not actually move the basket immediately; you need to call updateServos() a few times over a sec.
 * to actually move the basket.
 * @param (bool)up direction to move basket.
 */
void setBasketPos(bool up);
bool moveConveyor(bool up);
void deactivateServos();
void activateServos();
int getPos();
void resetPos();
void moveFlag(int i);
void liftHook(int i);
void moveWinch(int i);
void setHookPos(int i);
#endif

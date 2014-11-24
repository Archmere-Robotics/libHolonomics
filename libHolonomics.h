#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          heartbeat,     tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          leftHook,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightHook,     tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     liftRightMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     liftLeftMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     wheelB,        tmotorTetrix, PIDControl, driveLeft)
#pragma config(Motor,  mtr_S1_C2_2,     wheelA,        tmotorTetrix, PIDControl, driveRight)
#pragma config(Motor,  mtr_S1_C3_1,     collectorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     wheelC,        tmotorTetrix, PIDControl, driveRight)
#pragma config(Motor,  mtr_S2_C2_2,     wheelD,        tmotorTetrix, PIDControl, driveLeft)
#pragma config(Servo,  srvo_S2_C1_1,    dumpServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    doorServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//include guard
#ifndef _LIBHOLO_H
#define _LIBHOLO_H
//define constants for motors
#define LIFT_DOWN 0
#define LIFT_UP_FAST 40
#define LIFT_UP_SLOW 30
#define LIFT_STOP 10
#define DUMPSERVO_FLAT 180//value for the PVC dump servo to be balanced
#define DUMPSERVO_LEFT 200
#define DUMPSERVO_RIGHT 160
#define CONVEYOR_UP 30
#define CONVEYOR_STOP 0
#define CONVEYOR_DOWN -5
#define DOOR_OPEN 250
#define DOOR_CLOSED 85
//determines if the servos are active
int dumpservo_pos;
bool dumpActive;
int liftSpeed;
int conveyorSpeed;
bool conveyorActive;
int doorservo_pos;
bool dooractive;
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
int igetLiftSpeed();
/**
 * Gets the basket position as an boolean. True means the basket is up, false means it is down. Note that the value returned
 * are the theoretical values that are sent to the basket servo, not the actual values. Basically just a wrapper for
 * igetBasketPos();
 */
bool bgetLiftSpeed();
/**TODO: document more
 * Sets the lift speed.
 * @param (int)i new servo position
 */
void setLiftSpeed(int i);
/**TODO: document
 * Sets the basket position. If up==true, then it sets it the basket up, otherwise it sets the basket down.
 * @param (int)dir direction to move lift
 * @param (bool)fast speed to move lift
 */
void setLiftPos(int dir, bool fast);
bool moveConveyor(int speed);
void deactivateServos();
void activateServos();
int getPos();
void resetPos();
void holoInit();
void setDump(int pos);
#endif

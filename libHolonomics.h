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

void addVal(int wA, int wB, int wC, int wD);
void normalize(int mod2);
void loadVal();
void updateServos();
int igetBasketPos();
bool bgetBasketPos();
void setBasketPos(int i);
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
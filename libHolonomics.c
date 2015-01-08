#include "libHolonomics.h"

//include guard
#ifndef _LIBHOLO_C
#define _LIBHOLO_C
/*
@author Liam Feehery
@awesomeBoxBot', and should be applicaple for any holonomic
drive, if you remove the extra functions.
@version ß1.1.1
This is the motor control library written for the FTC competition 'Block Party' (2013-2014 season).
It controlls the holonomic drive system for '
*/

//internal variable declarations/definitions
static int ra, rb, rc, rd=0;//motor values.
//stops everything
void Stop(){
	motor[wheelA]  = 0;
	motor[wheelB]  = 0;
	motor[wheelC]  = 0;
	motor[wheelD]  = 0;
	ra             = 0;
	rb             = 0;
	rc             = 0;
	rd             = 0;
	return;
}

//you shouldn't call this directly unless you're testing
void cDir(int wA, int wB, int wC, int wD) {
	motor[wheelA]  = wA;
	motor[wheelB]  = wB;
	motor[wheelC]  = wC;
	motor[wheelD]  = wD;
	return;
}

//for testing: rotates in place
#if defined(USING_rotate) || defined(HOLO_DEBUG)
void rotate(int p) {
	cDir(p,p,p,p);
}
#endif

void addVal(int wA, int wB, int wC, int wD) {
	ra = ra + wA;
	rb = rb + wB;
	rc = rc + wC;
	rd = rd + wD;
}

//fixes motor values
int normalize(int mod2) {
	if(abs(mod2)<MOTOR_MAX)return mod2;
	float mod = MOTOR_MAX/((float)abs(mod2));
	ra *= mod;
	rb *= mod;
	rc *= mod;
	rd *= mod;
	return mod2>0?MOTOR_MAX:-MOTOR_MAX;
}
#ifdef AWD
void applyAWD() {
	ra+=rotationOffset-vecX-vecY;
	rb+=rotationOffset+vecX-vecY;
	rc+=rotationOffset+vecX+vecY;
	rd+=rotationOffset-vecX+vecY;
	//now, update offset/vector
	int dRotation=nMotorEncoder[wheelA]+nMotorEncoder[wheelB]+nMotorEncoder[wheelC]+nMotorEncoder[wheelD];
	int dx=-nMotorEncoder[wheelA]+nMotorEncoder[wheelB]+nMotorEncoder[wheelC]-nMotorEncoder[wheelD];
	int dy=-nMotorEncoder[wheelA]-nMotorEncoder[wheelB]+nMotorEncoder[wheelC]+nMotorEncoder[wheelD];
	int aRotation=ra+rb+rc+rd;
	int ax=-ra+rb+rc-rd;
	int ay=-ra-rb+rc+rd;
	#ifdef DEBUG_AWD
		bDisplayDiagnostics=false;
		eraseDisplay();
	//	drawLine(50,32,50+(ax/8),32+(ay/12));
	//	drawLine(50,63,50+(aRotation/8),32);
	//	drawLine(50,32,50+(dx/8),32+(dy/12));
	//	drawLine(50,0,50+(dRotation/8),32);
		drawLine(33,32,33,32+(dy/6));
		drawLine(66,32,66,32+(dy/6));
	#endif
	nMotorEncoder[wheelA]=0;
	nMotorEncoder[wheelB]=0;
	nMotorEncoder[wheelC]=0;
	nMotorEncoder[wheelD]=0;
}
#endif

//makes stuff happen
void loadVal() {
	#ifdef DEBUG_MOTOR_VALUES
		//store values for display later
		int oldA=ra,oldB=rb,oldC=rc,oldD=rd;
	#endif
	//normalize values
	ra=normalize(ra);
	rb=normalize(rb);
	rc=normalize(rc);
	rd=normalize(rd);
	#ifdef AWD
		applyAWD();
	#endif
	//write values to the motors
	cDir(ra,rb,rc,rd);
	//now, set other non-drivetrain motors
	if(!liftAuto)
		motor[liftMotor]=liftSpeed;
	motor[collectorMotor]=conveyorSpeed;
	#ifdef DEBUG_MOTOR_VALUES
		//display motor values to screen
		nxtDisplayCenteredTextLine(1,"A: %3d -> %3d",oldA,ra);
		nxtDisplayCenteredTextLine(2,"B: %3d -> %3d",oldB,rb);
		nxtDisplayCenteredTextLine(3,"C: %3d -> %3d",oldC,rc);
		nxtDisplayCenteredTextLine(4,"D: %3d -> %3d",oldD,rd);
	#endif
	//reset internal motor values
	ra=0;
	rb=0;
	rc=0;
	rd=0;
}

//updates servo values. call once per cycle
void updateServos() {
	//move dump
	if(dumpActive){//checks if the lift servo is activated
		//if so, move lift
		servoChangeRate[dumpServo]=1;
		servo[dumpServo]=dumpservo_pos+DUMPSERVO_FLAT;
	}else
		servoChangeRate[dumpServo]=0;
	if(rightIRActive) {
		servoChangeRate[rightIRServo]=1;
		servo[rightIRServo]=RIGHT_SERVO_POS;
	}else
		servoChangeRate[rightIRServo]=1;
	if(leftIRActive){
		servoChangeRate[leftIRServo]=1;
		servo[leftIRServo]=LEFT_SERVO_POS;
	}else
		servoChangeRate[leftIRServo]=1;
	if(liftAuto) {
		int liftPos=nMotorEncoder[liftMotor];
		int spd=LIFT_STOP;
		if(abs(liftPos-liftTarget)>10){
			spd = ((liftTarget-liftPos));
			if(spd<LIFT_DOWN)
				spd = LIFT_DOWN;
			if(spd>70)
				spd = 70;
			motor[liftMotor]=spd;
			displayCenteredTextLine(3,"%d",spd);
		}
		motor[liftMotor]=spd;
	}
	servoChangeRate[rightHook]=5;
	servo[rightHook]=rightHookPos;
}

//returns lift position as integer
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_igetLiftSpeed)
int igetLiftSpeed() {
	return liftSpeed;
}
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_bgetLiftSpeed)
//returns lift position as boolean (lift up=true)
bool bgetLiftSpeed() {
	return (liftSpeed>0);
}
#endif

//sets lift position
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setLiftSpeed)
void setLiftSpeed(int i) {
	liftSpeed=i;
	if(liftSpeed>LIFT_UP_FAST)
		liftSpeed=LIFT_UP_FAST;
	if(liftSpeed<LIFT_DOWN)
		liftSpeed=LIFT_DOWN;
	liftAuto=false;
}
#endif

//better lift controller: lift can only go up/down/stop
//dir can be: >0 (up), <0 (down) or 0 (stop)
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setLiftPos)
void setLiftPos(int dir,bool fast) {
	if(dir>0)
		liftSpeed=fast?LIFT_UP_FAST:LIFT_UP_SLOW;
	else if(dir<0)
		liftSpeed=LIFT_DOWN;
	else
		liftSpeed=LIFT_STOP;
}
#endif

//moves queues conveyor for moving up/down
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_moveConveyor)
bool moveConveyor(int speed) {
	conveyorSpeed=speed;
	return true;
}
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_deactivateServos)
void deactivateServos() {
	conveyorActive=false;
	dumpActive=false;
}
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_activateServos)
void activateServos() {
	conveyorActive=true;
	dumpActive=true;
	rightIRActive=true;
	leftIRActive=true;
}
#endif

//returns encoder
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_getPos)
int getPos() {
	return nMotorEncoder[wheelA];
}
int getPos(int i){
	switch(i)	{
		case 1:
			return nMotorEncoder[wheelA];
		case 2:
			return nMotorEncoder[wheelB];
		case 3:
			return nMotorEncoder[wheelC];
		case 4:
			return nMotorEncoder[wheelD];
	}
	return 0;
}
#endif
//resets encoder
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_resetPos)
void resetPos() {
	nMotorEncoder[wheelA]= 0;
	nMotorEncoder[wheelC]=0;
}
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setDump)
void setDump(int pos) {
	dumpservo_pos=pos;
}
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setDoorPos)
//void setDoorPos(bool open) {
//	doorservo_pos=(open?DOOR_OPEN:DOOR_CLOSED);
//}
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setLiftTarget)
void setLiftTarget(unsigned int target) {
	liftTarget=target;
}
#endif
#if defined(HOLO_DEBUG) || defined(USING_ALL) || defined(USING_setLiftAuto)
void setLiftAuto(bool aflag){
	liftAuto=aflag;
}
#endif
#if defined(USING_ALL) || defined (USING_setRightHook)
void setRightHook(int pos) {
	rightHookPos=pos;
}
void setRightHook(bool up) {
	rightHookPos=up?RIGHT_HOOK_UP:RIGHT_HOOK_DOWN;
}
#endif
#endif

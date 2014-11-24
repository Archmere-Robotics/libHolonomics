#include "libHolonomics.h"

//include guard
#ifndef _LIBHOLO_C
#define _LIBHOLO_C
#define DEBUG_MOTOR_VALUES
/*
@author Liam Feehery
@awesome
@version ß1.1.1
This is the motor control library written for the FTC competition 'Block Party' (2013-2014 season).
It controlls the holonomic drive system for 'BoxBot', and should be applicaple for any holonomic
drive, if you remove the extra functions.
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

//you shouldn't call this directly unless you're testing
void cDir(int wA, int wB, int wC, int wD, int lpos) {
	motor[wheelA]  = wA;
	motor[wheelB]  = wB;
	motor[wheelC]  = wC;
	motor[wheelD]  = wD;
//	servoChangeRate[basket] = 5;
//	servo[basket]  = lpos;
	return;
}

//for testing: rotates in place
void rotate(int p) {
	cDir(p,p,p,p);
}

void addVal(int wA, int wB, int wC, int wD) {
	if(wA>100)
		wA = 100;
	if(wB>100)
		wB   = 100;
	if(wC>100)
		wC   = 100;
	if(wD>100)
		wD   = 100;
	ra = ra + wA;
	rb = rb + wB;
	rc = rc + wC;
	rd = rd + wD;
}

//fixes motor values
void normalize(int mod2) {
	float mod    = ((float)abs(mod2))/((float)100);
	ra *= mod;
	rb *= mod;
	rc *= mod;
	rd *= mod;
}

//makes stuff happen
void loadVal() {
	#ifdef DEBUG_MOTOR_VALUES
		//store values for display later
		int oldA=ra,oldB=rb,oldC=rc,oldD=rd;
	#endif
	//normalize values
	if(ra>100){
		normalize(ra);
		ra=100;
	}
	if(rb>100){
		normalize(rb);
		rb=100;
	}
	if(rc>100){
		normalize(rc);
		rc=100;
	}
	if(rd>100){
		normalize(rd);
		rd=100;
	}
	if(ra<-100){
		normalize(-ra);
		ra=-100;
	}
	if(rb<-100){
		normalize(-rb);
		rb=-100;
	}
	if(rc<-100){
		normalize(-rc);
		rc=-100;
	}
	if(rd<-100){
		normalize(-rd);
		rd=-100;
	}
	//write values to the motors
	cDir(ra,rb,rc,rd);
	//now, set other non-drivetrain motors
	motor[liftLeftMotor]=liftSpeed;
	motor[liftRightMotor]=liftSpeed;
	motor[collectorMotor]=conveyorSpeed;
	#ifdef DEBUG_MOTOR_VALUES
		string t1, t2, t3, t4;
		//build strings for display
		stringFormat(t1, "A: %3d -> %3d", oldA, ra);
		stringFormat(t2, "B: %3d -> %3d", oldB, rb);
		stringFormat(t3, "C: %3d -> %3d", oldC, rc);
		stringFormat(t4, "D: %3d -> %3d", oldD, rd);
		//display motor values to screen
		nxtDisplayCenteredTextLine(1,t1);
		nxtDisplayCenteredTextLine(2,t2);
		nxtDisplayCenteredTextLine(3,t3);
		nxtDisplayCenteredTextLine(4,t4);
	#endif
	//reset theoretical motor values
	ra=0;
	rb=0;
	rc=0;
	rd=0;
}

//updates servo values. call once per cycle
void updateServos() {
	//moves lift
	if(dumpActive){//checks if the lift servo is activated
		//if so, move lift
		servoChangeRate[dumpServo]=1;
		servo[dumpServo]=dumpservo_pos+DUMPSERVO_FLAT;
	}
	if(doorActive) {
		servoChangeRate[doorServo]=5;
		servo[doorServo]=doorservo_pos;
	}
}

//returns lift position as integer
int igetLiftSpeed() {
	return liftSpeed;
}

//returns lift position as boolean (lift up=true)
bool bgetLiftSpeed() {
	return (liftSpeed>0);
}

//sets lift position
void setLiftSpeed(int i) {
	liftSpeed=i;
	if(liftSpeed>LIFT_UP_FAST)
		liftSpeed=LIFT_UP_FAST;
	if(liftSpeed<LIFT_DOWN)
		liftSpeed=LIFT_DOWN;
}

//better lift controller: lift can only go up/down/stop
//dir can be: >0 (up), <0 (down) or 0 (stop)
void setLiftPos(int dir,bool fast) {
	if(dir>0)
		liftSpeed=fast?LIFT_UP_FAST:LIFT_UP_SLOW;
	else if(dir<0)
		liftSpeed=LIFT_DOWN;
	else
		liftSpeed=LIFT_STOP;
}

//moves queues conveyor for moving up/down
bool moveConveyor(int speed) {
	conveyorSpeed=speed;
	return true;
}
void deactivateServos() {
	conveyorActive=false;
	dumpActive=false;
}
void activateServos() {
	conveyorActive=true;
	dumpActive=true;
	doorActive=true;
}

//returns encoder
int getPos() {
	return nMotorEncoder[wheelA];
}
int getPos(int i){
	if(i==1){
		return nMotorEncoder[wheelA];
	}else{
		return nMotorEncoder[wheelC];
	}
}
//resets encoder
void resetPos() {
	nMotorEncoder[wheelA]= 0;
	nMotorEncoder[wheelC]=0;
}
void setDump(int pos) {
	dumpservo_pos=pos;
}
void setDoorPos(bool open) {
	doorservo_pos=(open?DOOR_OPEN:DOOR_CLOSED);
}
#endif

#include "libHolonomics.h"

const int convOut=173;
const int convIn=85;
const int basketUp=20;
const int basketDown=232;
/*
@author Liam Feehery
@awesome
@version ß1.1.1
This is the motor control library written for the FTC competition 'Block Party' (2013-2014 season).
It controlls the holonomic drive system for 'BoxBot', and should be applicaple for any holonomic
drive, if you remove the extra functions.
*/
int ra, rb, rc, rd=0;//motor values.
int b1pos=175;//lift value; 175 rests above conveyor
int hookPos=0;
bool conveyorUp=true;//determines if conveyor is up on robot
//determines if the servos are active
bool basketActive=false;
bool conveyorActive=false;
bool hookActive=false;
//stops everything
void Stop(){
	motor[wheelA]=0;
	motor[wheelB]=0;
	motor[wheelC]=0;
	motor[wheelD]=0;
	basketActive=false;
	conveyorActive=false;
	return;
}

//you shouldn't call this directly unless you're testing
void cDir(int wA, int wB, int wC, int wD) {
	motor[wheelA]=wA;
	motor[wheelB]=wB;
	motor[wheelC]=wC;
	motor[wheelD]=wD;
	return;
}

//you shouldn't call this directly unless you're testing
void cDir(int wA, int wB, int wC, int wD, int lpos) {
	motor[wheelA]=wA;
	motor[wheelB]=wB;
	motor[wheelC]=wC;
	motor[wheelD]=wD;
	servoChangeRate[basket]=5;
	servo[basket]=lpos;
	return;
}

//for testing: rotates in place
void rotate(int p) {
	cDir(p,p,p,p);
}

void addVal(int wA, int wB, int wC, int wD) {
	if(wA>100){wA=100;}
	if(wB>100){wB=100;}
	if(wC>100){wC=100;}
	if(wD>100){wD=100;}
	ra=ra + wA;
	rb=rb + wB;
	rc=rc + wC;
	rd=rd + wD;
}

//fixes motor values
void normalize(int mod2) {
	float mod=((float)abs(mod2))/((float)100);
	ra*=mod;
	rb*=mod;
	rc*=mod;
	rd*=mod;
}

//makes stuff happen
void loadVal() {
	if(ra>100){normalize(ra); ra=100;}
	if(rb>100){normalize(rb);rb=100;}
	if(rc>100){normalize(rc);rc=100;}
	if(rd>100){normalize(rd);rd=100;}
	if(ra<-100){normalize(-ra);ra=-100;}
	if(rb<-100){normalize(-rb);rb=-100;}
	if(rc<-100){normalize(-rc);rc=-100;}
	if(rd<-100){normalize(-rd);rd=-100;}
	cDir(ra,rb,rc,rd);
	string t1, t2, t3, t4;
	StringFormat(t1, "%4d", ra);
	StringFormat(t2, "%4d", rb);
	StringFormat(t3, "%4d", rc);
	StringFormat(t4, "%4d", rd);
	nxtDisplayCenteredTextLine(1,t1);
	nxtDisplayCenteredTextLine(2,t2);
	nxtDisplayCenteredTextLine(3,t3);
	nxtDisplayCenteredTextLine(4,t4);
	ra=0;
	rb=0;
	rc=0;
	rd=0;
}

//updates servo values. call once per cycle
void updateServos() {
	//moves lift
	if(basketActive){//checks if the lift servo is activated
		//if so, move lift
		servoChangeRate[basket]=5;
		servo[basket]=b1pos;
		}else{
		//do absolutely nothing
	}
	//move conveyor lift
	int convTarg;
	//update position for conveyor lift
	if(conveyorUp){
		convTarg=convOut;
		}else{
		convTarg=convIn;
	}
	if(conveyorActive){
		//check if the lift has to be moved
		if(abs(ServoValue[conveyorLift]-convTarg)>10){
			//move conveyor lift
			servo[conveyorLift]=convTarg;
			servoChangeRate[conveyorLift]=5;
			}else{
			//kill conveyor lift
		}
		}else{
		//do literally nothing
	}
	if(hookActive){
		if(abs(ServoValue[hook]-hookPos)>2){
			servo[hook]=hookPos;
			servoChangeRate[hook]=5;
		}
	}
}

//returns lift position as integer
int igetBasketPos() {
	return b1pos;
}

//returns lift position as boolean (lift up=true)
bool bgetBasketPos() {
	return (abs(b1pos-200)<10);
}

//sets lift position
void setBasketPos(int i) {
	b1pos=i;
	if(b1pos>200){b1pos=200;}
	if(b1pos<0){b1pos=0;}
}

//better lift controller: lift can only go up/down
void setBasketPos(bool up) {
	if(up){
		b1pos=basketUp;
		}else{
		b1pos=basketDown;
	}
}

//moves queues conveyor for moving up/down
bool moveConveyor(bool up) {
	bool cu=(conveyorUp==up);
	conveyorUp=up;
	return cu;
}
void deactivateServos() {
	conveyorActive=false;
	basketActive=false;
	hookActive=false;
}
void activateServos() {
	conveyorActive=true;
	basketActive=true;
	hookActive=true;
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

//controls flag motor
void moveFlag(int i) {
	motor[flagLift]=i;
	return;
}

//controls hook up or down
void liftHook(int i) {
	motor[hookLift]=i;
	return;
}

void moveWinch(int i) {
	motor[winch]=i;
	return;
}
void setHookPos(int i) {
	hookPos=i;
}

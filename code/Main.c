#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Motor,  port2,           Fr,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           Fl,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Bl,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           ForKt,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Br,            tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
void Flag(){
}
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
int count = 0;
//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}
// DATE == 10/27/18
/*
Fr = Front Right
Fl = Front Left
Br = Back Right
Bl = Back Left
ForK = Fork Lift
*/
//Func to stop motors
void stopMotors(){
	motor[Fr] = 0;
	motor[Fl] = 0;
	motor[Br] = 0;
	motor[Bl] = 0;
	motor[ForKt] = 0;
}
void ifs(){
	if(vexRT[Btn6U] == 1){
		motor[ForKt] = - 127;
	}
	else if(vexRT[Btn6D] == 1){
		motor[ForKt] =  127;
	}
	else{
		motor[ForKt] = 0;
	}
}
void clearLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}
void clearENC(){
	resetMotorEncoder(Fr);
	resetMotorEncoder(Fl);
	resetMotorEncoder(Br);
	resetMotorEncoder(Bl);
	resetMotorEncoder(ForKt);
}
// This code is for the VEX cortex platform
#pragma platform(VEX2)
// Select Download method as "competition"
#pragma competitionControl(Competition)
//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void pre_auton()
{
	//This is my br atun clearing LCD and turning on backlight
	bStopTasksBetweenModes = false;
	bLCDBacklight = true;
	clearLCD();
	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 4 different options
		switch(count){
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "lPBlue");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 3;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "LPRed");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Flag");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		default:
			count = 0;
			break;
		}
	}
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
task autonomous()
{
	clearLCDLine(0);
	clearLCDLine(1);
	//Switch Case that actually runs the user choice
	switch(count){
	case 0:
		//If count = 0, run the code correspoinding with choice 1
		displayLCDCenteredString(0, "lPBlue");
		displayLCDCenteredString(1, "is running!");

		break;
	case 1:
		//If count = 1, run the code correspoinding with choice 2
		displayLCDCenteredString(0, "LPRed");
		displayLCDCenteredString(1, "is running!");

		break;
	case 2:
		//If count = 2, run the code correspoinding with choice 3
		displayLCDCenteredString(0, "Flag");
		displayLCDCenteredString(1, "is running!");						
		Flag();
		break;
	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
/*
motor[Fr] = vexRT[Ch2];
motor[Br] = vexRT[Ch2];
motor[Fl] = vexRT[Ch3];
motor[Bl] = vexRT[Ch3];
*/
task usercontrol()
{
	while (true)
	{
		displayLCDCenteredString(0, "Its not delivery");
		displayLCDCenteredString(1, "its digorno");
		ifs();
		motor[Fr] = vexRT[Ch2];
 		motor[Br] = vexRT[Ch2];
 		motor[Fl] = vexRT[Ch3];
 		motor[Bl] = vexRT[Ch3];
	}
}
/*
--------------------------------------------------------------------------------------------------------------------------------
*/

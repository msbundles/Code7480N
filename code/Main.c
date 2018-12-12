#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  BL,             sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           Fr,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           Fl,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Bl,            tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port6,           Lift,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Fork,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Br,            tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

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
int count = 0;
/*
Fr = Front Right
Fl = Front Left
Br = Back Right
Bl = Back Left
ForK = Fork Lift
*/
//task to be lit
/*
task milan(){
while(1){
displayLCDCenteredString(0,"Proud NRA");
displayLCDCenteredString(1,"Member");
sleep(2000);
displayLCDCenteredString(0,"Prius Lives");
displayLCDCenteredString(1,"Matter");
sleep(2000);
}
}
*/
//Makes robot go forward for auton
/*
void forwardd(){
motor[Fr] = 127;
motor[Fl] = 127;
motor[Br] = 127;
motor[Bl] = 127;
}
//Makes robot go backward for auton
void backwardd(){
motor[Fr] = -127;
motor[Fl] = -127;
motor[Br] = -127;
motor[Bl] = -127;
}
//Makes robot turn right for auton
void turnR(){
motor[Fr] = -127;
motor[Fl] = 127;
motor[Br] = -127;
motor[Bl] = 127;
}
void turnL(){
motor[Fr] = 127;
motor[Fl] = -127;
motor[Br] = 127;
motor[Bl] = -127;
}

//If count = 0, run the code correspoinding with choice 1
displayLCDCenteredString(0, "RED");
displayLCDCenteredString(1, "is running!");
//Flag toggle
forwardd();
sleep(2000);
stopMotors();
//Getting in position for parking
backwardd();
sleep(2500);
stopMotors();
// turning twards platform
turnR();
sleep(2000);
stopMotors();
//Parking on platform
forwardd();
sleep(2000);
stopMotors();
break;
*/

void ifs(){
	if(vexRT[Btn6U] == 1){
		motor[Lift] = - 127;
	}
	else if(vexRT[Btn6D] == 1){
		motor[Lift] =  127;
	}
	else{
		motor[Lift] = 0;
	}
	if(vexRT[Btn5U] == 1){
		motor[Fork] = -60;
	}
	else if(vexRT[Btn5D] == 1){
		motor[Fork] =  60;
	}
	else{
		motor[Fork] = 0;
	}
}
//Makes robot stop for auton
void stopMotors(){
	motor[Fr] = 0;
	motor[Fl] = 0;
	motor[Br] = 0;
	motor[Bl] = 0;
}
void clearLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}
void resetEnc(){
	resetMotorEncoder(Bl);
}
void drive(int Fri,int Fli,int Bri,int Bli,int distance){
	while(abs(getMotorEncoder(Bl))<distance){
		motor[Fr] = Fri;
		motor[Fl] = Fli;
		motor[Br] = Bri;
		motor[Bl] = Bli;
	}
	stopMotors();
	resetEnc();
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
	//starting milan
	// House keeping things.
	bDisplayCompetitionStatusOnLcd = false;
	bStopTasksBetweenModes = true;
	//Turning lcd backlight on
	bLCDBacklight = true;
	//clearing lcd
	clearLCD();
	//clearing encoders
	resetEnc();

	//------------- Beginning of User Interface Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed
	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 4 different options
		switch(count){
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "RED");
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
			displayLCDCenteredString(0, "BLUE");
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
		}
	}
	clearLCD();
	displayLCDCenteredString(0, "Good Luck!!");
	displayLCDCenteredString(1, "Murphy's Law;)");

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
task autonomous(){
	//clearing encoders
	resetEnc();
	//Switch Case that actually runs the user choice
	/*
	drive(FR,FL,BR,BL,Distance);
	http://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Mobile_Robotics/VEX/Using_encoders_to_drive_some_distance
	*/
	switch(count){
	case 0:

		break;
	case 1:

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
Extra driver cide in case it gets lost.
motor[Fr] = vexRT[Ch2];
motor[Br] = vexRT[Ch2];
motor[Fl] = vexRT[Ch3];
motor[Bl] = vexRT[Ch3];
*/
task usercontrol()
{
	//startTask(milan);
	while (true)
	{
		//code for joystick buttons
		ifs();
		//code for joysticks
		motor[Fr] = vexRT[Ch2];
		motor[Br] = vexRT[Ch2];
		motor[Fl] = vexRT[Ch3];
		motor[Bl] = vexRT[Ch3];
	}

}

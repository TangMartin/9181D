#pragma config(Sensor, in1,    armPot,         sensorPotentiometer)
#pragma config(Sensor, in2,    gyro,           sensorGyro)
#pragma config(Motor,  port1,           backInnerLeftDrive, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           frontLeftDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           backOuterLeftDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftArm,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightArm,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           frontRightDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           backOuterRightDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          backInnerRightDrive, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"w
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Penguin_Competition_Includes.c"
#include "Autonomous.c"


int armPosition = 0;
int armTaskRunning = 0;

int autoNumber = 0; //Sets default autonomous to the 0th autonomous

#define NUM_AUTOS 4 //There are 4 different autonomous codes
string autoNames[] = {"Red 1","Red 2","Blue 1", "Blue 2"}; //Names for each auton



void setArm(int power);
void gyroTurn(int target);

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
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

  SensorType[gyro] = sensorNone;
  wait1Msec(1000);
  //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
  SensorType[gyro] = sensorGyro;
  wait1Msec(2000);

  SensorFullCount[gyro] = 36000;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
	switch(autoNumber)
	{
		case 0:
			gyroTurn(-900);
		break;

		case 1:
			RedAuto2();
		break;

		case 2:
			BlueAuto();
		break;

		case 3:
			BlueAuto2();
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

int motorCap(int power)
{
		if(power > 127)
			return 127;
	  else if(power < -127)
	  	return -127;
	  else
	  	return power;
}


task arm()
{
	armTaskRunning = 1;
	armPosition = SensorValue[armPot];
	int difference = 0;
	float kP= 0.5;

	while(true)
	{
		difference = (armPosition - SensorValue[armPot] )*kP;
		setArm(difference);

	}

}

task LCD()
{
	int lastPrintedArmPosition = 0;

	while(true)
	{
		if(lastPrintedArmPosition!= armPosition)
		{

			clearLCDLine(0);
			clearLCDLine(1);

			lastPrintedArmPosition = armPosition;
			displayLCDString(0,0,"Arm: ");
			displayLCDNumber(0,6,lastPrintedArmPosition);

			wait1Msec(1000);
		}
	}

}

task autoSelection()
{
	// Clears the LCD lines
	clearLCDLine(0);
	clearLCDLine(1);

	// Displays the currently selected autonomous
	displayLCDString(0,0,"Current Auto: ");
	displayLCDString(1,0,autoNames[autoNumber]);

	int lastButtonPressed = 0;
	int buttonPressed = 0;
	while(true)
	{
		buttonPressed = nLCDButtons;
		if(buttonPressed != lastButtonPressed)
		{
			switch(buttonPressed)
			{

				case 1: // Left
					if(autoNumber > 0)
						autoNumber--;
				break;

				case 4: // Right
					if(autoNumber < NUM_AUTOS-1)
						autoNumber++;
				break;

				default:

				break;
			}

			lastButtonPressed = buttonPressed;
			clearLCDLine(0);
			clearLCDLine(1);

			displayLCDString(0,0,"Current Auto: ");
			displayLCDString(1,0,autoNames[autoNumber]);

		}
	}
}

// Controls the left wheels
void setLeftDrive(int power)
{
	motor[backInnerRightDrive] = motor[backOuterRightDrive] = motor[frontRightDrive] = power;
}

// Controls the right wheels
void setRightDrive(int power)
{
	motor[backInnerLeftDrive] = motor[backOuterLeftDrive] = motor[frontLeftDrive] = power;
}

// Turns the robot precicely using the gyro sensor
void gyroTurn (int target){
	bool atTarget = false; // Initially the robot has not yet reached it's turn target

	int error = target; // Gyro sensors are prone to error, so this is used for corrections.
	int previousError = target; // Same deal as above
	int errorDifference = 0; // There is no error because it hasn't started turning yet
	float errorSum = 0; //Same as above
	int output;

	// Constants used for error calculation
	float kp = 0.2;
	float ki = 0.0001;

	// Sets the real target by adding the current gyro offset
	target += SensorValue[gyro];

	while (!atTarget) {
		error = target - SensorValue[gyro]; // Calculates error
		errorDifference = error - previousError; // Calculates the change in error from the last tick
		previousError = error; // Saves the error value to be used in the next cycle

		// If the error is less than 50, it is negligible so it sets error to 0
		if (abs(error) < 50)
			errorSum = errorSum + error;
		else
			errorSum = 0;

		// Calculates the new turn power based on the error
		output = error * kp + errorSum * ki;

		// Detects if the robot has finished the turn
		if ((abs(errorDifference) == 0) && abs(error) < 10) {
			atTarget = true;
		}

		// Sets the motors to keep turning
		setLeftDrive(-output);
		setRightDrive(+output);

		wait1Msec(10);
	}

	// Stops the robot once the turn is complete
	setLeftDrive(0);
	setRightDrive(0);
}

void setArm(int power) //Sets the power of the arm to a value. Ex: setArm(50) sets the arm to a power of 50
{
	motor[leftArm] = motor[rightArm] = motorCap(power);
}

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {
  	// Wheel controls
  	setLeftDrive(vexRT[Ch3]);
  	setRightDrive(vexRT[Ch2]);

  	// Moves the arm up while 5U is pressed
  	if(vexRT[Btn5U])
  	{
  		armTaskRunning = 0;
  		stopTask(arm);
  		setArm(127);
  	}
  	// Moves the arm down while 5D is pressed
  	else if(vexRT[Btn5D])
  	{
  		armTaskRunning = 0;
  		stopTask(arm);
  		setArm(-127);
  	}
  	// Stops the arm when neither buttons are being pressed.
  	else if(armTaskRunning == 0)
  	{
  		setArm(0);
  		wait1Msec(100);
  		startTask(arm);
  	}

  	// Manual override of armPosition in code. Used if the robot wasn't started properly and fixes errors during the match.
  	if(vexRT[Btn8D])
  	{
			armPosition = 1600;
  	}

  	if(vexRT[Btn8U])
  	{
			armPosition = 2500;
  	}

  }
}

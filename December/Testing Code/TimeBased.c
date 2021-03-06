#pragma config(Sensor, in1,    LeftSensor,     sensorPotentiometer)
#pragma config(Sensor, in2,    RightSensor,    sensorPotentiometer)
#pragma config(Sensor, dgtl1,  RightSensor2,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LeftSensor2,    sensorQuadEncoder)
#pragma config(Motor,  port1,            ,             tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           BackRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FrontRight,    tmotorVex269_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LiftRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LiftRightTwo,  tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           LiftLeftTwo,   tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           LiftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           FrontBackLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,           ,             tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void cogoco()
{
	while(SensorValue(RightSensor2) <  200)
	{
		motor[LiftLeftTwo] = 	-90;
		motor[LiftRightTwo] = 90;
	}
		motor[LiftLeftTwo] = 	0;
		motor[LiftRightTwo] = 0;
}

void cogomo()
{
	while(SensorValue(RightSensor2) > 10)
	{
		motor[LiftLeftTwo] = 90;
		motor[LiftRightTwo] = -90;
	}
		motor[LiftLeftTwo] = 0;
		motor[LiftRightTwo] = 0;

}

void clawopen(int time)
{
	motor[Claw] = 90;
}

void clawclose(int time)
{
	motor[Claw] = -90;
}

//Mobile Goal Go Down While Robot Moves Forward
void mogodownforward(int time)
{
	motor[BackRight] = 100;
	motor[FrontRight] = 100;
	motor[FrontBackLeft] = 100;
	motor[LiftLeft] = 100;
	motor[LiftRight] = 100;
	wait1Msec(time);
	motor[BackRight] = 0;
	motor[FrontRight] = 0;
	motor[FrontBackLeft] = 0;
	motor[LiftLeft] = 0;
	motor[LiftRight] = 0;
}

void mogoupbackward(int time)
{
	motor[BackRight] = -100;
	motor[FrontRight] = -100;
	motor[FrontBackLeft] = -100;
	motor[LiftLeft] = -100;
	motor[LiftRight] = -100;
	wait1Msec(time);
	motor[BackRight] = 0;
	motor[FrontRight] = 0;
	motor[FrontBackLeft] = 0;
	motor[LiftLeft] = 0;
	motor[LiftRight] = 0;
}

//conelift right turn
void cogodown(int time)
{
	motor[LiftLeftTwo] = 127;
	motor[LiftRightTwo]= -127;
	wait1Msec(time);
	motor[LiftLeftTwo] = 0;
	motor[LiftRightTwo]= 0;
}

//conelift left turn
void cogoup(int time)
{
	motor[LiftLeftTwo] = -127;
	motor[LiftRightTwo]= 127;
	wait1Msec(time);
	motor[LiftLeftTwo] = 0;
	motor[LiftRightTwo]= 0;
}

//mobilegoal down
void mogodown(int time)
{
	motor[LiftLeft] = motor[LiftRight] = -100;
	wait1Msec(time);
	motor[LiftLeft] = motor[LiftRight] = 0;
}

//mobilegoal up
void mogoup(int time)
{
	motor[LiftLeft] = motor[LiftRight] = 100
	wait1Msec(time);
	motor[LiftLeft] = motor[LiftRight] = 0;
}

//move forward
void driveforward(int time)
{
	motor[FrontBackLeft] = 100;
 	motor[FrontRight] = 100;
 	motor[BackRight] = 100;
 	wait1Msec(time);
 	motor[FrontRight] = 0;
 	motor[BackRight] = 0;
 	motor[FrontBackLeft] = 0;
}

//moveforward
void drivebackward(int time)
{
 	motor[FrontRight] = -100;
 	motor[FrontBackLeft] = -100;
 	motor[BackRight] = -100;
 	wait1Msec(time);
 	motor[FrontRight] = 0;
 	motor[BackRight] = 0;
 	motor[FrontBackLeft] = 0;
}

//right turn
void right(int time)
{
 	motor[FrontRight] = -100;
 	motor[FrontBackLeft] = 100;
 	motor[BackRight] = -100;
 	wait1Msec(time);
 	motor[FrontRight] = 0;
 	motor[BackRight] = 0;
 	motor[FrontBackLeft] = 0;
}


//left turn
void left(int time)
{
	motor[FrontRight] = 100;
 	motor[FrontBackLeft] = -100;
 	motor[BackRight] = 100;
 	wait1Msec(time);
 	motor[FrontRight] = 0;
 	motor[BackRight] = 0;
 	motor[FrontBackLeft] = 0;
}

void mobilegoalten()
{
		cogoup(1300);
  	mogodown(1400);
		driveforward(1600);
 		mogoup(650);
 		cogodown(2000);
 		wait1Msec(100);
 		clawopen(150);
 		cogoup(400);
 		clawclose(80);
 		cogoup(1200);
 		mogoup(900);
 		drivebackward(1800);
 		right(350);
 		driveforward(100);
 		right(800);
 		driveforward(400);
 		mogodown(1400);
		drivebackward(500);
 		mogoup(1400);
}

void stationarygoal()
{
	drivebackward(120);
	cogoup(1680);
	wait1Msec(500);
	clawopen(80);
	wait1Msec(500);
	cogodown(1400);
	driveforward(150);
	clawclose(80);
	motor[FrontRight] = -127;
 	motor[FrontBackLeft] = 127;
 	motor[BackRight] = -127;
 	wait1Msec(500);
 	motor[FrontBackLeft] = 127;
 	motor[FrontRight] = 127;
 	motor[BackRight] = 127;
 	wait1Msec(500);
 	motor[FrontBackLeft] = 0;
 	motor[FrontRight] = 0;
 	motor[BackRight] = 0;
 	clawclose(80);

}

task main()
{
	while(true)
	{
		if(vexRT[Btn5U] == 1)
	{
		cogoup(800);
  	mogodown(1700);
		driveforward(2000);
 		mogoup(1700);
 		drivebackward(2000);
 		left(450);
 		driveforward(150);
 		left(600);
 		driveforward(500);
 		mogodown(1400);
		drivebackward(700);
 		mogoup(1400);
	}
		else
	{
		motor[FrontRight] = 0;
		motor[BackRight] = 0;
		motor[LiftLeft] = 0;
		motor[LiftRight] = 0;
		motor[LiftLeftTwo] = 0;
		motor[LiftRightTwo] = 0;
		motor[FrontBackLeft] = 0;
	}
}
}


#ifndef _LIBGLOBALE_H
#define _LIBGLOBALE_H


#include "Vector2.h"
#include "SearchCell.h"
#include "Grid.h"
#include "RobotBase.h"
#include "PathFinding.h"

#include "LibGlobale.h"
#include <iostream>
#include <math.h>
#include <vector>

#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <wiringPi.h>

/********** Variables linked to the map **********/

#define WORLD_SIZE_X 1000
#define WORLD_SIZE_Y 1000
#define CELL_SIZE 10
#define CELL_DIAG_SIZE 14.1421

/********** Variable linked to the accuracy of the robot location **********/

#define ACCURACY 1

/********** Variable linked to the command of the robot **********/

#define CMD_MIN 0
#define CMD_MAX 255

/********** Variable linked to the wheel encoder **********/

#define LEFT_PWM 1
#define RIGHT_PWM 24

#define LEFT_IT 0
#define LEFT_A 2
#define LEFT_B 3

#define RIGHT_IT 21
#define RIGHT_A 22
#define RIGHT_B 23

#define WHEEL_CONST 20 // TO DO

volatile int eventLeftCounter;
volatile int eventRightCounter;

volatile int counterPosX;
volatile int counterPosY;
volatile int counterOrientation;

void timer_handler(int signum)
{
	int tmp1 = eventLeftCounter;
	int tmp2 = eventRightCounter;
	eventLeftCounter = 0;
	eventRightCounter = 0;

	counterPosX = ((tmp1 + tmp2) / 2) * WHEEL_CONST;
	counterPosY = ((tmp1 + tmp2) / 2) * WHEEL_CONST;
	counterOrientation = (tmp1 - tmp2);
}

void myLeftCounterIT(void) {

	bool encoderA = digitalRead(LEFT_A);
	bool encoderB = digitalRead(LEFT_B);

	if (encoderA && !encoderB)
		eventLeftCounter++;
	if (!encoderA && encoderB)
		eventLeftCounter--;
}

void myRightCounterIT(void) {

	bool encoderA = digitalRead(RIGHT_A);
	bool encoderB = digitalRead(RIGHT_B);

	if (encoderA && !encoderB)
		eventRightCounter++;
	if (!encoderA && encoderB)
		eventRightCounter--;
}

void initGPIO()
{
	// Set up Wiring Pi

  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return;
  }


	pinMode(LEFT_PWM, OUTPUT);
	pinMode(RIGHT_PWM, OUTPUT);
	digitalWrite(LEFT_PWM, LOW);
	digitalWrite(RIGHT_PWM, LOW);
	pinMode(LEFT_PWM, PWM_OUTPUT);
	pinMode(RIGHT_PWM, PWM_OUTPUT);

	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(2);
	pwmSetRange(2048);

	pinMode(LEFT_IT, INPUT);
	pinMode(LEFT_A, INPUT);
	pinMode(LEFT_B, INPUT);

	pinMode(RIGHT_IT, INPUT);
	pinMode(RIGHT_A, INPUT);
	pinMode(RIGHT_B, INPUT);


}

void initTimer()
{
	// Interrupt timer

	struct sigaction sa;
	struct itimerval timer;

	// Install timer_handler as the signal handler for SIGVTALRM.
	memset(&sa, 0, sizeof (sa));
	sa.sa_handler = &timer_handler;
	sigaction(SIGVTALRM, &sa, NULL);

	// Configure the timer to expire after 250 msec...
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 250000;
	// ... and every 250 msec after that.
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 250000;
	// Start a virtual timer. It counts down whenever this process is
	//executing.
	setitimer(ITIMER_VIRTUAL, &timer, NULL);

	// set Pin 17/0 generate an interrupt on high-to-low transitions
	// and attach myLeftCounterIT() to the interrupt

    if ( wiringPiISR (LEFT_IT, INT_EDGE_RISING, &myLeftCounterIT) < 0 ) {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
      return ;
    }

	// set Pin 5/21 generate an interrupt on high-to-low transitions
	// and attach myLeftCounterIT() to the interrupt
    if ( wiringPiISR (RIGHT_IT, INT_EDGE_RISING, &myRightCounterIT) < 0 ) {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
      return ;
    }
}



#endif //_LIBGLOBALE_H

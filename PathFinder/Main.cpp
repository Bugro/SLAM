
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
#include <stdio.h>
#include <string.h>
//#include <sys/time.h>
//#include <wiringPi.h>

void timer_handler(int signum);
void myRightCounterIT(void);
void myRightCounterIT(void);

int main(int argc, char* args[])
{
	// initGPIO();
	// initTimer();

	//Create Process

	std::cout << " ************** Robot Simulation ************** " << std::endl << std::endl << std::endl;

	Vector2 targetPos = Vector2(120, 230);
	RobotBase robot = RobotBase();

	std::cout << " Position de depart: " << robot.getPosition().GetX() << " " << robot.getPosition().GetY() << std::endl;
	std::cout << " Position de d'arrivee: " << targetPos.GetX() << " " << targetPos.GetY() << std::endl << std::endl;

	robot.PathFinder(robot.getPosition(), targetPos);

	getchar();
}
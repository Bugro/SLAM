
/**
*
* @file RobotBase.cpp
* @brief RobotBase class implementation
* @author J. CHAUDET
* @date 01 January 2016
*
* @section Copyright
*
* This document is confidential and the property of CentraleSupelec.
* It can't be distributed without the prior consent of its owner.
*
*/

#include "RobotBase.h"

#define PI 3.14159

using namespace std;

/**
* Robot implementation
*/

/* Constructor */

RobotBase::RobotBase(void)
{
	m_position.SetX(WORLD_SIZE_X / 2);
	m_position.SetY(WORLD_SIZE_Y / 2);
	m_destination.SetX(0);
	m_destination.SetY(0);
	m_orientation = 0;
}

RobotBase::RobotBase(Vector2 position, Vector2 destination, short orientation)
{
	m_position.SetX(position.GetX());
	m_position.SetY(position.GetY());
	m_destination.SetX(destination.GetX());
	m_destination.SetY(destination.GetY());
	m_orientation = orientation;
}

RobotBase::~RobotBase(void)
{}

/**
*	Getter and setter
*/
Vector2 RobotBase::getPosition() const{
	return m_position;
}

void RobotBase::setPosition(Vector2 newPosition){
	m_position = newPosition;
}

short RobotBase::getOrientation() const{
	return m_orientation;
}

void RobotBase::setOrientation(short newOrientation){
	m_orientation = newOrientation;
}


void RobotBase::PathFinder(Vector2 currentPos, Vector2 targetPos){

	PathFinding path = PathFinding();

	m_pathToGoalRobot = path.FindPath(targetPos, currentPos);

	std::cout << " ************** Path Find ************** " << std::endl << std::endl;

	path.PathDisplay();
}

/**
* Moves the robot in function of the orientation and the speed passed in parameter (manual mode)
*/
void RobotBase::move(short goalOrientation) {

	//PWM adaptation
	if (goalOrientation != 0)
	{
		while (!isOriented(goalOrientation))
		{
			if (goalOrientation <= 0)
			{
				//pwmWrite(LEFT_PWM, 700);
				//pwmWrite(RIGHT_PWM, 300);
			}
			else
			{
				//pwmWrite(LEFT_PWM, 300);
				//pwmWrite(RIGHT_PWM, 700);
			}
		}
	}
	while (!isArrived())
	{
		//Renvoi des commandes moteurs

		//pwmWrite(LEFT_PWM, 700);
		//pwmWrite(RIGHT_PWM 700);
	}
}

/**
* Moves the robot to the position passed in parameter (automatic mode)
*/
void RobotBase::moveTo(Vector2 destination) {

	PathFinding path = PathFinding();
	int i = 0;
	short goalOrientation;

	m_pathToGoalRobot = path.FindPath(destination, getPosition());

	while (i != (m_pathToGoalRobot.size()-1))
	{
		goalOrientation = computeOrientation(m_pathToGoalRobot[i]->GetVector(), m_pathToGoalRobot[i + 1]->GetVector());

		m_destination.SetX(m_pathToGoalRobot[i]->GetX());
		m_destination.SetY(m_pathToGoalRobot[i]->GetY());

		move(goalOrientation);
		i++;
	}
}

/**
* Stops robot's motors
*/
void RobotBase::stop() {

	//pwmWrite(LEFT_PWM 500);
	//pwmWrite(RIGHT_PWM, 500);
}

/**
* Stops in emergency the robot
*/
void RobotBase::emergencyStop() {

	//pwmWrite(LEFT_PWM, 500);
	//pwmWrite(RIGHT_PWM, 500);
}

/**
* Informs about robot state
*/
int RobotBase::getStatus() {
	return 0;
}

/**
* Gets current battery level
*/
int RobotBase::getBatteryLevel() {
	return 0;
}

/**
* Alerts that the battery is empty
*/
void RobotBase::informBatteryEmpty() {
	std::cout << "No Battery information" << std::endl;
}

/**
* Computes motors commands following user order and obstacles
*/
void RobotBase::computeMotorsCommands(short orientationError, short speed, short acceleration) {

	//debug_printf("computeMotorsCommands cmdMax \n");

	//PWM adaptation

	//Renvoi des commandes moteurs

	//pwmWrite(LEFT_PWM, speed);
	//pwmWrite(RIGHT_PWM, speed);
}

/**
* Calculates the angle between abscissa axis and vector {Position1,Position2} (in trigonometric)
*/
float RobotBase::computeOrientation(Vector2 Position1, Vector2 Position2) {
	if (Position1.GetX() != Position2.GetX() || Position1.GetY() != Position2.GetY())
	{
		float angle = 90 - ((float)rad2deg(atan2(Position2.GetX() - Position1.GetX(), Position2.GetY() - Position1.GetY())));

		if (angle > 180.0)
			angle -= 360.0;
		else if (angle < -180.0)
			angle += 360.0;
		return angle;
	}
	else
	{	//Les points sont confondus, orientation impossible � calculer
		return -1.0;
	}
}

/**
* Tests if the robot is arrived in position or not
*/
bool RobotBase::isArrived(void){
	if (m_position.GetX() >= (m_destination.GetX() - ACCURACY) &&
		m_position.GetX() <= (m_destination.GetX() + ACCURACY) &&
		m_position.GetY() >= (m_destination.GetY() - ACCURACY) &&
		m_position.GetY() <= (m_destination.GetY() + ACCURACY)){
		return true;
	}
	else
	{
		return false;
	}
}

bool RobotBase::isOriented(short goalOrientation){
	if (getOrientation() == goalOrientation){
		return true;
	}
	else
	{
		return false;
	}
}

float rad2deg(float rad){
	return (float)(180.0 * rad / PI);
}

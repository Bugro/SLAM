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
#include "PathFinding.h"
#include <iostream>
#include <math.h>

#define PI 3.14159

using namespace std;

/**
* Robot implementation
*/

/**
* Constructor
*/


RobotBase::RobotBase(void)
{
	m_position.SetX(0);
	m_position.SetY(0);
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
{
}


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
/*
void RobotBase::robotDisplay()
{
	SDL_Rect robot;
	robot.x = m_position.GetX() - 10;
	robot.y = m_position.GetY() - 10;
	robot.w = m_position.GetX() + 10;
	robot.h = m_position.GetY() + 10;


}
*/
/**
* Moves the robot in function of the orientation and the speed passed in parameter (manual mode)
*/
void RobotBase::move(short orientation, short speed, short acceleration) {

	debug_printf("move \n");

	computeMotorsCommands(orientation, speed, acceleration);
}

/**
* Moves the robot to the position passed in parameter (automatic mode)
*/
void RobotBase::moveTo(Vector2 destination) {
	std::cout << "TODO" << std::endl;

}

/**
* Stops robot's motors
*/
void RobotBase::stop() {

	//pwmWrite(1, 500);
	//pwmWrite(2, 500);
}

/**
* Stops in emergency the robot
*/
void RobotBase::emergencyStop() {

	//pwmWrite(1, 500);
	//pwmWrite(2, 500);
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

	debug_printf("computeMotorsCommands cmdMax \n");

	//PWM adaptation

	//Renvoi des commandes moteurs

	//pwmWrite(1, speed);
	//pwmWrite(2, speed);
}

/**
* Calculates the angle between abscissa axis and vector {Position1,Position2} (in trigonometric)
*/
float RobotBase::computeOrientation(Vector2 Position1, Vector2 Position2) {
	if (Position1.GetX() != Position2.GetX() || Position1.GetY() != Position2.GetY())
	{
		float angle = (float)rad2deg(atan2(Position2.GetX() - Position1.GetY(), Position2.GetX() - Position1.GetY()));
		if (angle > 180.0)
			angle -= 360.0;
		else if (angle < -180.0)
			angle += 360.0;
		return angle;
	}
	else
	{	//Les points sont confondus, orientation impossible à calculer
		return -1;
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


float rad2deg(float rad){
	return (float)(180.0 * rad / PI);
}
/**
* Project SLAM_Project
*/


#ifndef _ROBOTBASE_H
#define _ROBOTBASE_H

#include "Declaration.h"
#include "PathFinding.h"
#include "Vector2.h"
#include "SearchCell.h"

#include <vector>

#define ACCURACY 1

#define CMD_MIN 0
#define CMD_MAX 255


// The robot state machien class
class RobotBase{
public:

	/**
	* Constructor
	*/
	RobotBase(void);
	RobotBase(Vector2 position, Vector2 destination, short orientation);
	~RobotBase(void);

	/**
	* Getter and setter
	*/
	Vector2 getPosition() const;
	void setPosition(Vector2 newPosition);
	short getOrientation() const;
	void setOrientation(short newOrientation);

	//void RobotBase::robotDisplay();

	/**
	*
	* @fn void move(short orientation, short speed, short acceleration)
	* @brief Moves the robot in function of the orientation and the speed passed in parameter (manual mode)
	*
	* @param orientationSetPoint: Robot guidance set
	* @param speed: Robot speed setpoint
	* @param acceleration: Robot acceleration
	* @pre Robot initialized
	* @post
	*
	*/
	void move(short orientation);

	/**
	*
	* @fn void moveTo(Point destination)
	* @brief Moves the robot to the position passed in parameter (automatic mode)
	*
	* @param destination: Point to be reached
	* @pre Robot initialized
	* @post
	*
	*/
	
	void moveTo(Vector2 destination);
	
	/**
	*
	* @fn void stop()
	* @brief Stops robot's motors
	*
	* @pre Robot initialized
	* @post Motors stopped
	*/
	void stop();

	/**
	*
	* @fn void emergencyStop()
	* @brief Stops in emergency the robot
	*
	* @pre Robot initialized
	* @post Robot stopped and comes back in initial state
	*
	*/
	void emergencyStop();

	/**
	*
	* @fn int getStatus()
	* @brief Informs about robot state
	*
	* @pre
	* @post Robot state recovered
	* @return The robot state.
	*
	*/
	int getStatus();

	/**
	*
	* @fn int getBatteryLevel()
	* @brief Gets current battery level
	*
	* @pre
	* @post Battery level obtained
	* @return The battery level(en %)
	*
	*/
	int getBatteryLevel();

	/**
	*
	* @fn void informBatteryEmpty()
	* @brief Alerts that the battery is empty
	*
	* @pre
	* @post Alert triggered
	*
	*/
	void informBatteryEmpty();

	/**
	*
	* @fn bool isArrived()
	* @brief Tests if the robot is arrived in position or not
	*
	* @pre Robot position uptdated
	* @post
	* @return True if the robot is arrived, else False
	*/
	bool isArrived();

	bool isOriented(short goalOrientation);

	void PathFinder(Vector2 currentPos, Vector2 targetPos);

	std::vector <Vector2*> m_pathToGoalRobot;

private:
	/**
	*	The robot position
	*/
	Vector2 m_position;

	/**
	* The robot destination
	*/
	Vector2 m_destination;

	/**
	* The robot orientation (between -180 and +180)
	*/
	short m_orientation;
	
	/**
	*
	* @fn void computeMotorsCommands(short orientationError, short speed)
	* @brief Transmits motors commands following user order.
	*
	* @param orientationError Robot set gap.
	* @param speed Robot speed setpoint.
	* @pre
	* @post Commands of the different motors has been sent
	*
	*/
	void computeMotorsCommands(short orientationError, short speed, short acceleration);

	/**
	*
	* @fn void computeOrientation(Point Position1, Point Position2)
	* @brief Calculates the angle between abscissa axis and vector {Position1,Position2} (in trigonometric)
	*
	* @param Position1: The origin Point.
	* @param Position2: The destination Point.
	* @pre
	* @post Angle has been calculated
	* @return -1 When Position1 and Position2 are mingled, else an orientation in degrees between -180 and +180.
	*
	*/
	float computeOrientation(Vector2 Position1, Vector2 Position2);
};

float rad2deg(float rad);

#endif //_ROBOTBASE_H
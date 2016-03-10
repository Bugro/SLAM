
/**
*
* @file Vector2.cpp
* @brief Vector2 class implementation
* @author J. CHAUDET
* @date 01 January 2016
*
* @section Copyright
*
* This document is confidential and the property of CentraleSupelec.
* It can't be distributed without the prior consent of its owner.
*
*/

#include "Vector2.h"

/* Constructor */

Vector2::Vector2() : m_x(0), m_y(0) {}

Vector2::Vector2(float x, float y) : m_x(x), m_y(y) {}

Vector2 Vector2::GetVector()
{
	Vector2 temp = Vector2(m_x, m_y);
	return temp;
}

float Vector2::GetX() const
{ 
	return m_x; 
}

float Vector2::GetY() const
{ 
	return m_y; 
}

void Vector2::SetX(float x)
{ 
	m_x = x; 
}
void Vector2::SetY(float y)
{ 
	m_y = y; 
}

float Vector2::Length()
{ 
	return (sqrt(m_x*m_x + m_y*m_y));
}


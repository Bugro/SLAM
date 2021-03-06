
#include <math.h>
#include "Vector2.h"

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


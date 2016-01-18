
#include <math.h>
#include "Vector2.h"

Vector2::Vector2() : m_x(0), m_y(0) {}
Vector2::Vector2(int x, int y) : m_x(x), m_y(y) {}

int Vector2::GetX() const
{ 
	return m_x; 
}

int Vector2::GetY() const
{ 
	return m_y; 
}

void Vector2::SetX(int x)
{ 
	m_x = x; 
}
void Vector2::SetY(int y)
{ 
	m_y = y; 
}

int Vector2::Length()
{ 
	return (int)(sqrt((float)(m_x*m_x + m_y*m_y))); 
}



#ifndef _VECTOR2_H
#define _VECTOR2_H

#include "LibGlobale.h"
#include <math.h>

class Vector2{

public:
	Vector2();
	Vector2(float x, float y);
	
	float GetX()const;
	float GetY()const;
	void SetX(float x);
	void SetY(float y);

	Vector2 GetVector();
	float Length();

private:
	float m_x;
	float m_y;

};

#endif //_VECTOR2_H
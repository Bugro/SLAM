#ifndef _VECTOR2_H
#define _VECTOR2_H

#include <math.h>

class Vector2{

public:
	Vector2();
	Vector2(int x, int y);
	
	int GetX()const;
	int GetY()const;
	void SetX(int x);
	void SetY(int y);

	Vector2 GetVector();
	int Length();

private:
	int m_x;
	int m_y;

};

#endif //_VECTOR2_H
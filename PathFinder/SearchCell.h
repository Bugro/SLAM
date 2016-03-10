
#ifndef _SEARCHCELL_H
#define _SEARCHCELL_H

#include "LibGlobale.h"
#include <math.h>

class SearchCell{

public:

	SearchCell();
	SearchCell(float x, float y, SearchCell *_parent = 0);
	~SearchCell();

	float GetXcoord()const;
	float GetYcoord()const;
	void SetXcoord(float);
	void SetYcoord(float);
	int GetId()const; 
	void SetId(int);
	bool GetWalkable();
	void SetWalkable(bool);
	float GetF();

	float ManhattanDistance(SearchCell *);

	SearchCell *parent;
	float G;
	float H;

private:

	float m_xcoord, m_ycoord;
	int m_id;
	bool m_walkable;
};

#endif //_SEARCHCELL_H
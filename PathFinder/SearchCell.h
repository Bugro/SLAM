#ifndef _SEARCHCELL_H
#define _SEARCHCELL_H

#include <math.h>

#define WORLD_SIZE_X 1000
#define WORLD_SIZE_Y 1000
#define CELL_SIZE 10
#define CELL_DIAG_SIZE 14.1421

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
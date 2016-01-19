#ifndef _SEARCHCELL_H
#define _SEARCHCELL_H

#include <math.h>

#define WORLD_SIZE 60
#define CELL_SIZE 10
#define CELL_DIAG_SIZE 14.1421

class SearchCell{

public:

	SearchCell();
	SearchCell(int x, int y, SearchCell *_parent = 0);
	~SearchCell();

	int GetXcoord()const;
	int GetYcoord()const;
	void SetXcoord(int);
	void SetYcoord(int);
	int GetId()const; 
	void SetId(int);
	bool GetWalkable(int id)const;
	void SetWalkable(bool);
	float GetF();

	float ManhattanDistance(SearchCell *);

	SearchCell *parent;
	float G;
	float H;

private:

	int m_xcoord, m_ycoord;
	int m_id;
	bool m_walkable;
};

#endif //_SEARCHCELL_H
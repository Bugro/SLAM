
#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include "Vector2.h"
#include "SearchCell.h"
#include "Grid.h"

#include "LibGlobale.h"
#include <iostream>
#include <vector>
#include <math.h>

class PathFinding
{

public:
	PathFinding(void);
	~PathFinding(void);

	std::vector <Vector2*> FindPath(Vector2 currentPos, Vector2 targetPos);
	Vector2 NextPathPos();

	void ClearOpenList();
	void ClearVisitedList();
	void ClearPathToGoal();
	void PathDisplay();
	void SetStartGoal(SearchCell start, SearchCell goal);
	void PathOpened(float x, float y, float newCost, SearchCell *parent);

	bool m_initializedStartGoal;
	bool m_foundGoal;
	Grid map = Grid();

private:

	SearchCell *GetNextCell();
	void ContinuePath();

	SearchCell *m_startCell;
	SearchCell *m_goalCell;

	std::vector <SearchCell*> m_openList;
	std::vector <SearchCell*> m_visitedList;
	std::vector <Vector2*> m_pathToGoal;
	std::vector <SearchCell*> m_pathToGoalGrid;
	std::vector <Vector2> m_pathToGoalGridVect;
	Grid grid;

};

#endif //_PATHFINDING_H

#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include <vector>
#include <math.h>
#include "Vector2.h"
#include "SearchCell.h"

class PathFinding
{

public:
	PathFinding(void);
	~PathFinding(void);

	void FindPath(Vector2 currentPos, Vector2 targetPos);
	Vector2 NextPathPos();

	void ClearOpenList();
	void ClearVisitedList();
	void ClearPathToGoal();
	void PathDisplay();
	void SetStartGoal(SearchCell start, SearchCell goal);
	void PathOpened(int x, int y, float newCost, SearchCell *parent);

	bool m_initializedStartGoal;
	bool m_foundGoal;

private:

	SearchCell *GetNextCell();
	void ContinuePath();

	SearchCell *m_startCell;
	SearchCell *m_goalCell;
	std::vector <SearchCell*> m_openList;
	std::vector <SearchCell*> m_visitedList;
	std::vector <Vector2*> m_pathToGoal;

};

#endif //_PATHFINDING_H
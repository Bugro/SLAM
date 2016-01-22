
#include <iostream>
#include "PathFinding.h"
#include "RobotBase.h"


PathFinding::PathFinding(void)
{
	m_initializedStartGoal = false;
	m_foundGoal = false;
}

PathFinding::~PathFinding(void)
{

}

void PathFinding::SetStartGoal(SearchCell start, SearchCell goal)
{
	m_startCell = new SearchCell(start.GetXcoord(), start.GetYcoord(), NULL);
	m_goalCell = new SearchCell(goal.GetXcoord(), goal.GetYcoord(), &goal);

	m_startCell->G = 0;
	m_startCell->H = m_startCell->ManhattanDistance(m_goalCell);
	m_startCell->parent = 0;

	m_openList.push_back(m_startCell);
}

std::vector <Vector2*> PathFinding::FindPath(Vector2 currentPos, Vector2 targetPos)
{
	if (!m_initializedStartGoal)
	{
		for (unsigned int i = 0; i < m_openList.size(); i++)
		{
			delete m_openList[i];
		}
		m_openList.clear();

		for (unsigned int i = 0; i < m_visitedList.size(); i++)
		{
			delete m_visitedList[i];
		}
		m_visitedList.clear();

		for (unsigned int i = 0; i < m_pathToGoal.size(); i++)
		{
			delete m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		//Initialize start

		SearchCell start;
		start.SetXcoord(currentPos.GetX());
		start.SetYcoord(currentPos.GetY());

		//Initialize goal

		SearchCell goal;
		goal.SetXcoord(targetPos.GetX());
		goal.SetYcoord(targetPos.GetY());

		SetStartGoal(start, goal);
		m_initializedStartGoal = true;
	}

	if (m_initializedStartGoal)
	{
		ContinuePath();
	}

	return m_pathToGoal;
}

SearchCell* PathFinding::GetNextCell()
{
	float bestF = 999999.0f;
	int cellIndex = -1;
	SearchCell* nextCell = NULL;

	for (unsigned int i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->GetF() < bestF)
		{
			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	if (cellIndex >= 0)
	{
		nextCell = m_openList[cellIndex];
		m_visitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}

	return nextCell;
}

void PathFinding::PathOpened(float x, float y, float newCost, SearchCell *parent)
{
	int id = (int)(y * (WORLD_SIZE_X/CELL_DIAG_SIZE) + x);
	/*
	Vector2 temp = Vector2(x, y);
	if(map.CellFromGrid(temp)->GetWalkable())
	{
		return;
	}
	*/
	for (unsigned int i = 0; i < m_visitedList.size(); i++)
	{
		if (id == m_visitedList[i]->GetId())
		{
			return ;
		}
	}

	SearchCell* newChild = new SearchCell(x, y, parent);
	newChild->G = newCost;
	newChild->H = parent->ManhattanDistance(m_goalCell);

	for (unsigned int i = 0; i < m_openList.size(); i++)
	{
		if (id == m_openList[i]->GetId())
		{
			float newF = newChild->G + newCost + m_openList[i]->H;

			if (m_openList[i]->GetF() > newF)
			{
				m_openList[i]->G = newChild->G + newCost;
				m_openList[i]->parent = newChild;
			}
			else
			{
				delete newChild;
				return ;
			}
		}
	}
	
	m_openList.push_back(newChild);
}

void PathFinding::ContinuePath()
{
	while (!m_foundGoal)
	{
		if (m_openList.empty())
		{
			return;
		}

		SearchCell* currentCell = GetNextCell();

		if (currentCell->GetId() == m_goalCell->GetId())
		{
			m_goalCell->parent = currentCell->parent;

			SearchCell* getPath;

			for (getPath = m_goalCell; getPath != NULL; getPath = getPath->parent)
			{
				m_pathToGoal.push_back(new Vector2((getPath->GetXcoord()), (getPath->GetYcoord())));
				m_pathToGoalGrid.push_back(map.CellFromGrid(Vector2((getPath->GetXcoord()), (getPath->GetYcoord()))));
			}
			m_foundGoal = true;
		}
		else
		{
			//Right Cell
			PathOpened(currentCell->GetXcoord() + CELL_SIZE, currentCell->GetYcoord(), currentCell->G + CELL_SIZE, currentCell);
			//Left Cell
			PathOpened(currentCell->GetXcoord() - CELL_SIZE, currentCell->GetYcoord(), currentCell->G + CELL_SIZE, currentCell);
			//Up Cell
			PathOpened(currentCell->GetXcoord(), currentCell->GetYcoord() + CELL_SIZE, currentCell->G + CELL_SIZE, currentCell);
			//Down Cell
			PathOpened(currentCell->GetXcoord(), currentCell->GetYcoord() - CELL_SIZE, currentCell->G + CELL_SIZE, currentCell);
			//Left-up Diagonal Cell
			PathOpened(currentCell->GetXcoord() - CELL_SIZE, currentCell->GetYcoord() + CELL_SIZE, currentCell->G + CELL_DIAG_SIZE, currentCell);
			//Right-up Cell
			PathOpened(currentCell->GetXcoord() + CELL_SIZE, currentCell->GetYcoord() + CELL_SIZE, currentCell->G + CELL_DIAG_SIZE, currentCell);
			//Left-down Diagonal Cell
			PathOpened(currentCell->GetXcoord() - CELL_SIZE, currentCell->GetYcoord() - CELL_SIZE, currentCell->G + CELL_DIAG_SIZE, currentCell);
			//Right-down Diagonal Cell
			PathOpened(currentCell->GetXcoord() + CELL_SIZE, currentCell->GetYcoord() - CELL_SIZE, currentCell->G + CELL_DIAG_SIZE, currentCell);

			for (unsigned int j = 0; j < m_openList.size(); j++)
			{
				if (currentCell->GetId() == m_openList[j]->GetId())
				{
					m_openList.erase(m_openList.begin() + j);
				}
			}
		}
	}
}

/*
Vector2 PathFinding::NextPathPos()
{
	int index = 1;

	Vector2 nextPos;
	nextPos.m_x = m_pathToGoal[m_pathToGoal.size() - index]->m_x + (CELL_SIZE / 2);
	nextPos.m_y = m_pathToGoal[m_pathToGoal.size() - index]->m_y + (CELL_SIZE / 2);

	Vector2 distance = nextPos - pos;

	if (index < m_pathToGoal.size())
	{
		if (distance.Length() < radius)
		{
			m_pathToGoal.erase(m_pathToGoal.end() - index);
		}
	}
	return nextPos;
}
*/

void PathFinding::ClearOpenList() { m_openList.clear(); }
void PathFinding::ClearVisitedList() { m_visitedList.clear(); }
void PathFinding::ClearPathToGoal() { m_pathToGoal.clear(); }

void PathFinding::PathDisplay()
{
	if (m_pathToGoal.empty())
	{
		std::cout << "Path Not Find" << std::endl;
	}
	else
	{
		std::cout << "Path Find" << std::endl << std::endl;

		for (unsigned int i = 0; i < m_pathToGoal.size(); i++)
		{
			std::cout << " " << m_pathToGoal[i]->GetX() << " " << m_pathToGoal[i]->GetY() << std::endl;
		}

		std::cout << std::endl << std::endl;

		for (unsigned int i = 0; i < m_pathToGoalGrid.size(); i++)
		{
			std::cout << " " << m_pathToGoalGrid[i]->GetXcoord() << " " << m_pathToGoalGrid[i]->GetYcoord() << std::endl;
		}
		map.DisplayGrid();
	}
}

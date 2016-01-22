#ifndef _GRID_H
#define _GRID_H

#include "SearchCell.h"
#include "Vector2.h"
#include "SDL.h"
#include <vector>

class Grid
{
	Vector2 gridWorldSize;
	float nodeRadius;
	float nodeDiameter;
	int iGridX, iGridY;

	std::vector<std::vector<SearchCell*> > grid;

public:
	Grid();
	~Grid();

	int gridSizeX, gridSizeY;

	void SetWorldSize(int, int);
	SearchCell* CellFromGrid(Vector2 point);
	void DisplayGrid(SDL_Renderer* renderer);
	void EraseCell(Vector2 point);
	Vector2 PosGrid(Vector2 point);

private:

};
#endif //_SEARCHCELL_H

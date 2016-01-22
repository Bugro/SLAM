#include "Grid.h"
#include <iostream>

Grid::Grid()
{
	gridWorldSize.SetX(WORLD_SIZE_X);
	gridWorldSize.SetY(WORLD_SIZE_Y);
	nodeRadius = CELL_SIZE/2;

	nodeDiameter = nodeRadius * 2;
	gridSizeX = (int)(gridWorldSize.GetX() / nodeDiameter);
	gridSizeY = (int)(gridWorldSize.GetY() / nodeDiameter);

	// Set up sizes. (HEIGHT x WIDTH)
	grid.resize(gridWorldSize.GetX());
	for (int i = 0; i < gridSizeX; ++i){
		grid[i].resize(gridSizeY);
	}

	for (int i = 0; i < gridSizeX; ++i){
		for (int j = 0; j < gridSizeY; ++j){
			grid[i][j] = new SearchCell();
			grid[i][j]->SetWalkable(true);
			grid[i][j]->SetXcoord(i*nodeDiameter + nodeRadius);
			grid[i][j]->SetYcoord(j*nodeDiameter + nodeRadius);
			grid[i][j]->SetId(j * WORLD_SIZE_X/CELL_SIZE + i);
		}
	}

	for (int i = 0; i < gridSizeX; ++i){
		grid[i][0]->SetWalkable(false);
		grid[i][gridSizeY - 1]->SetWalkable(false);
	}
	for (int i = 0; i < gridSizeY; ++i){
		grid[0][i]->SetWalkable(false);
		grid[gridSizeX - 1][i]->SetWalkable(false);
	}
}

Grid::~Grid()
{
}

SearchCell* Grid::CellFromGrid(Vector2 point)
{
	int x = (int)((point.GetX() / CELL_SIZE));
	std::cout << point.GetX() << std::endl;
	std::cout << x << std::endl;

	int y = (int)((point.GetY() / CELL_SIZE));

	return grid[x][y];
}

Vector2 Grid::PosGrid(Vector2 point)
{
	int x = (int)((point.GetX() / CELL_SIZE));
	std::cout << point.GetX() << std::endl;
	std::cout << x << std::endl;

	int y = (int)((point.GetY() / CELL_SIZE));

    Vector2 v2 = Vector2(x,y);
	return v2;
}

void Grid::EraseCell(Vector2 point)
{

}

void Grid::DisplayGrid()
{
	for (int i = 0; i < gridSizeX; i++){
		for (int j = 0; j < gridSizeY; j++){
			if (grid[i][j]->GetWalkable())
				std::cout << "1";
			else
				std::cout << "0";
		}
		std::cout << std::endl;
	}
}

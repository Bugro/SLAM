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

	for (int i = 2; i < gridSizeX-2; ++i){
		grid[i][70]->SetWalkable(false);

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

	return Vector2(x, y);
}

void Grid::EraseCell(Vector2 point)
{

}

void Grid::DisplayGrid(SDL_Renderer* renderer)
{
	SDL_Rect Display;

	for (int i = 0; i < gridSizeX; i++){
		for (int j = 0; j < gridSizeY; j++){
			if (grid[i][j]->GetWalkable())
			{
				Display.x = grid[i][j]->GetXcoord() - 5;
				Display.y = grid[i][j]->GetYcoord() - 5;
				Display.w = CELL_SIZE;
				Display.h = CELL_SIZE;

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &Display);
			}
			else
			{
				Display.x = grid[i][j]->GetXcoord() - 5;
				Display.y = grid[i][j]->GetYcoord() - 5;
				Display.w = CELL_SIZE;
				Display.h = CELL_SIZE;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &Display);
			}
		}
		std::cout << std::endl;
	}
}


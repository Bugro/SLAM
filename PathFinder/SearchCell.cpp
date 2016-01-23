
/**
*
* @file SearchCell.cpp
* @brief SearchCell class implementation
* @author J. CHAUDET
* @date 01 January 2016
*
* @section Copyright
*
* This document is confidential and the property of CentraleSupelec.
* It can't be distributed without the prior consent of its owner.
*
*/

#include "SearchCell.h"

/* Constructor */

SearchCell::SearchCell() : parent(0){}
SearchCell::SearchCell(float x, float y, SearchCell *_parent)
{
	m_xcoord = x;
	m_ycoord = y;
	parent = _parent;
	m_id = (int)(y * (WORLD_SIZE_X/CELL_SIZE) + x);
	G = 0; 
	H = 0;
	m_walkable = true;
}
SearchCell::~SearchCell()
{
}

float SearchCell::GetXcoord()const { return m_xcoord; }
float SearchCell::GetYcoord()const { return m_ycoord; }
void SearchCell::SetXcoord(float x) { m_xcoord = x; }
void SearchCell::SetYcoord(float y) { m_ycoord = y; }
int SearchCell::GetId()const { return m_id; }
void SearchCell::SetId(int id) { m_id = id; }
bool SearchCell::GetWalkable() {return m_walkable; }
void SearchCell::SetWalkable(bool walkable) { m_walkable = walkable; }

float SearchCell::GetF(){ return G + H; }


float SearchCell::ManhattanDistance(SearchCell *nodeEnd)
{
	float x = (fabs((float)(this->m_xcoord - nodeEnd->m_xcoord)));
	float y = (fabs((float)(this->m_ycoord - nodeEnd->m_ycoord)));

	return (x + y);
}
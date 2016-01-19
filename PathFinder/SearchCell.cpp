
#include "SearchCell.h"

SearchCell::SearchCell() : parent(0){}
SearchCell::SearchCell(int x, int y, SearchCell *_parent)
{
	m_xcoord = x;
	m_ycoord = y;
	parent = _parent;
	m_id = (y * WORLD_SIZE + x);
	G = 0; 
	H = 0;
	m_walkable = true;
}
SearchCell::~SearchCell()
{
}

int SearchCell::GetXcoord()const { return m_xcoord; }
int SearchCell::GetYcoord()const { return m_ycoord; }
void SearchCell::SetXcoord(int x) { m_xcoord = x; }
void SearchCell::SetYcoord(int y) { m_ycoord = y; }
int SearchCell::GetId()const { return m_id; }
void SearchCell::SetId(int id) { m_id = id; }
bool SearchCell::GetWalkable(int id)const { 

	while (id != m_id){

		id++;
	}
	return m_walkable; 
}
void SearchCell::SetWalkable(bool walkable) { m_walkable = walkable; }

float SearchCell::GetF(){ return G + H; }


float SearchCell::ManhattanDistance(SearchCell *nodeEnd)
{
	float x = (fabs((float)(this->m_xcoord - nodeEnd->m_xcoord)));
	float y = (fabs((float)(this->m_ycoord - nodeEnd->m_ycoord)));

	return (x + y);
}
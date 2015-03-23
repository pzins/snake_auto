#include "coordinate.h"



Coordinate::Coordinate(int x, int y) : x_(x), y_(y)
{

}

Coordinate::~Coordinate()
{
	
}

bool Coordinate::operator==(const Coordinate& ths) const
{
	
	return (ths.x_ == x_ && ths.y_ == y_);
}
#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>

class Coordinate
{
	private:
		int x_;
		int y_;

	public:
		Coordinate(int x, int y);
		~Coordinate();

		int getX(){return x_;}
		int getY(){return y_;}

		void setX(int x){x_ = x;}
		void setY(int y){y_ = y;}

	    bool operator==(const Coordinate& ths) const;

};

#endif


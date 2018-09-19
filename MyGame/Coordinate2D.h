#pragma once
#include "./ThirdPartyLibs/daancode_a-star/source/AStar.hpp"

#define DEFAULT_POINT_COORDINATE 0

class Coordinate2D
{
private:
	
	int mX;
	int mY;

public:

	Coordinate2D();
	Coordinate2D(int _x, int _y);
	~Coordinate2D();

	int getX();	
	int getY();
	void setX(int _x);
	void setY(int _y);

	bool operator== (const Coordinate2D & coordinates_);
	bool operator!= (const Coordinate2D & coordinates_);
	Coordinate2D operator-(const Coordinate2D& _coord);

	friend const bool operator == (const Coordinate2D& coord1, const Coordinate2D& coord2);
	friend const Coordinate2D operator-(const Coordinate2D& _coord);
};

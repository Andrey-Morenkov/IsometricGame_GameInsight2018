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

	//Vec2i makeVec();

	friend const bool operator == (const Coordinate2D& coord1, const Coordinate2D& coord2);
};

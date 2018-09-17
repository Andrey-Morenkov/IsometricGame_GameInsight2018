#pragma once

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
};

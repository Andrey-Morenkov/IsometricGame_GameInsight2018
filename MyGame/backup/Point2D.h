#pragma once

#define DEFAULT_POINT_COORDINATE 0

class Point2D
{
private:
	
	int mX;
	int mY;

public:

	Point2D();
	Point2D(int _x, int _y);
	~Point2D();

	int getX();	
	int getY();
	void setX(int _x);
	void setY(int _y);
};

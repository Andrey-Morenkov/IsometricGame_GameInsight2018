#include "Coordinate2D.h"

Coordinate2D::Coordinate2D()
{
	mX = DEFAULT_POINT_COORDINATE;
	mY = DEFAULT_POINT_COORDINATE;
}

Coordinate2D::Coordinate2D(int _x, int _y)
{
	mX = _x;
	mY = _y;
}

Coordinate2D::~Coordinate2D()
{
}

int Coordinate2D::getX()
{
	return mX;
}

int Coordinate2D::getY()
{
	return mY;
}

void Coordinate2D::setX(int _x)
{
	mX = _x;
}

void Coordinate2D::setY(int _y)
{
	mY = _y;
}

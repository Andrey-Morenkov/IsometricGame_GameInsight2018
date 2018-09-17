#include "Point2D.h"

Point2D::Point2D()
{
	mX = DEFAULT_POINT_COORDINATE;
	mY = DEFAULT_POINT_COORDINATE;
}

Point2D::Point2D(int _x, int _y)
{
	mX = _x;
	mY = _y;
}

Point2D::~Point2D()
{
}

int Point2D::getX()
{
	return mX;
}

int Point2D::getY()
{
	return mY;
}

void Point2D::setX(int _x)
{
	mX = _x;
}

void Point2D::setY(int _y)
{
	mY = _y;
}

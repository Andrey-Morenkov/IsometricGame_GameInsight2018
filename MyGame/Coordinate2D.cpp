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

bool Coordinate2D::operator==(const Coordinate2D & coordinates_)
{
	return ((mX == coordinates_.mX)&&(mY == coordinates_.mY));
}

bool Coordinate2D::operator!=(const Coordinate2D & coordinates_)
{
	return !((mX == coordinates_.mX) && (mY == coordinates_.mY));
}

Coordinate2D Coordinate2D::operator-(const Coordinate2D & _coord)
{
	return Coordinate2D(mX - _coord.mX, mY - _coord.mY);
}

const bool operator==(const Coordinate2D & coord1, const Coordinate2D & coord2)
{
	return((coord1.mX == coord2.mX) && (coord1.mY == coord2.mY));
}

const Coordinate2D operator-(const Coordinate2D & _coord)
{
	Coordinate2D res;
	res.mX -= _coord.mX;
	res.mY -= _coord.mY;
	return res;
}

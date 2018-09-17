#include <string>

#include "IsometricEngine.h"
#include "SupportMacroses.h"
#include "ResultCode.h"
#include "SDL_log.h"
#include "SDL.h"

void IsometricEngine::convert2DtoIsometric(Coordinate2D& _point)
{
	//LOG_INFO("Incoming 2D point params: x = %d, y = %d", _point->getX(), _point->getY());
	int tmpX = _point.getX() - _point.getY();
	int tmpY = (_point.getX() + _point.getY())*0.5;
	_point.setX(tmpX);
	_point.setY(tmpY);

		//LOG_INFO("New isometric point params: x = %d, y = %d", _point->getX(), _point->getY());
}

void IsometricEngine::convertIsometricTo2D(Coordinate2D& _point)
{
	int tmpX = (2 * _point.getY() + _point.getX())*0.5;
	int tmpY = (2 * _point.getY() - _point.getX())*0.5;
	_point.setX(tmpX);
	_point.setY(tmpY);
}

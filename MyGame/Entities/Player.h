#pragma once
#include "../Entity.h"
#include "../Texture.h"

enum class PlayerDirection
{
	UP_LEFT = 0,
	UP,
	UP_RIGHT,
	RIGHT,
	RIGHT_DOWN,
	DOWN,
	DOWN_LEFT,
	LEFT
};

class Player : public Entity
{
private:

	Texture mPlayerTexture;
	PlayerDirection mDirection;
	int mSpeed; //pixels per tick

public:
	Player();
	Player(Coordinate2D _startCoord);
	virtual ~Player();

	void render() override;

	void setDirection(PlayerDirection _direction);
	void setPostition(Coordinate2D _newPos);
	void setPositionFromTileIsoCoords(Coordinate2D _targetTileLeftTopCornerCoords);
	void setSpeed(int _speed);
	Coordinate2D getPosition();
	Coordinate2D getDownCenterPosition(); //use this for movement
	PlayerDirection getDirection();
	int getSpeed();
};




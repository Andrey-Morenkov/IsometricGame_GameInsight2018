#pragma once
#include "../Entity.h"
#include "../Texture.h"
#include "../World.h"

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
	bool mIsMoving;

public:
	Player();
	Player(Coordinate2D _startCoord);
	virtual ~Player();

	void render() override;

	void setDirection(PlayerDirection _direction);
	void setPostition(Coordinate2D _newPos);
	void setSpeed(int _speed);
	void setIsMoving(bool _ismoving);
	Coordinate2D getPosition();
	PlayerDirection getDirection();
	int getSpeed();
	bool getIsMoving();
};




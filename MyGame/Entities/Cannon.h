#pragma once
#include "../Entity.h"
#include "World.h"
#include "../Interfaces/Runnable.h"
#include "Fireball.h"

class Cannon : public Entity, public Runnable
{
private:

	WallType mType;
	void loadTexture() override;

public:

	Cannon();
	Cannon(Coordinate2D _startCoord);
	virtual ~Cannon();

	void setType(WallType _type);
	WallType getType();

	void render() override;
	bool fire();
};


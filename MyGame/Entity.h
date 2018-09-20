#pragma once

#include <string>

#include "./Interfaces/Renderable.h"
#include "Coordinate2D.h"
#include "Texture.h"

class Entity : public Renderable
{
protected:

	Coordinate2D mPosition;

	void loadTexture() override = 0;
	
public:

	Entity();
	Entity(Coordinate2D _startCoord);
	virtual ~Entity();
	
	void render() override = 0;

	Coordinate2D getPosition();
	void setPosition(Coordinate2D _newPosition);
};


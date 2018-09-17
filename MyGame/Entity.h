#pragma once

#include "Renderable.h"
#include "Coordinate2D.h"

class Entity : public Renderable
{
protected:

	Coordinate2D mPosition;

public:

	Entity();
	virtual ~Entity();

	void render() override = 0;
};


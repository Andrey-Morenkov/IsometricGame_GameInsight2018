#pragma once

#include "../Entity.h"
#include "../Texture.h"
#include "World.h"

class MouseCursor : public Entity
{
private:

	Texture mTextureCursor;

public:
	MouseCursor();
	virtual ~MouseCursor();

	void render() override;

	Texture& getTextureCursor();
	Coordinate2D getPosition();
	void setPosition(Coordinate2D _newPosition);
};


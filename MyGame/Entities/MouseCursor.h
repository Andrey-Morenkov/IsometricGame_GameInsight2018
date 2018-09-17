#pragma once

#include "../Entity.h"
#include "../Texture.h"
#include "World.h"

class MouseCursor : public Entity
{
private:

	Texture mTextureCursor;
	World *mWorld;
	Coordinate2D mLastTileClicked;

	void getMouseTileClick();

public:
	MouseCursor();
	MouseCursor(World* _world);
	virtual ~MouseCursor();

	void render() override;

	World* getLocation();
	void setLocation(World* _world);
	Texture& getTextureCursor();
	Coordinate2D getPosition();
	void setPosition(Coordinate2D _newPosition);
};


#pragma once

#include "../Entity.h"
#include "../Texture.h"
#include "World.h"

class MouseCursor : public Entity
{
private:

	bool isCorrect;
	void loadTexture() override;

public:
	MouseCursor();
	virtual ~MouseCursor();

	void render() override;

	void setIsCorrect(bool _newState);
	bool getIsCorrect();
};


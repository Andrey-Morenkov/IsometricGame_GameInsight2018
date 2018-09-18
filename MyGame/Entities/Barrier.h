#pragma once
#include "../Entity.h"
#include "../Coordinate2D.h"
#include "../Texture.h"

class Barrier :	public Entity
{
private:

	int     mTextureType;
	Texture mTextureBarrier;

	int getRandomTexture();

public:
	
	Barrier();
	virtual ~Barrier();

	void render() override;

	Texture& getTextureBarrier();
	Coordinate2D getPosition();
	void setPosition(Coordinate2D _newPosition);
};


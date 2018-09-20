#pragma once
#include "../Entity.h"

class Barrier :	public Entity
{
private:

	int getRandomTexture();

	void loadTexture() override;

public:
	
	Barrier();
	virtual ~Barrier();

	void render() override;
};


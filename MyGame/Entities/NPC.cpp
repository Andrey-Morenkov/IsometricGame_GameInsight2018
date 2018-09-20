#include "NPC.h"
#include "../Settings.h"

void NPC::loadTexture()
{
	mSelfTexture.setWidthEachTextureTypeInPixels(NPC_TEXTURE_WIDTH_IN_PIXELS);
	mSelfTexture.setHeightEachTextureTypeInPixels(NPC_TEXTURE_HEIGHT_IN_PIXELS);
	mSelfTexture.loadFromPath(NPC_TEXTURE_PATH);
}

NPC::NPC()
{
	mDirection = EntityDirection::UP_LEFT; //default
	loadTexture();
	mTimeExeInSec = NPC_SPEED;
	//mPath.setCyclicMode(true);
}

NPC::NPC(Coordinate2D _startCoord) : NPC()
{
	mPosition = _startCoord;
}

NPC::~NPC()
{
}

Coordinate2D NPC::getProjectionToTileISOcoord()
{
	return Coordinate2D(mPosition.getX() + (NPC_TEXTURE_WIDTH_IN_PIXELS / 2), mPosition.getY() + NPC_TEXTURE_HEIGHT_IN_PIXELS);
}

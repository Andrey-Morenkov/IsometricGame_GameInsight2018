#pragma once
#include "../System.h"
class SystemRender : public System
{
private:
	unsigned int mCurrentRenderingTick;
	unsigned int mLastRenderedTick;
	unsigned int mMaxFPS;

	bool needRender();

public:
	SystemRender();
	virtual ~SystemRender();

	void run() override;
	void renderSuccessfulScreen();
	void renderDeadScreen();
};
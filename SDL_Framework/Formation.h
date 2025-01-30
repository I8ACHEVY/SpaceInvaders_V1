#pragma once

#include "GameEntity.h"
#include "GLGraphics.h"
#include "Timer.h"

using namespace SDL_Framework;

class Formation : public GameEntity {

public:
	Formation();
	~Formation();

	void Update() override;

	int GetTick();

	Vector2 GridSize();

	bool Locked();
	void Lock();

private:
	Timer* mTimer;

	//side to side
	bool mMovingRight;
	float mMovingSpeed;
	float mFormationBoundaryLeft;
	float mFormationBoundaryRight;

	//Drop
	float mDropAmount;
	float mDropTimer;
	float mDropDelay;

	//Offset
	float mOffsetAmount;
	float mOffsetTimer;
	float mOffsetDelay;
	int mOffsetCounter;
	int mOffsetDirection;

	//pulsing
	float mPulseTimer;
	float mPulseDelay;
	int mPulseCounter;
	int mPulseDirection;

	Vector2 mGridSize;

	bool mLocked;

};
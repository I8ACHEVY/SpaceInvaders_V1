#pragma once
#include "Enemy.h"


class Crab : public Enemy {

public:
	static void CreateDivePaths();

	//void Dive(int type = 0) override;

	void HandleFiring();

	void Hit(PhysEntity* other) override;

	Crab(int path, int index, bool challenge);
	~Crab();

private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	float mFireTimer;
	float mFireInterval;

	Vector2 LocalFormationPosition() override;

	void HandleDiveState() override;

	void RenderDiveState() override;

};
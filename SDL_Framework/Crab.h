#pragma once
#include "Enemy.h"


class Crab : public Enemy {

public:

	void Hit(PhysEntity* other) override;

	Crab(int path, int index, bool challenge);
	~Crab();

private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	Vector2 LocalFormationPosition() override;

};
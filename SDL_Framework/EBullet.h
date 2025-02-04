#pragma once

#include "PhysicsEntity.h"
#include "Timer.h"
#include "GLAnimatedTexture.h"

using namespace SDL_Framework;

class EBullet : public PhysEntity {
public:
	EBullet();
	~EBullet();

	void Update() override;
	void Render() override;

	void Hit(PhysEntity* other) override;

	void Fire(Vector2 pos);
	void Reload();

private:
	bool IgnoreCollision() override;

	static const int OFFSCREEN_BUFFER = 180;
	Timer* mTimer;
	GLAnimatedTexture* mAlienBullet;
	float mSpeed;
};

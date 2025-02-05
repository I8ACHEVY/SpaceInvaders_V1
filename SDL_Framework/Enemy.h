#pragma once

#include "BezierPath.h"
#include "GLAnimatedTexture.h"
#include "PhysicsEntity.h"
#include "Player.h"
#include "Formation.h"
#include "EBullet.h"

using namespace SDL_Framework;

class Enemy : public PhysEntity {
public:
	static int sActiveBullets;
	void FireCoolDown();
	bool Fire();
	void HandleFiring();

	enum States { FlyIn, Diving, InFormation, Dead };
	enum Types { Crab, Octopus, Squid, RedShips};

	static void CreatePaths();
	virtual void Dive(int type = 0);
	static void SetFormation(Formation* formation);
	static void CurrentPlayer(Player* player);

	States CurrentState();
	Types Type();
	int Index();

	Enemy(int path, int Index, bool Challenge);
	virtual ~Enemy();

	virtual void Hit(PhysEntity* other) override;
	bool InDeathAnimation();

	void Update() override;
	virtual void Render() override;

protected:
	static Formation* sFormation;
	static std::vector<std::vector<Vector2>> sPaths;
	static Player* sPlayer;

	Timer* mTimer;

	Texture* mTexture[2];

	Formation* mFormation;

	GLAnimatedTexture* mDeathAnimation;

	States mCurrentState;

	Types mType;

	int mIndex;

	unsigned mCurrentPath;
	Vector2 mDiveStartPosition;

	unsigned mCurrentWayPoint;
	const float EPSILON = 50.0f;

	float mSpeed;

	virtual void PathComplete();
	virtual void FlyInComplete();

	void JoinFormation();

	virtual Vector2 WorldFormationPosition();
	virtual Vector2 LocalFormationPosition() = 0;

	virtual void HandleFlyInState();
	virtual void HandleInFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState();

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderInFormationState();
	virtual void RenderDiveState() = 0;
	virtual void RenderDeadState();

	void RenderStates();

	bool IgnoreCollision() override;

	float mFireRate;
	//void FireBullet(Vector2 position, Vector2 direction);
	static const int MAX_EBULLETS = 1;
	EBullet* mEBullets[MAX_EBULLETS];
	AudioManager* mAudio;
};
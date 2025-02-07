#pragma once
#include "PlaySideBar.h"
#include "Player.h"
#include "Crab.h"
#include "Octopus.h"
#include "Squid.h"
#include "RedShip.h"
#include "TileLayer.h"
#include "Tinyxml2.h"
#include "EBullet.h"

using namespace SDL_Framework;
using namespace tinyxml2;

class Level : public GameEntity {

public:
	enum LevelStates {Running, Finished, GameOver};

	Level(int stage, PlaySideBar* sideBar, Player* player);
	~Level();

	LevelStates State();
	
	Enemy* SelectRandomEnemy();

	void Update() override;
	void Render() override;

private:
	Timer* mTimer;
	PlaySideBar* mSideBar;
	Player* sPlayer;
	Player* mStartTimer;
	Formation* mFormation;
	
	bool mMovingRight;
	float mSpeed;
	float mDropAmount;
	float mRightBoundary;
	float mLeftBoundary;
	int mRightBoundaryHits = 0;
	int mLeftBoundaryHits = 0;
	float mSpeedTimer;

	TileLayer* mBarrack1;
	TileLayer* mBarrack2;
	TileLayer* mBarrack3;
	TileLayer* mBarrack4;

	static const int MAX_CRABS = 22;
	static const int MAX_OCTOPI = 22;	
	static const int MAX_SQUIDS = 22;	
	static const int MAX_SHIPS = 1;	

	int mCrabCount;
	int mOctopusCount;
	int mSquidCount;
	int mShipCount;
	
	Crab* mFormationCrabs[MAX_CRABS];
	Octopus* mFormationOctopi[MAX_OCTOPI];
	Squid* mFormationSquids[MAX_SQUIDS];
	RedShip* mFormationShip[MAX_SHIPS];

	static const int MAX_EBULLETS = 2;
	EBullet* mEBullets[MAX_EBULLETS];
	//std::vector<EBullet*> mEBullets;
	float mFireCoolDown;
	float mFireRate;

	RedShip* mDivingShip;
	float mShipDiveDelay;
	float mShipDiveTimer;

	std::vector<Enemy*> mEnemies;	//debug testing
	Enemy* mEnemy;

	XMLDocument mSpawningPatterns;
	int mCurrentFlyInPriority;
	int mCurrentFlyInIndex;

	float mSpawnDelay;
	float mSpawnTimer;
	bool mSpawningFinished;

	int mStage; 
	bool mStageStarted;

	Texture* mReadyLabel;
	Scoreboard* mStageNumber;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Texture* mStageLabel;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	float mLabelTimer;

	bool mPlayerHit;
	float mRespawnDelay;
	float mRespawnTimer;
	float mRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LevelStates mCurrentState;

	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();
	
	void StartStage();

	bool EnemyFlyingIn();

	void HandleEnemyFiring(Vector2 bulletDirection);
	bool CanFire(Enemy* enemy);
	void FireEBullet(Enemy* enemy);

	void HandleEnemySpawning();
	void HandleEnemyFormation();
	void HandleEnemyDiving();
};
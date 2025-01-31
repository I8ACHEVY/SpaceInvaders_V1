#include "Enemy.h"
#include "PhysicsManager.h"
#include "Bullet.h"

std::vector<std::vector<Vector2>>Enemy::sPaths;
Player* Enemy::sPlayer = nullptr;
Formation* Enemy::sFormation = nullptr;

void Enemy::CreatePaths() {
	int screenXPoint = (int)(Graphics::Instance()->SCREEN_WIDTH * 0.46f);
	int screenYPoint = (int)(Graphics::Instance()->SCREEN_HEIGHT * 0.25f);

	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({
		Vector2(screenXPoint + 150.0f, screenYPoint + -10.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + -20.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + 30.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + 20.0f) }, 1
		);

	path->AddCurve({
		Vector2(screenXPoint + 150.0f, screenYPoint + 20.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + 100.0f),
		Vector2(320.0f, screenYPoint + 140.0f),
		Vector2(320.0f, screenYPoint + 300.0f) }, 25
		);

	path->AddCurve({
		Vector2(320.0f, screenYPoint + 300.0f),
		Vector2(320.0f, screenYPoint + 500.0f),
		Vector2(580.0f, screenYPoint + 600.0f),
		Vector2(580.0f, screenYPoint + 340.0f) }, 25
		);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	currentPath = 1;
	path = new BezierPath();
	int fullScreen = screenXPoint * 0.8;

	path->AddCurve({
		Vector2(screenXPoint - 50.0f, screenYPoint + -10.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + -20.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + 30.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + 20.0f) }, 1);

	path->AddCurve({
		Vector2(screenXPoint - 50.0f, screenYPoint + 20.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + 80.0f),
		Vector2(1070.0f, screenYPoint + 140.0f),
		Vector2(1070.0f, screenYPoint + 300.0f) }, 25);

	path->AddCurve({
		Vector2(1070.0f, screenYPoint + 300.0f),
		Vector2(1070.0f, screenYPoint + 500.0f),
		Vector2(830.0f, screenYPoint + 600.0f),
		Vector2(830.0f, screenYPoint + 340.0f) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	currentPath = 2;
	float temp = screenXPoint - 100.0f;

	path = new BezierPath();

	path->AddCurve({
		Vector2(280.0f, screenYPoint + 640.0f),
		Vector2(280.0f, screenYPoint + 640.0f),
		Vector2(310.0f, screenYPoint + 640.0f),
		Vector2(310.0f, screenYPoint + 640.0f) }, 1);

	path->AddCurve({
		Vector2(310.0f, screenYPoint + 640.0f),
		Vector2(400.0f, screenYPoint + 640.0f),
		Vector2(temp, screenYPoint + 500.0f),
		Vector2(temp, screenYPoint + 400.0f) }, 15);

	path->AddCurve({
		Vector2(temp, screenYPoint + 400.0f),
		Vector2(temp, screenYPoint + 200.0f),
		Vector2(320.0f, screenYPoint + 140.0f),
		Vector2(320.0f, screenYPoint + 300.0f) }, 15);

	path->AddCurve({
		Vector2(320.0f, screenYPoint + 300.0f),
		Vector2(320.0f, screenYPoint + 500.0f),
		Vector2(temp + 40.0f, screenYPoint + 600.0f),
		Vector2(temp + 40.0f, screenYPoint + 340.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	currentPath = 3;
	temp = screenXPoint + 60.0f;
	float temp2 = fullScreen - 40.0f;
	path = new BezierPath();

	path->AddCurve({
		Vector2(temp2 + 620.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 620.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 580.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 580.0f, screenYPoint + 640.0f) }, 1);

	path->AddCurve({
		Vector2(temp2 + 580.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 510.0f, screenYPoint + 640.0f),
		Vector2(temp + 130, screenYPoint + 500.0f),
		Vector2(temp + 130, screenYPoint + 400.0f) }, 15);

	path->AddCurve({
		Vector2(temp + 130, screenYPoint + 400.0f),
		Vector2(temp + 130, screenYPoint + 200.0f),
		Vector2(temp2 + 590.0f, screenYPoint + 140.0f),
		Vector2(temp2 + 590.0f, screenYPoint + 300.0f) }, 15);

	path->AddCurve({
		Vector2(temp2 + 590.0f, screenYPoint + 300.0f),
		Vector2(temp2 + 590.0f, screenYPoint + 500.0f),
		Vector2(temp + 120.0f, screenYPoint + 600.0f),
		Vector2(temp + 120.0f, screenYPoint + 340.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	currentPath = 4;		// side by side left bottom
	temp = screenXPoint - 100.0f;
	path = new BezierPath();

	path->AddCurve({
	Vector2(280.0f, screenYPoint + 600.0f),
	Vector2(280.0f, screenYPoint + 600.0f),
	Vector2(270.0f, screenYPoint + 600.0f),
	Vector2(270.0f, screenYPoint + 600.0f) }, 1);

	path->AddCurve({
	Vector2(270.0f, screenYPoint + 600.0f),
	Vector2(360.0f, screenYPoint + 600.0f),
	Vector2(temp - 40.0f, screenYPoint + 500.0f),
	Vector2(temp - 40.0f, screenYPoint + 440.0f) }, 15);

	path->AddCurve({
	Vector2(temp - 40.0f, screenYPoint + 440.0f),
	Vector2(temp - 40.0f, screenYPoint + 240.0f),
	Vector2(360.0f, screenYPoint + 180.0f),
	Vector2(360.0f, screenYPoint + 300.0f) }, 15);

	path->AddCurve({
	Vector2(360.0f, screenYPoint + 300.0f),
	Vector2(360.0f, screenYPoint + 500.0f),
	Vector2(temp, screenYPoint + 500.0f),
	Vector2(temp, screenYPoint + 340.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;


	currentPath = 5;			//edit to be side by side right bottom
	temp = screenXPoint + 60.0f;
	temp2 = fullScreen - 40.0f;
	path = new BezierPath();

	path->AddCurve({
		Vector2(temp2 + 620.0f, screenYPoint + 600.0f),
		Vector2(temp2 + 620.0f, screenYPoint + 600.0f),
		Vector2(temp2 + 560.0f, screenYPoint + 600.0f),
		Vector2(temp2 + 560.0f, screenYPoint + 600.0f) }, 1);

	path->AddCurve({
		Vector2(temp2 + 560.0f, screenYPoint + 600.0f),
		Vector2(temp2 + 560.0f, screenYPoint + 600.0f),
		Vector2(temp + 160, screenYPoint + 500.0f),
		Vector2(temp + 160, screenYPoint + 440.0f) }, 15);

	path->AddCurve({
		Vector2(temp + 160, screenYPoint + 440.0f),
		Vector2(temp + 160, screenYPoint + 240.0f),
		Vector2(temp2 + 560.0f, screenYPoint + 180.0f),
		Vector2(temp2 + 560.0f, screenYPoint + 300.0f) }, 15);

	path->AddCurve({
		Vector2(temp2 + 560.0f, screenYPoint + 300.0f),
		Vector2(temp2 + 560.0f, screenYPoint + 500.0f),
		Vector2(temp + 160.0f, screenYPoint + 500.0f),
		Vector2(temp + 160.0f, screenYPoint + 340.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;


	currentPath = 6;			//side by side top left hook
	path = new BezierPath();

	path->AddCurve({
		Vector2(screenXPoint + 190.0f, screenYPoint + -10.0f),
		Vector2(screenXPoint + 190.0f, screenYPoint + -20.0f),
		Vector2(screenXPoint + 190.0f, screenYPoint + 30.0f),
		Vector2(screenXPoint + 190.0f, screenYPoint + 20.0f) }, 1
		);

	path->AddCurve({
		Vector2(screenXPoint + 190.0f, screenYPoint + 20.0f),
		Vector2(screenXPoint + 190.0f, screenYPoint + 100.0f),
		Vector2(360.0f, screenYPoint + 140.0f),
		Vector2(360.0f, screenYPoint + 300.0f) }, 25
		);

	path->AddCurve({
		Vector2(360.0f, screenYPoint + 300.0f),
		Vector2(360.0f, screenYPoint + 500.0f),
		Vector2(540.0f, screenYPoint + 500.0f),
		Vector2(540.0f, screenYPoint + 340.0f) }, 25
		);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;


	currentPath = 7;			//side by side top right hook
	path = new BezierPath();

	path->AddCurve({
		Vector2(screenXPoint - 90.0f, screenYPoint + -10.0f),
		Vector2(screenXPoint - 90.0f, screenYPoint + -20.0f),
		Vector2(screenXPoint - 90.0f, screenYPoint + 30.0f),
		Vector2(screenXPoint - 90.0f, screenYPoint + 20.0f) }, 1);

	path->AddCurve({
		Vector2(screenXPoint - 90.0f, screenYPoint + 20.0f),
		Vector2(screenXPoint - 90.0f, screenYPoint + 80.0f),
		Vector2(1030.0f, screenYPoint + 140.0f),
		Vector2(1030.0f, screenYPoint + 300.0f) }, 25);

	path->AddCurve({
		Vector2(1030.0f, screenYPoint + 300.0f),
		Vector2(1030.0f, screenYPoint + 500.0f),
		Vector2(870.0f, screenYPoint + 500.0f),
		Vector2(870.0f, screenYPoint + 340.0f) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

}

void Enemy::SetFormation(Formation* formation) {
	sFormation = formation;
}

void Enemy::CurrentPlayer(Player* player) {
	sPlayer = player;
}

//void Enemy::HandleFiring() {
//	if (sPlayer == nullptr) return;
//
//	Vector2 playerPosition = sPlayer->Position();
//	Vector2 direction = (playerPosition - Position()).Normalized();
//
//	int numBullets = (rand() % 2) + 1;
//
//	for (int i = 0; i < MAX_BULLETS; i++) {
//		float spreadAngle = (rand() % 20 - 10) * DEG_TO_RAD;
//		Vector2 bulletDirection = (spreadAngle);
//
//		Bullet* bullet = new Bullet(false);
//		bullet->Fire(Position());
//		PhysicsManager::Instance()->RegisterEntity(bullet, PhysicsManager::CollisionLayers::HostileProjectile);
//
//		if (!mBullets[i]->Active()) {
//			mBullets[i]->Fire(Position());
//			//mAudio->PlaySFX("Fire.wav");
//			break;
//		}
//	}
//}

Enemy::Enemy(int path, int index, bool challenge) :
	mCurrentPath(path),mIndex(index), mChallengeStage(challenge){

	mTimer = Timer::Instance();

	mCurrentState = FlyIn;

	mCurrentWayPoint = 1;

	Position(sPaths[mCurrentPath][0]);

	mTexture[0] = nullptr;
	mTexture[1] = nullptr;
	
	mSpeed = 580.0f;

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	mDeathAnimation = new GLAnimatedTexture("EnemyExplosion.png", 0, 0, 128, 128, 5, 1.0f, Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	//for (int i = 0; i < MAX_BULLETS; i++) {
	//	mBullets[i] = new Bullet(true);
	//}
}

Enemy::~Enemy() {
	mTimer = nullptr;

	for (int i = 0; i < 2; i++) {
		delete mTexture[i];
		mTexture[i] = nullptr;
	}

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	//for (auto bullet : mBullets) {
	//	delete bullet;
	//	bullet = nullptr;
	//}
}

Enemy::States Enemy::CurrentState() {
	return mCurrentState;
}

Vector2 Enemy::WorldFormationPosition() {
	return sFormation->Position() + LocalFormationPosition();
}

void Enemy::FlyInComplete() {
	//if (mChallengeStage) {
	//	mCurrentState = Dead;	//change dead when adding challenge stages
	//}
	//else {
		JoinFormation();
	//}
}

void Enemy::JoinFormation() {
	Position(WorldFormationPosition());
	Rotation(0);
	Parent(sFormation);
	mCurrentState = InFormation;
}

void Enemy::PathComplete() {
	//if (mChallengeStage) {
	//	mCurrentState = Dead;	//change dead when adding challenge stages
	//}
}

Enemy::Types Enemy::Type() {
	return mType;
}

int Enemy::Index() {
	return mIndex;
}

void Enemy::Update() {
	if (Active()) {
		HandleStates();
	}
}

void Enemy::Render() {
	if (Active()) {
		RenderStates();
	}

	//for (int i = 0; i < MAX_BULLETS; i++) {
	//	mBullets[i]->Render();
	//}
}

void Enemy::HandleFlyInState() {
	if (mCurrentWayPoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWayPoint] - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((sPaths[mCurrentPath][mCurrentWayPoint] - Position()).MagnitudeSqr()
			< EPSILON * mSpeed / 25.0f) {

			mCurrentWayPoint++;
		}

		if (mCurrentWayPoint >= sPaths[mCurrentPath].size()) {
			PathComplete();
		}
	}
	else {
		Vector2 dist = WorldFormationPosition() - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			FlyInComplete();
		}
	}
}

void Enemy::HandleInFormationState() {
	Position(LocalFormationPosition());

	float rotation = Rotation();
	if (rotation != 0.0f) {
		if (rotation > 5.0f) {
			float rotationSpeed = 200.0f;
			float rotationDir = (rotation >= 180.0f) ? 1.0f : -1.0f;
			Rotate(rotationDir * mTimer->DeltaTime() * rotationSpeed);
		}
		else {
			Rotation(0.0f);
		}
	}
}

void Enemy::HandleDeadState() {
	if (mDeathAnimation->IsAnimating()) {
		mDeathAnimation->Update();
	}
}

void Enemy::RenderDeadState() {
	if (mDeathAnimation->IsAnimating()) {
		mDeathAnimation->Render();
	}
}

void Enemy::HandleStates() {
	switch (mCurrentState) {

	case FlyIn:
		HandleFlyInState();
		break;

	case InFormation:
		HandleInFormationState();
		break;

	case Dead:
		HandleDeadState();
		break;
	}
}

void Enemy::RenderFlyInState() {
	mTexture[0]->Render();
}

void Enemy::RenderInFormationState() {
	mTexture[sFormation->GetTick() % 2]->Render();
}

void Enemy::RenderStates() {
	switch (mCurrentState) {

	case FlyIn:
		RenderFlyInState();
		break;

	case InFormation:
		RenderInFormationState();
		break;

	case Dead:
		RenderDeadState();
		break;
	}
	PhysEntity::Render();
}

bool Enemy::IgnoreCollision(){
	return mCurrentState == Dead;
}

void Enemy::Hit(PhysEntity* other) {
	if (mCurrentState == InFormation) {
		Parent(nullptr);
	}

	mCurrentState = Dead;
}

bool Enemy::InDeathAnimation() {
	return mDeathAnimation->IsAnimating();
}
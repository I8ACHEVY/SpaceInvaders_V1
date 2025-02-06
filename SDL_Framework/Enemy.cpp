#include "Enemy.h"
#include "PhysicsManager.h"
#include "EBullet.h"

std::vector<std::vector<Vector2>>Enemy::sPaths;
Player* Enemy::sPlayer = nullptr;
Formation* Enemy::sFormation = nullptr;

void Enemy::CreatePaths() {
	int screenXPoint = (int)(Graphics::Instance()->SCREEN_WIDTH * 0.46f);
	int screenYPoint = (int)(Graphics::Instance()->SCREEN_HEIGHT * 0.25f);

	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({
		Vector2(screenXPoint - 350.0f, screenYPoint + -30.0f),
		Vector2(screenXPoint - 350.0f, screenYPoint + -50.0f),
		Vector2(120.0f, screenYPoint + 100.0f),
		Vector2(120.0f, screenYPoint + 100.0f) }, 1
		);

	path->AddCurve({
		Vector2(120.0f, screenYPoint + 100.0f),
		Vector2(120.0f, screenYPoint + 200.0f),
		Vector2(200.0f, screenYPoint + 340.0f),
		Vector2(300.0f, screenYPoint + 340.0f) }, 25
		);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	currentPath = 1;
	path = new BezierPath();
	int fullScreen = screenXPoint * 0.8;

	path->AddCurve({
		Vector2(screenXPoint + 400.0f, screenYPoint + -30.0f),
		Vector2(screenXPoint + 400.0f, screenYPoint + -50.0f),
		Vector2(900.0f, screenYPoint + 100.0f),
		Vector2(900.0f, screenYPoint + 100.0f) }, 1
	);

	path->AddCurve({
		Vector2(900.0f, screenYPoint + 100.0f),
		Vector2(900.0f, screenYPoint + 200.0f),
		Vector2(800.0f, screenYPoint + 340.0f),
		Vector2(700.0f, screenYPoint + 340.0f) }, 25
		);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	currentPath = 2;
	float temp = screenXPoint - 100.0f;

	path = new BezierPath();

	path->AddCurve({
	Vector2(screenXPoint - 350.0f, screenYPoint + -30.0f),
	Vector2(screenXPoint - 350.0f, screenYPoint + -50.0f),
	Vector2(120.0f, screenYPoint + 100.0f),
	Vector2(120.0f, screenYPoint + 100.0f) }, 1
	);

	path->AddCurve({
		Vector2(120.0f, screenYPoint + 100.0f),
		Vector2(120.0f, screenYPoint + 150.0f),
		Vector2(200.0f, screenYPoint + 300.0f),
		Vector2(300.0f, screenYPoint + 300.0f) }, 25
		);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	currentPath = 3;
	temp = screenXPoint + 60.0f;
	float temp2 = fullScreen - 40.0f;
	path = new BezierPath();

	path->AddCurve({
		Vector2(screenXPoint + 400.0f, screenYPoint + -30.0f),
		Vector2(screenXPoint + 400.0f, screenYPoint + -50.0f),
		Vector2(900.0f, screenYPoint + 100.0f),
		Vector2(900.0f, screenYPoint + 100.0f) }, 1
		);

	path->AddCurve({
		Vector2(900.0f, screenYPoint + 100.0f),
		Vector2(900.0f, screenYPoint + 150.0f),
		Vector2(800.0f, screenYPoint + 300.0f),
		Vector2(700.0f, screenYPoint + 300.0f) }, 25
		);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	currentPath = 4;		
	temp = screenXPoint - 100.0f;
	path = new BezierPath();

	path->AddCurve({
		Vector2(screenXPoint - 350.0f, screenYPoint + -30.0f),
		Vector2(screenXPoint - 350.0f, screenYPoint + -50.0f),
		Vector2(120.0f, screenYPoint + 100.0f),
		Vector2(120.0f, screenYPoint + 100.0f) }, 25
		);

	path->AddCurve({
		Vector2(120.0f, screenYPoint + 100.0f),
		Vector2(120.0f, screenYPoint + 120.0f),
		Vector2(200.0f, screenYPoint + 280.0f),
		Vector2(300.0f, screenYPoint + 280.0f) }, 25
		);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;


	currentPath = 5;			
	temp = screenXPoint + 60.0f;
	temp2 = fullScreen - 40.0f;
	path = new BezierPath();

	path->AddCurve({
		Vector2(screenXPoint + 400.0f, screenYPoint + -30.0f),
		Vector2(screenXPoint + 400.0f, screenYPoint + -50.0f),
		Vector2(900.0f, screenYPoint + 100.0f),
		Vector2(900.0f, screenYPoint + 100.0f) }, 25
		);

	path->AddCurve({
		Vector2(900.0f, screenYPoint + 100.0f),
		Vector2(900.0f, screenYPoint + 120.0f),
		Vector2(800.0f, screenYPoint + 280.0f),
		Vector2(700.0f, screenYPoint + 280.0f) }, 25
		);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	currentPath = 6;		
	path = new BezierPath();

	path->AddCurve({
		Vector2(1000.0f, 450.0f),
		Vector2(1000.0f, 500.0f),
		Vector2(1000.0f, 500.0f),
		Vector2(1000.0f, 450.0f) }, 1);
	
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
//	mFireRate -= mTimer->DeltaTime();
//	
//	if (sPlayer == nullptr) return;
//
//	for (int i = 0; i < MAX_EBULLETS; i++) {
//		if (!mEBullets[i]->Active()) {
//			Vector2 bulletDirection = Vector2(0, -1);
//			mEBullets[i]->Fire(Position() + bulletDirection);
//
//			EBullet* bullet = new EBullet();
//			bullet->Fire(Position() + bulletDirection);
//			PhysicsManager::Instance()->RegisterEntity(bullet, PhysicsManager::CollisionLayers::HostileProjectile);
//
//			break;
//		}
//	}
//}

Enemy::Enemy(int path, int index, bool challenge) :
	mCurrentPath(path),mIndex(index){

	mTimer = Timer::Instance();

	mCurrentState = FlyIn;

	mCurrentWayPoint = 1;

	Position(sPaths[mCurrentPath][0]);

	mTexture[0] = nullptr;
	mTexture[1] = nullptr;
	
	mSpeed = 100.0f; //580

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	mDeathAnimation = new GLAnimatedTexture("EnemyExplosion.png", 0, 0, 128, 128, 5, 1.0f, Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

}

Enemy::~Enemy() {
	mTimer = nullptr;

	for (int i = 0; i < 2; i++) {
		delete mTexture[i];
		mTexture[i] = nullptr;
	}

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

}

Enemy::States Enemy::CurrentState() {
	return mCurrentState;
}

Vector2 Enemy::WorldFormationPosition() {
	return sFormation->Position() + LocalFormationPosition();
}

void Enemy::FlyInComplete() {

	JoinFormation();
}

void Enemy::JoinFormation() {
	Position(WorldFormationPosition());
	Rotation(0);
	Parent(sFormation);
	mCurrentState = InFormation;
}

void Enemy::PathComplete() {

}

Enemy::Types Enemy::Type() {
	return mType;
}

int Enemy::Index() {
	return mIndex;
}

void Enemy::Dive(int type) {
	Parent(nullptr);
	mCurrentState = Diving;
	mDiveStartPosition = Position();
	mCurrentWayPoint = 1;
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

	case Diving:
		HandleDiveState();
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

	case Diving:
		RenderDiveState();
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
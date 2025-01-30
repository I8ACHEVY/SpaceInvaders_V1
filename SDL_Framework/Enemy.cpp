#include "Enemy.h"
#include "PhysicsManager.h"
#include "Bullet.h"

Player* Enemy::sPlayer = nullptr;
Formation* Enemy::sFormation = nullptr;

void Enemy::SetFormation(Formation* formation) {
	sFormation = formation;
}

void Enemy::CurrentPlayer(Player* player) {
	sPlayer = player;
}

void Enemy::HandleFiring() {
	if (sPlayer == nullptr) return;

	Vector2 playerPosition = sPlayer->Position();
	Vector2 direction = (playerPosition - Position()).Normalized();

	int numBullets = (rand() % 2) + 1;

	for (int i = 0; i < MAX_BULLETS; i++) {
		float spreadAngle = (rand() % 20 - 10) * DEG_TO_RAD;
		Vector2 bulletDirection = (spreadAngle);

		Bullet* bullet = new Bullet(false);
		bullet->Fire(Position());
		PhysicsManager::Instance()->RegisterEntity(bullet, PhysicsManager::CollisionLayers::HostileProjectile);

		if (!mBullets[i]->Active()) {
			mBullets[i]->Fire(Position());
			//mAudio->PlaySFX("Fire.wav");
			break;
		}
	}
}

Enemy::Enemy(int index, bool challenge) :
	mIndex(index), mChallengeStage(challenge){

	mTimer = Timer::Instance();

	mCurrentState = InFormation;

	mCurrentWayPoint = 1;
	// Position(sPaths[mCurrentPath][0]);

	mTexture[0] = nullptr;		// enemy new Texture("AnimatedEnemies.png", 0, 0, 52, 40);
	mTexture[1] = nullptr;
	
	mSpeed = 580.0f;

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	mDeathAnimation = new GLAnimatedTexture("EnemyExplosion.png", 0, 0, 128, 128, 5, 1.0f, Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i] = new Bullet(true);
	}
}

Enemy::~Enemy() {
	mTimer = nullptr;

	for (int i = 0; i < 2; i++) {
		delete mTexture[i];
		mTexture[i] = nullptr;
	}

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	for (auto bullet : mBullets) {
		delete bullet;
		bullet = nullptr;
	}
}

Enemy::States Enemy::CurrentState() {
	return mCurrentState;
}

Vector2 Enemy::WorldFormationPosition() {
	return sFormation->Position() + LocalFormationPosition();
}

void Enemy::JoinFormation() {
	Position(WorldFormationPosition());
	Rotation(0);
	Parent(sFormation);
	mCurrentState = InFormation;
}

void Enemy::PathComplete() {
	if (mChallengeStage) {
		mCurrentState = Dead;	//change dead when adding challenge stages
	}
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

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i]->Render();
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

	case Dead:
		HandleDeadState();
		break;
	}
}

void Enemy::RenderInFormationState() {
	mTexture[sFormation->GetTick() % 2]->Render();
}

void Enemy::RenderStates() {
	switch (mCurrentState) {

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
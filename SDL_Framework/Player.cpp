#include "Player.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {

	if (mInput->KeyDown(SDL_SCANCODE_A) || mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_D) || mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
	}

	Vector2 pos = Position(Local);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}

	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Position(pos);
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE) || mInput->MouseButtonPressed(InputManager::Left)) {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Position());
				mAudio->PlaySFX("Fire.wav");
				break;
			}
		}
	}
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mTag = "Player";
	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 3;

	mMoveSpeed = 250.0f;
	mMoveBounds = Vector2(300.0f, 780.0f);

	mTank = new GLTexture("InvaderSprites.png", 278, 228, 27, 17);
	mTank->Parent(this);
	mTank->Position(Vec2_Zero);

	mDeathAnimation = new GLAnimatedTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f,
		Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	AddCollider(new BoxCollider(mTank->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this,
		PhysicsManager::CollisionLayers::Friendly);

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i] = new Bullet(true);
	}
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mTank;
	mTank = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	for (auto bullet : mBullets) {
		delete bullet;
		bullet = nullptr;
	}
}

void Player::SetVisible(bool visible) {
	mVisible = visible;
}

void Player::StartTimer() {
	mStartTimer = 0.0f;
}

bool Player::IsVisible() {
	return mVisible;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

bool Player::WasHit() {
	return mWasHit;
}

bool Player::IgnoreCollision() {
	return !mVisible || mAnimating || !Active();
}

void Player::Hit(PhysEntity* other) {

	std::cout << "Player Hit by Tag" << other->GetTag() << std::endl;

	if (other->GetTag() == "EBullet") {
		mLives -= 1;
		mAnimating = true;
		mDeathAnimation->ResetAnimation();
		mAudio->PlaySFX("PlayerExplosion.wav", 0, -1);
		mWasHit = true;
	
	}
	else if (other->GetTag() == "Crab" || 
		other->GetTag() == "Octopus" || 
		other->GetTag() == "Squid" ||
		other->GetTag() == "RedShip") {

			mLives -= 100;
			mAnimating = true;
			mDeathAnimation->ResetAnimation();
			mAudio->PlaySFX("PlayerExplosion.wav", 0, -1);
			mWasHit = true;
	}

}

void Player::Update() {
	mStartTimer += mTimer->DeltaTime();

	if (mAnimating){
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();

		if (mWasHit) {
			mWasHit = false;
		}
	}
	else {
		if (Active()) {
			HandleMovement();
			if (mStartTimer >= 6.0f) {
				HandleFiring();
			}
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i]->Update();
	}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			mTank->Render();
		}

		PhysEntity::Render();
	}

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i]->Render();
	}
}
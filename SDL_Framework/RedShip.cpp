#include "RedShip.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> RedShip::sDivePaths;

void RedShip::CreateDivePaths() {
}

//void RedShip::Dive(int type) {
//
//}

Vector2 RedShip::LocalFormationPosition() {
	Vector2 retVal;
	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x =
		(sFormation->GridSize().x + sFormation->GridSize().x *
			2 * (mIndex / 2)) * (float)dir;
	retVal.y = -sFormation->GridSize().y * 2.8;

	return retVal;
}

void RedShip::HandleDiveState() {
	int currentPath = mIndex % 2;

	if (mCurrentWayPoint < sDivePaths[currentPath].size() &&
		!sPlayer->IsAnimating() && sPlayer->IsVisible()) {

		Vector2 waypointPos = mDiveStartPosition + sDivePaths
			[currentPath][mCurrentWayPoint];

		Vector2 dist = waypointPos - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);

		if (sPlayer->IsVisible()) {

			Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);
		}

		if ((waypointPos - Position()).MagnitudeSqr() < EPSILON * mSpeed / 25) {
			mCurrentWayPoint++;
		}
	}
	else {
		Vector2 dist = WorldFormationPosition() - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			JoinFormation();
		}
	}

}

void RedShip::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("PlayerExplosion.wav", 0, -1);
	sPlayer->AddScore(mCurrentState == Enemy::InFormation ? 80 : 160);
	Enemy::Hit(other);
}

void RedShip::RenderDiveState() {
	int currentPath = mIndex % 2;

	mTexture[0]->Render();

	Vector2 finalPos = WorldFormationPosition();
	auto currentDivePath = sDivePaths[currentPath];
	Vector2 pathEndPos = mDiveStartPosition + currentDivePath[currentDivePath.size() - 1];

}

RedShip::RedShip(int path, int index, bool challenge) :
	Enemy(path, index, challenge) {

	mTag = "RedShip";

	
		mTexture[0] = new GLTexture("InvaderSprites.png", 215, 223, 50, 24);
		mTexture[1] = new GLTexture("InvaderSprites.png", 215, 223, 50, 24);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		texture->Scale(Vector2(0.7f, 0.7f));
	}

	mType = Enemy::RedShips;


	AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));


	mId = PhysicsManager::Instance()->RegisterEntity(this,
	
	PhysicsManager::CollisionLayers::Hostile);

	mDeathAnimation = new GLAnimatedTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f,
		Animation::Layouts::Horizontal);
	
	mDeathAnimation->Parent();
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i] = new Bullet(true);
	}
}

RedShip::~RedShip() {
	if (mCollider) {
		delete mCollider;
		mCollider = nullptr;
	}

	if (mDeathAnimation) {
		delete mDeathAnimation;
		mDeathAnimation = nullptr;
	}

	for (auto bullet : mBullets) {
		delete bullet;
		bullet = nullptr;
	}
}

void RedShip::UpdateTexture(int index) {

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		texture->Scale(Vector2(0.7f, 0.7f));
	}
}

bool RedShip::IgnoreCollision(PhysEntity* Entity) {
	return !Active();
}

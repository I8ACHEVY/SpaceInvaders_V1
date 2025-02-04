#include "Squid.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> Squid::sDivePaths;

void Squid::CreateDivePaths() {
}

void Squid::RenderDiveState() {
	int currentPath = mIndex % 2;

	mTexture[0]->Render();

	Vector2 finalPos = WorldFormationPosition();
	auto currentDivePath = sDivePaths[currentPath];
	Vector2 pathEndPos = mDiveStartPosition + currentDivePath[currentDivePath.size() - 1];
}

void Squid::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("ButterflyDestroyed.wav", 0, -1);
	sPlayer->AddScore(20);
	Enemy::Hit(other);
	
}

void Squid::HandleDiveState() {
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

Vector2 Squid::LocalFormationPosition() {
	Vector2 retVal;
	int dir = mIndex % 2 == 0 ? -1 : 1;

	int enemiesPerRow = 11;
	int middle = enemiesPerRow / 2;
	retVal.x = (mIndex % enemiesPerRow - middle) * sFormation->GridSize().x * 1.2f;
	retVal.y = -sFormation->GridSize().y * 2.2 + sFormation->GridSize().y * 0.5f * 
	((mIndex / enemiesPerRow));

	return retVal;
}

Squid::Squid(int path, int index, bool challenge) :
	Enemy(path, index, challenge){

	mTag = "Squid";

	mTexture[0] = new GLTexture("InvaderSprites.png", 7, 225, 18, 18);
	mTexture[1] = new GLTexture("InvaderSprites.png", 40, 225, 18, 18);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		//texture->Scale(Vector2(1.7f, 1.7f));
	}

	mType = Enemy::Squid;

	mCurrentPath = 0;

	AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));

	mWasHit = false;
}

Squid::~Squid() {

}
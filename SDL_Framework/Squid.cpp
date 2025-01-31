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
	if (mWasHit) {
		Enemy::Hit(other);
		AudioManager::Instance()->PlaySFX("BossDestroyed.wav", 0, 2);
		sPlayer->AddScore(30);
		Enemy::Hit(other);
	}
	else {
		mWasHit = true;
		SDL_Rect temp = { 0, 64, 60, 64 };
		mTexture[0]->SetSourceRect(&temp);
		temp.x = 66;
		temp.y = 68;
		mTexture[1]->SetSourceRect(&temp);
		AudioManager::Instance()->PlaySFX("BossInjured.wav", 0, -1);
	}
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

	retVal.x =
		(sFormation->GridSize().x + sFormation->GridSize().x *
			2 * (mIndex / 2)) * (float)dir;
	retVal.y = -sFormation->GridSize().y;

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
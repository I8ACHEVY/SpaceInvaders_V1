#include "Octopus.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> Octopus::sDivePaths;

void Octopus::CreateDivePaths() {
}

void Octopus::RenderDiveState() {
	int currentPath = mIndex % 2;

	mTexture[0]->Render();

	Vector2 finalPos = WorldFormationPosition();
	auto currentDivePath = sDivePaths[currentPath];
	Vector2 pathEndPos = mDiveStartPosition + currentDivePath[currentDivePath.size() - 1];
}

Vector2 Octopus::LocalFormationPosition() {
	Vector2 retVal;

	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 
		2 * (mIndex / 4)) * (float)dir;

	retVal.y = sFormation->GridSize().y * 2 + sFormation->GridSize().y * 
		((mIndex % 4) / 2);

	return retVal;
}

void Octopus::HandleDiveState() {
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

void Octopus::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("WaspDestroyed.wav", 0, -1);
	sPlayer->AddScore(10);

	Enemy::Hit(other);
}

Octopus::Octopus(int path, int index, bool challenge) :
	Enemy(path, index, challenge){

	mTag = "Octopus";

	mTexture[0] = new GLTexture("InvaderSprites.png", 147, 226, 26, 24);
	mTexture[1] = new GLTexture("InvaderSprites.png", 179, 226, 26, 24);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		//texture->Scale(Vector2(1.7f, 1.7f));

	}

		mType = Enemy::Octopus;

		//AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));
}

Octopus::~Octopus() {

}

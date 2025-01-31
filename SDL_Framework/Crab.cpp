#include "Crab.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> Crab::sDivePaths;

void Crab::CreateDivePaths() {
}

void Crab::RenderDiveState() {
	int currentPath = mIndex % 2;

	mTexture[0]->Render();

	for (int i = 0; i < sDivePaths[currentPath].size() - 1; i++) {		// Dive path debugging sPath
		Graphics::Instance()->DrawLine(
			mDiveStartPosition.x + sDivePaths[currentPath][i].x,
			mDiveStartPosition.y + sDivePaths[currentPath][i].y,
			mDiveStartPosition.x + sDivePaths[currentPath][i + 1].x,
			mDiveStartPosition.y + sDivePaths[currentPath][i + 1].y
		);
	}

	Vector2 finalPos = WorldFormationPosition();
	auto currentDivePath = sDivePaths[currentPath];
	Vector2 pathEndPos = mDiveStartPosition + currentDivePath[currentDivePath.size() - 1];

	for (int i = 0; i < sPaths[mCurrentPath].size() - 1; i++) {		// debug bezier paths even after called sDivePaths
		Graphics::Instance()->DrawLine(
			sPaths[mCurrentPath][i].x,
			sPaths[mCurrentPath][i].y,
			sPaths[mCurrentPath][i + 1].x,
			sPaths[mCurrentPath][i + 1].y
		);
	}
}


Vector2 Crab::LocalFormationPosition() {
	Vector2 retVal;

	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 
		2 * (mIndex / 4)) * (float)dir;

	retVal.y = sFormation->GridSize().y * ((mIndex % 4) / 2);

	return retVal;
}

void Crab::HandleDiveState() {
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

void Crab::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("ButterflyDestroyed.wav", 0, -1); 
	sPlayer->AddScore(20);
	Enemy::Hit(other);
}

Crab::Crab(int path, int index, bool challenge) :
Enemy(path, index, challenge) 
{
	mTag = "Crab";

	mTexture[0] = new GLTexture("InvaderSprites.png", 74, 225, 24, 24);
	mTexture[1] = new GLTexture("InvaderSprites.png", 107, 225, 24, 24);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		//texture->Scale(Vector2(1.7f, 1.7f));
	}
	
	mType = Enemy::Crab;

	AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));
}

Crab::~Crab() {}

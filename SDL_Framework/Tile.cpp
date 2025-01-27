#include "Tile.h"
#include "BoxCollider.h"
#include "AudioManager.h"

void Tile::Hit(PhysEntity* other) {
	if (mWasHit) {
		Enemy::Hit(other);
		AudioManager::Instance()->PlaySFX("BossDestroyed.wav", 0, 2);
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

Vector2 Tile::LocalFormationPosition() {
	Vector2 retVal;
	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x =
		(sFormation->GridSize().x + sFormation->GridSize().x *
			2 * (mIndex / 2)) * (float)dir;
	retVal.y = -sFormation->GridSize().y;

	return retVal;
}

Tile::Tile(int index, bool challenge) :
	Enemy(index, challenge) {

	mTag = "Tile";

	mTexture[0] = new GLTexture("blockSheet.png", 56, 2, 16, 16);
	mTexture[1] = new GLTexture("blockSheet.png", 38, 2, 16, 16);
	mTexture[2] = new GLTexture("blockSheet.png", 20, 2, 16, 16);
	mTexture[3] = new GLTexture("blockSheet.png", 2, 2, 16, 16);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		//texture->Scale(Vector2(1.7f, 1.7f));
	}

	mType = Enemy::Tile;

	mCurrentTextureIndex = 0;
	AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));

	mWasHit = false;
}

Tile::~Tile() {
	for (int i = 0; i < 4; i++) {
		delete mTexture[i];
		mTexture[i] = nullptr;
	}
}
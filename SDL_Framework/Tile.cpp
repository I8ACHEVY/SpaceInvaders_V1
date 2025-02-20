#include "Tile.h"
#include "PhysicsManager.h"
#include "BoxCollider.h"
#include "AudioManager.h"

namespace SDL_Framework {

	Vector2 Tile::GetScaledDimensions() {
		return mTexture[0]->ScaledDimensions();
	}

	void Tile::Hit(PhysEntity* other) {
		mHitCount++;

		if (mHitCount >= 4) {
			this->Active(false);
			AudioManager::Instance()->PlaySFX("BossDestroyed.wav", 0, 2);
			return;
		}

		mCurrentTextureIndex = 3 - mHitCount;

		SDL_Rect temp = { mCurrentTextureIndex * 18, 2, 16, 16 };
		mTexture[mCurrentTextureIndex]->SetSourceRect(&temp);

		if (mHitCount == 3) {
			AudioManager::Instance()->PlaySFX("BossInjured.wav", 0, -1);
		}
	}

	Tile::Tile(int index, bool challenge) {

		mTag = "Tile";
		mCurrentTextureIndex = 0;
		mHitCount = 0;
		mWasHit = false;

		mTexture[0] = new GLTexture("blockSheet.png", 56, 2, 16, 16);
		mTexture[1] = new GLTexture("blockSheet.png", 38, 2, 16, 16);
		mTexture[2] = new GLTexture("blockSheet.png", 20, 2, 16, 16);
		mTexture[3] = new GLTexture("blockSheet.png", 2, 2, 16, 16);
		
		for (int i = 0; i < 4; i++) {
			mTexture[i]->Parent(this);
			mTexture[i]->Position(Vec2_Zero);
		}

		AddCollider(new BoxCollider(mTexture[0]->ScaledDimensions()));

		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Barracks);
	}

	Tile::~Tile() {
		for (int i = 0; i < 4; i++) {
			delete mTexture[i];
			mTexture[i] = nullptr;
		}
	}

	bool Tile::IgnoreCollision() {
        return !this->Active();
	}

    void Tile::Render() {
        if (this->Active()) {
            mTexture[mCurrentTextureIndex]->Render();
        }
    }
}
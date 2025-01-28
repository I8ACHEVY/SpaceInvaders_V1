#pragma once
#include "PhysicsEntity.h"
#include "Random.h"
#include "GLTexture.h"

namespace SDL_Framework {

	class Tile : public PhysEntity {
	public:

		Tile(int index, bool challenge);
		~Tile();

		void Hit(PhysEntity* other) override;
		bool IgnoreCollision() override;
		void Render() override;
		//void Update() override;

	private:
		int mHitCount;
		int mCurrentTextureIndex;
		bool mWasHit;

		GLTexture* mTexture[4];

	};
}

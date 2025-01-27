#pragma once
#include "Enemy.h"
#include "Random.h"
#include "GLTexture.h"

namespace SDL_Framework {

	class Tile : public Enemy {
	public:

		void Hit(PhysEntity* other) override;

		Tile(int index, bool challenge);
		~Tile();

		bool mWasHit;

	private:
		static std::vector<std::vector<Vector2>> sDivePaths;

		int mCurrentPath;

		int mCurrentTextureIndex;

	

		Vector2 LocalFormationPosition() override;

	};
}

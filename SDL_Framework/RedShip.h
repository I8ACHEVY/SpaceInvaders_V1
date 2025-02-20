#pragma once
#include "PhysicsManager.h"
#include "Enemy.h"

#include "Player.h"

namespace SDL_Framework {

	class RedShip :
		public Enemy{

	public:

		void UpdateTexture(int index);

		static void CreateDivePaths();

		void Dive(int type = 0) override;

		void Hit(PhysEntity* other) override;
		bool IgnoreCollision(PhysEntity* Entity);

		RedShip(int path, int index, bool challenge);
		~RedShip();

	private:
		static std::vector<std::vector<Vector2>> sDivePaths;

		GLTexture* mRedShip;
		PhysEntity* mCollider;

		bool mVisible;

		int mRedShipIndex;
		unsigned mCurrentPath;
		Vector2 mDiveStartPosition;

		Vector2 LocalFormationPosition() override;

		void HandleDiveState() override;
		void RenderDiveState() override;
	};
}
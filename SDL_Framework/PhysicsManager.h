#pragma once
#include <bitset>
#include "PhysicsEntity.h"

namespace SDL_Framework {

	class PhysicsManager {
	public:
		enum class CollisionLayers {
			Friendly,
			FriendlyProjectile,
			Hostile,
			HostileProjectile,
			Barracks,
			MaxLayers
		};

		enum class CollisionFlags {
			None = 0x00, //0000 0000
			Friendly = 0x01,
			FriendlyProjectile = 0x02,
			Hostile = 0x04,
			HostileProjectile = 0x08,
			Barracks = 0x10,
		};

		static PhysicsManager* Instance();
		static void Release();

		unsigned long RegisterEntity(PhysEntity* entity, CollisionLayers layer);
		void UnregisterEntity(unsigned long id);

		void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

		void Update();


	private:
		PhysicsManager();
		~PhysicsManager();

		static PhysicsManager* sInstance;
		std::vector<PhysEntity*>mCollisionLayers[
			static_cast<unsigned int>(CollisionLayers::MaxLayers)];

		std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>
			mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

		unsigned long mLastId;

	};

	inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, 
		PhysicsManager::CollisionFlags b) {

		return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | 
			static_cast<unsigned int>(b));
	}

	inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a,
		PhysicsManager::CollisionFlags b) {

		return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) &
			static_cast<unsigned int>(b));
	}

}
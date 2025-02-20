#pragma once
#include "GLTexture.h"

namespace SDL_Framework {
	
	class Collider : public GameEntity {
	public:
		enum class ColliderType { Box, Circle }; 

		Collider(ColliderType type);
		virtual ~Collider();

		virtual void Render();

		virtual Vector2 GetFurthestPoint() = 0;

		ColliderType GetType();

	protected:
		ColliderType mType;

		static const bool DEBUG_COLLIDERS = false;
		Texture* mDebugTexture;

		void SetDebugTexture(Texture* texture);
	};

}
#pragma once
#include "Collider.h"

namespace SDL_Framework{

	class CircleCollider : public Collider {
	public:
		CircleCollider(float radius, bool broadPhase = false);
		~CircleCollider();

		Vector2 GetFurthestPoint() override;

		float GetRadius();

	private:
		float mRadius;
	};

}
#include "EBullet.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool EBullet::IgnoreCollision() {
	return!Active();
}

EBullet::EBullet() {
	mTimer = Timer::Instance();

	//mTexture = new GLTexture("alienBullet.png");
	//mTexture->Parent(this);
	//mTexture->Position(Vec2_Zero);
	//mTexture->Scale(Vector2(0.7f, 0.7f));

	mAlienBullet = new GLAnimatedTexture("alienBullet.png", 1, 2, 8, 21, 2, 1.0f, Animation::Layouts::Horizontal);
	mAlienBullet->Parent(this);
	mAlienBullet->Position(Vec2_Zero);
	mAlienBullet->SetWrapMode(Animation::WrapModes::Loop);

	mSpeed = 100.0f;

	Reload();

	AddCollider(new BoxCollider(mAlienBullet->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectile);
	
}

EBullet::~EBullet() {
	mTimer = nullptr;

	delete mAlienBullet;
	mAlienBullet = nullptr;
}

void EBullet::Fire(Vector2 pos) {
	Position(pos);
	Active(true);
}

void EBullet::Reload() {
	Active(false);
}

void EBullet::Hit(PhysEntity* other) {
	Reload();
}

void EBullet::Update() {
	mAlienBullet->Update();
	if (Active()) {
		Translate(Vec2_Up * mSpeed * mTimer->DeltaTime());

		Vector2 pos = Position();
		if (pos.y < OFFSCREEN_BUFFER) {
			Reload();
		}
	}
}

void  EBullet::Render() {
	if (Active()) {
		mAlienBullet->Render();
		PhysEntity::Render();
	}
}
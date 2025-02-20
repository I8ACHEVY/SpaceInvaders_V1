#include "Level.h"

void Level::StartStage() {
	mStageStarted = true;
}

Level::Level(int stage, PlaySideBar* sideBar, Player* player){

	mTimer = Timer::Instance();
	mSideBar = sideBar;
	mSideBar->SetLevel(stage);

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	mStageLabel = new GLTexture("STAGE", "ARCADE.ttf", 40, { 0, 255, 0 });
	mStageLabel->Parent(this);
	mStageLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.6f);

	mStageNumber = new Scoreboard({ 0, 255, 0});
	mStageNumber->Score(stage);
	mStageNumber->Parent(this);
	mStageNumber->Position(Graphics::SCREEN_WIDTH * 0.56f, Graphics::SCREEN_HEIGHT * 0.6f);

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	mReadyLabel = new GLTexture("READY", "ARCADE.ttf", 40, { 150, 0,0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.6f);

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	sPlayer = player;
	mPlayerHit = false;
	mRespawnDelay = 3.0f;
	mRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new GLTexture("gameOverSprite.png", 0, 0, 300, 300);
	mGameOverLabel->Parent(this);
	mGameOverLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mGameOverDelay = 8.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 6.0f;

	mCurrentState = Running;

	int numRows = 2;
	int numTilesPerRow = 3;
	float spacing = 0.0f;

	mBarrack1 = new TileLayer(2, 3, 0.0f, 30.0f, 0.0f);
	mBarrack2 = new TileLayer(2, 3, 0.0f, 156.0f, 0.0f);
	mBarrack3 = new TileLayer(2, 3, 0.0f, 282.0f, 0.0f);
	mBarrack4 = new TileLayer(2, 3, 0.0f, 410.0f, 0.0f);

	mCrabCount = 0;
	mOctopusCount = 0;
	mSquidCount = 0;
	mShipCount = 0;

	std::string fullPath = SDL_GetBasePath();

	if (mStage == 1) {
		fullPath.append("Data/Level1.xml");
		mSpawningPatterns.LoadFile(fullPath.c_str());
		if (mSpawningFinished) {
			mSpawningPatterns.Clear();
		}
	}

	if (mStage == 2) {	
		fullPath.append("Data/Level2.xml");
		mSpawningPatterns.LoadFile(fullPath.c_str());
		std::cout << mStage << std::endl;
	}
		
	if (mStage == 3) {
		fullPath.append("Data/Level3.xml");
		mSpawningPatterns.LoadFile(fullPath.c_str());
		std::cout << mStage << std::endl;
	}

	if (mStage == 4) {
		fullPath.append("Data/Challenge.xml");
		mSpawningPatterns.LoadFile(fullPath.c_str());
		std::cout << mStage << std::endl;
	}

	mFormation = new Formation();
	mFormation->Position(Graphics::SCREEN_WIDTH * 0.5f, 560.0f);
	Enemy::SetFormation(mFormation);
	
	for (int i = 0; i < MAX_CRABS; i++) {
		mFormationCrabs[i] = nullptr;
	}

	for (int i = 0; i < MAX_OCTOPI; i++) {
		mFormationOctopi[i] = nullptr;
	}

	for (int i = 0; i < MAX_SQUIDS; i++) {
		mFormationSquids[i] = nullptr;
	}
	for (int i = 0; i < MAX_SHIPS; i++) {
		if (mFormationShip[i] = nullptr) {
			mFormationShip[i]->Position(Graphics::SCREEN_WIDTH * 0.9f, 560.0f);
		}
	}

	mMovingRight = true;
	mSpeed = 100.0f;
	mDropAmount = 5.0f;
	mRightBoundary = Graphics::SCREEN_WIDTH - 480.0f;
	mLeftBoundary = 480.0f;
	mSpeedTimer = 0.0f;
	
	mCurrentFlyInPriority = 0;
	mCurrentFlyInIndex = 0;
	mSpawnDelay = 0.2f;
	mSpawnTimer = 0.0f;
	mSpawningFinished = false;

	mDivingShip = nullptr;
	mShipDiveDelay = 5.0f;
	mShipDiveTimer = 0.0f;

	mFireCoolDown = 2.0f;
	mFireRate = 0.0f;

	for (int i = 0; i < MAX_EBULLETS; i++) {
		mEBullets[i] = new EBullet();
	}

	Enemy::CurrentPlayer(sPlayer);
}

Level::~Level() {
	mTimer = nullptr;
	mSideBar = nullptr;
	sPlayer = nullptr;
	

	delete mBarrack1;
	mBarrack1 = nullptr;

	delete mBarrack2;
	mBarrack2 = nullptr;

	delete mBarrack3;
	mBarrack3 = nullptr;

	delete mBarrack4;
	mBarrack4 = nullptr;

	delete mStageLabel;
	mStageLabel = nullptr;

	delete mStageNumber;
	mStageNumber = nullptr;

	delete mReadyLabel;
	mReadyLabel;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;

	delete mFormation;
	mFormation = nullptr;

	for (int i = 0; i < MAX_CRABS; i++) {
		delete mFormationCrabs[i];
		mFormationCrabs[i] = nullptr;
	}
	
	for (int i = 0; i < MAX_OCTOPI; i++) {
		delete mFormationOctopi[i];
		mFormationOctopi[i] = nullptr;
	}
	
	for (int i = 0; i < MAX_SQUIDS; i++) {
		delete mFormationSquids[i];
		mFormationSquids[i] = nullptr;
	}

	for (int i = 0; i < MAX_SHIPS; i++) {
		delete mFormationShip[i];
		mFormationShip[i] = nullptr;
	}

	for (auto enemy : mEnemies) {
		delete enemy;
		enemy = nullptr;
	}

	for (auto bullet : mEBullets) {
		delete bullet;
		bullet = nullptr;
	}

	mEnemies.clear();
}

Level::LevelStates Level::State() {
	return mCurrentState;
}

void Level::HandleStartLabels() {
	mLabelTimer += mTimer->DeltaTime();

	if (mLabelTimer >= mStageLabelOffScreen) {
		sPlayer->Active(true);
		sPlayer->SetVisible(true);
		sPlayer->StartTimer();

		if (mStage > 1) {
			StartStage();
		}
		else {
			if (mLabelTimer >= mReadyLabelOffScreen) {
				StartStage();
			}
		}
	}
}

void Level::HandleCollisions() {
	if (!mPlayerHit) {
		if (sPlayer->WasHit()) {
			mSideBar->SetTanks(sPlayer->Lives());

			mPlayerHit = true;
			mRespawnTimer = 0.0f;
			sPlayer->Active(false);
		}
	}
}

void Level::HandlePlayerDeath() {
	if (!sPlayer->IsAnimating()) {
		if (sPlayer->Lives() > 0) {
			if (mRespawnTimer == 0.0f) {
				sPlayer->SetVisible(false);
			}
			mRespawnTimer += mTimer->DeltaTime();
			if (mRespawnTimer >= mRespawnDelay) {
				sPlayer->Active(true);
				sPlayer->SetVisible(true);
				mPlayerHit = false;
			}
		}
		else {
			if (mGameOverTimer == 0.0f) {
				sPlayer->SetVisible(false);
			}
			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = GameOver;
			}
		}
	}
}

void Level::HandleEnemySpawning() {

	mSpawnTimer += mTimer->DeltaTime();
	
	if (mSpawnTimer >= mSpawnDelay) {
		XMLElement* element = mSpawningPatterns.FirstChildElement("Level")
			->FirstChild()->NextSiblingElement();
		bool spawned = false;
		bool priorityFound = false;
	
		while (element != nullptr) {
			int priority = element->IntAttribute("priority");
	
			if (mCurrentFlyInPriority == priority) {
				priorityFound = true;
				int path = element->IntAttribute("path");
				XMLElement* child = element->FirstChildElement();
	
				for (int i = 0; i < mCurrentFlyInIndex && child != nullptr; i++) {
					child = child->NextSiblingElement();
				}
	
				if (child != nullptr) {
					std::string type = child->Attribute("type");
					int index = child->IntAttribute("index");
	
				     if (type.compare("Crab") == 0) {
							
							mFormationCrabs[index] = new Crab(path, index, false);
							mEnemies.push_back(mFormationCrabs[index]);
							mCrabCount += 1;
					}
					else if (type.compare("Octopus") == 0) {

							mFormationOctopi[index] = new Octopus(path, index, false);
							mEnemies.push_back(mFormationOctopi[index]);
							mOctopusCount += 1;

					}
					else if (type.compare("Squid") == 0) {

							mFormationSquids[index] = new Squid(path, index, false);
							mEnemies.push_back(mFormationSquids[index]);
							mSquidCount += 1;

					}
	
					else if (type.compare("RedShip") == 0) {

							 mFormationShip[index] = new RedShip(path, index, false);
							 mShipCount += 1;

					 }
	
					spawned = true;
				}
			}
	
			element = element->NextSiblingElement();
		}

		if (!priorityFound) {
	
			mSpawningFinished = true;
		}
		else {
			if (!spawned) {
	
				if (!EnemyFlyingIn()) {
					mCurrentFlyInPriority += 1;
					mCurrentFlyInIndex = 0;
				}
			}
			else {
				mCurrentFlyInIndex += 1;
			}
		}
	
		mSpawnTimer = 0.0f;
	}
}

bool Level::EnemyFlyingIn() {
	for (Crab* crab : mFormationCrabs) {
		if (crab != nullptr &&
			crab->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	for (Octopus* octopi : mFormationOctopi) {
		if (octopi != nullptr &&
			octopi->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	for (Squid* squid : mFormationSquids) {
		if (squid != nullptr &&
			squid->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	for (RedShip* redShip : mFormationShip) {
		if (redShip != nullptr &&
			redShip->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	return false;
}

void Level::HandleEnemyFormation() {
	mFormation->Update();

	bool levelCleared = mSpawningFinished;

	float playerY = sPlayer->Position().y;

	for (Crab* crab : mFormationCrabs) {
		if (crab != nullptr) {
			crab->Update();

			if (crab->Position().y >= playerY) {
				if (mGameOverTimer == 0.0f) {
					sPlayer->SetVisible(false);
				}
				mGameOverTimer += mTimer->DeltaTime();
				if (mGameOverTimer >= mGameOverDelay) {
					mCurrentState = GameOver;
				}

			}

			if (crab->CurrentState() != Enemy::Dead ||
				crab->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	for (Octopus* octopus : mFormationOctopi) {
		if (octopus != nullptr) {
			octopus->Update();

			if (octopus->Position().y >= playerY) {
				if (mGameOverTimer == 0.0f) {
					sPlayer->SetVisible(false);
				}
				mGameOverTimer += mTimer->DeltaTime();
				if (mGameOverTimer >= mGameOverDelay) {
					mCurrentState = GameOver;
				}
			}

			if (octopus->CurrentState() != Enemy::Dead ||
				octopus->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	for (RedShip* redShip : mFormationShip) {
		if (redShip != nullptr) {
			redShip->Update();

			if (redShip->Position().y >= playerY) {
				if (mGameOverTimer == 0.0f) {
					sPlayer->SetVisible(false);
				}
				mGameOverTimer += mTimer->DeltaTime();
				if (mGameOverTimer >= mGameOverDelay) {
					mCurrentState = GameOver;
				}
			}

			if (redShip->CurrentState() != Enemy::Dead ||
				redShip->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	for (Squid* squid : mFormationSquids) {
		if (squid != nullptr) {
			squid->Update();

			if (squid->Position().y >= playerY) {
				if (mGameOverTimer == 0.0f) {
					sPlayer->SetVisible(false);
				}
				mGameOverTimer += mTimer->DeltaTime();
				if (mGameOverTimer >= mGameOverDelay) {
					mCurrentState = GameOver;
				}
			}

			if (squid->CurrentState() != Enemy::Dead ||
				squid->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	if (!mFormation->Locked()) {
		if (mCrabCount == MAX_CRABS &&
			mOctopusCount == MAX_OCTOPI &&
			mSquidCount == MAX_SQUIDS){	

			if (!EnemyFlyingIn()) {
				mFormation->Lock();
			}
		}
	}

	else {
		HandleEnemyDiving();
	}

	if (levelCleared) {
		mCurrentState = Finished;
	}
}

void Level::HandleEnemyDiving() {

	if (mDivingShip == nullptr) {
		mShipDiveTimer += mTimer->DeltaTime();

		if (mShipDiveTimer >= mShipDiveDelay) {

			for (int i = MAX_SHIPS - 1; i >= 0; i--) {

				if (mFormationShip[i] != nullptr &&
					mFormationShip[i]->CurrentState() == Enemy::InFormation) {

					mDivingShip = mFormationShip[i];
					mDivingShip->Dive();
					break;
				}
			}
			mShipDiveTimer = 0.0f;
		}
	}
	else {
		if (mDivingShip->CurrentState() != Enemy::Diving) {
			mDivingShip = nullptr;
		}
	}

}

Enemy* Level::SelectRandomEnemy() {
	std::vector<Enemy*> eligibleEnemies;

	for (Enemy* enemy : mEnemies) {

		if (mFormation->Locked()){
			eligibleEnemies.push_back(enemy);
		}
	}

	if (!eligibleEnemies.empty()) {
		int index = Random::Instance()->RandomRange(0, eligibleEnemies.size() - 1);
		return eligibleEnemies[index];
	}
	else {
		return nullptr;
	}
}

void Level::HandleEnemyFiring(Vector2 bulletDirection) {
	if (mFireRate >= mFireCoolDown ) {
		Enemy* firingEnemy = SelectRandomEnemy();

		if (firingEnemy) {
			for (int i = 0; i < MAX_EBULLETS; i++) {
				if (!mEBullets[i]->Active()) {
					mEBullets[i]->Fire(firingEnemy->Position());
					AudioManager::Instance()->PlaySFX("Fire.wav", 0, -1);
					mFireRate = 0.0f;
					break;
				}
			}
		}
	}
}

void Level::Update() {
	mBarrack1->Update();
	mBarrack2->Update();
	mBarrack3->Update();
	mBarrack4->Update();


	mFireRate += mTimer->DeltaTime();

	for (int i = 0; i < MAX_EBULLETS; i++) {
		if (mEBullets[i]->Active()) {
			mEBullets[i]->Update();
		}
	}

	if (mFireRate >= mFireCoolDown) {
		bool fired = false;

		for (int i = 0; i < MAX_CRABS; ++i) {
			if (mFormationCrabs[i] != nullptr && mFormationCrabs[i]->
				CurrentState() != Enemy::States::Dead) {
				HandleEnemyFiring(mFormationCrabs[i]->Position());
				fired = true;
				mFireRate = 0.0f;
				break;
			}
		}

		for (int i = 0; i < MAX_OCTOPI; ++i) {
			if (mFormationOctopi[i] != nullptr && mFormationOctopi[i]->
				CurrentState() != Enemy::States::Dead) {
				HandleEnemyFiring(mFormationOctopi[i]->Position());
				fired = true;
				mFireRate = 0.0f;
				break;
			}
		}

		for (int i = 0; i < MAX_SQUIDS; ++i) {
			if (mFormationSquids[i] != nullptr && mFormationSquids[i]->
				CurrentState() != Enemy::States::Dead) {
				HandleEnemyFiring(mFormationSquids[i]->Position());
				fired = true;
				mFireRate = 0.0f;
				break;
			}
		}
	}

	if (mFormation->Locked()) {
		for (Crab* crab : mFormationCrabs) {
			if (crab != nullptr) {
			}
		}

		for (Octopus* octopus : mFormationOctopi) {
			if (octopus != nullptr) {
			}
		}

		for (RedShip* redShip : mFormationShip) {
			if (redShip != nullptr) {
			}
		}

		for (Squid* squid : mFormationSquids) {
			if (squid != nullptr) {
			}
		}

		float deltaTime = mTimer->DeltaTime();

		if (mMovingRight) {
			mFormation->Translate(Vector2(mSpeed * deltaTime, 0.0f));

			if (mFormation->Position().x >= mRightBoundary) {
				mMovingRight = false;
				mRightBoundaryHits++;

				if (mRightBoundaryHits >= 3) {
					mFormation->Translate(Vector2(0.0f, mDropAmount));
					mRightBoundaryHits = 0;
				}
			}
		}
		else {
			mFormation->Translate(Vector2(-mSpeed * deltaTime, 0.0f));

			if (mFormation->Position().x <= mLeftBoundary) {
				mMovingRight = true;
				mLeftBoundaryHits++;

				if (mLeftBoundaryHits >= 3) {
					mFormation->Translate(Vector2(0.0f, mDropAmount));
					mLeftBoundaryHits = 0;
				}
			}
		}

		mSpeedTimer += mTimer->DeltaTime();
		if (mStage == 1) {
			if (mSpeedTimer >= 5.0f) {
				mSpeed += 10.0f;
				mSpeedTimer = 0.0f;
			}
		}

		if (mStage == 2) {
			if (mSpeedTimer >= 5.0f) {
				mSpeed += 15.0f;
				mSpeedTimer = 0.0f;
			}
		}

		if (mStage == 3) {
			if (mSpeedTimer >= 5.0f) {
				mSpeed += 20.0f;
				mSpeedTimer = 0.0f;
			}
		}

		if (mStage == 4) {
			if (mSpeedTimer >= 5.0f) {
				mSpeed += 25.0f;
				mSpeedTimer = 0.0f;
			}
		}
	}

	if (!mStageStarted) {
		HandleStartLabels();
	}
	else {


		if (!mSpawningFinished) {
			HandleEnemySpawning();
		}

		HandleEnemyFormation();


		for (auto& enemy : mEnemies) {
			enemy->Update();
		}

		HandleCollisions();

		if (mPlayerHit) {
			HandlePlayerDeath();
		}
		else {
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) {		//Testing
				mCurrentState = Finished;
			}
		}
	}
}

void Level::Render() {
	mBarrack1->Render();
	mBarrack2->Render();
	mBarrack3->Render();
	mBarrack4->Render();

	for (int i = 0; i < MAX_EBULLETS; i++) {
		if (mEBullets[i]->Active()) {
			mEBullets[i]->Render();
		}
	}

	if (!mStageStarted) {
		if (mLabelTimer > mStageLabelOnScreen &&
			mLabelTimer < mStageLabelOffScreen) {

			mStageLabel->Render();
			mStageNumber->Render();

		}

		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {
			mReadyLabel->Render();
		}
	}

	else {
		
		for (Crab* crab : mFormationCrabs) {
			if (crab != nullptr) {
				crab->Render();
			}
		}

		for (Octopus* octopus : mFormationOctopi) {
			if (octopus != nullptr) {
				octopus->Render();
			}
		}

		for (RedShip* redShip : mFormationShip) {
			if (redShip != nullptr) {
				redShip->Render();
			}
		}

		for (Squid* squid : mFormationSquids) {
			if (squid != nullptr) {
				squid->Render();
			}
		}

		if (mPlayerHit) {
			if (mRespawnTimer >= mRespawnLabelOnScreen) {
				mReadyLabel->Render();
			}

			if (mGameOverTimer >= mGameOverLabelOnScreen) {
				mGameOverLabel->Render();
			}
		}
	}
}
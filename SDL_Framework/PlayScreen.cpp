#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Position(Graphics::SCREEN_WIDTH * 0.87f, Graphics::SCREEN_HEIGHT * 0.05f);

	mStartLabel = new GLTexture("START", "ARCADE.ttf", 40, { 0, 255, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.48f);

	mScoreMap = new GLAnimatedTexture("InvaderSprites.png", 1, 313, 150, 85, 2, 1.0f, Animation::Layouts::Horizontal);
	mScoreMap->Parent(this);
	mScoreMap->Position(520, 640);
	mScoreMap->Scale(Vector2(2.0f, 2.0f));
	mScoreMap->SetWrapMode(Animation::WrapModes::Loop);

	mLevel = nullptr;
	mLevelStartDelay = 2.0f;
	mLevelStarted = false;

	mPlayer = nullptr;

	Enemy::CreatePaths();
	RedShip::CreateDivePaths();
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mSideBar;
	mSideBar = nullptr;

	delete mStartLabel;
	mStartLabel = nullptr;

	delete mScoreMap;
	mScoreMap = nullptr;

	delete mLevel;
	mLevel = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::StartNewGame() {
	delete mPlayer;
	mPlayer = new Player(); 
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(false);

	mSideBar->SetHighScore(645987);	//CREATE SAVE SYSTEM
	mSideBar->SetTanks(mPlayer->Lives());
	mSideBar->SetPlayerScore(mPlayer->Score());
	mSideBar->SetLevel(0);

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;

	mAudio->PlayMusic("GameStart.wav", 0);
}

void PlayScreen::StartNextLevel() {
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentStage, mSideBar, mPlayer);

}

bool PlayScreen::GameOver() {
	return !mLevelStarted ? false : (mLevel->State() == Level::GameOver);
}

void PlayScreen::Update() {
	mScoreMap->Update();

	if (mGameStarted) {
		if (!mLevelStarted) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
			}
		}
		else {
			mLevel->Update();

			if(mLevel->State() == Level::Finished) {
				mLevelStarted = false;
			}
		}
		
		if (mCurrentStage > 0) {
			mSideBar->Update();
		}

        if (mPlayer != nullptr) {
            mPlayer->Update();
        }
		mSideBar->SetPlayerScore(mPlayer->Score());
	}
	else {
		if (!Mix_PlayingMusic()) {
			mGameStarted = true;
		}
	}
}

void PlayScreen::Render() {
	if (!mGameStarted) {
		mStartLabel->Render();
		mScoreMap->Render();
	}

	if (mGameStarted) {
		if (mLevelStarted) {
			mLevel->Render();
		}

		mPlayer->Render();
	}
	mSideBar->Render();
}
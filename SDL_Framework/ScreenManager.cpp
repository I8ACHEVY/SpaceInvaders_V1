#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;
GLTexture* mBackground = nullptr;

ScreenManager* ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}
	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager() {
	mBackgroundStars = BackgroundStars::Instance();
	mBackground = new GLTexture("Background.png");
	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mOptionScreen = new OptionScreen();
	mCreditScreen = new CreditScreen();
	mHighScoreTable = new HighScoreTable();

	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	BackgroundStars::Release();
	mBackgroundStars = nullptr;

	if (mBackground != nullptr) {
		delete mBackground;
		mBackground = nullptr;
	}

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mOptionScreen;
	mOptionScreen = nullptr;

	delete mCreditScreen;
	mCreditScreen = nullptr;

	delete mHighScoreTable;
	mHighScoreTable = nullptr;
}

void ScreenManager::Update() {
	mBackgroundStars->Update();

	switch (mCurrentScreen) {
	case ScreenManager::Start:
		mStartScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			int selectedMode = mStartScreen->SelectedMode();

			if (selectedMode == 0) {
				mCurrentScreen = Play;
				mStartScreen->ResetAnimation();
				mPlayScreen->StartNewGame();
			}
			if (selectedMode == 1) {
				mCurrentScreen = Option;
			}
			if (selectedMode == 2) {
				mCurrentScreen = Credit;
			}
			if (selectedMode == 3) {
				mCurrentScreen = HighScore;
			}
		}

		break;

	case ScreenManager::Play:
		mPlayScreen->Update();

		if (mPlayScreen->GameOver()) {
			mCurrentScreen = Start;
		}
		break;

	case ScreenManager::Option:
		mOptionScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			int selectedMode = mOptionScreen->SelectedMode();

			if (selectedMode == 0) {
				mCurrentScreen = Play;
				mPlayScreen->StartNewGame();
			}
			if (selectedMode == 1) {
				mCurrentScreen = Credit;
			}
			if (selectedMode == 2) {
				mCurrentScreen = HighScore;
			}
			if (selectedMode == 3) {
				mCurrentScreen = Start;
			}
		}

		break;

	case ScreenManager::Credit:
		mCreditScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			int selectedMode = mCreditScreen->SelectedMode();

			if (selectedMode == 0) {
				mCurrentScreen = Play;
				mPlayScreen->StartNewGame();
			}
			if (selectedMode == 1) {
				mCurrentScreen = Option;
			}
			if (selectedMode == 2) {
				mCurrentScreen = HighScore;
			}
			if (selectedMode == 3) {

				mCurrentScreen = Start;
			}
		}

		break;

	case ScreenManager::HighScore:
		mHighScoreTable->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			int selectedMode = mHighScoreTable->SelectedMode();

			if (selectedMode == 0) {
				mCurrentScreen = Play;
				mPlayScreen->StartNewGame();
			}
			if (selectedMode == 1) {
				mCurrentScreen = Option;
			}
			if (selectedMode == 2) {
				mCurrentScreen = Credit;
			}
			if (selectedMode == 3) {
				mCurrentScreen = Start;
			}
		}

		break;

	default:
		std::cerr << "Unknown state found for game screen" << std::endl;
		break;
	}
}

void ScreenManager::Render() {

	switch (mCurrentScreen) {
		
	case ScreenManager::Start:
		mBackgroundStars->Render();
		mStartScreen->Render();
		break;

	case ScreenManager::Play:
		mBackground->Render();
		mBackground->Position(535, 660);
		mBackground->Scale(Vector2(1.3f, 1.3f));
		mPlayScreen->Render();
		break;

	case ScreenManager::Option:
		mBackgroundStars->Render();
		mOptionScreen->Render();
		break;

	case ScreenManager::Credit:
		mBackgroundStars->Render();
		mCreditScreen->Render();
		break;

	case ScreenManager::HighScore:
		mBackgroundStars->Render();
		mHighScoreTable->Render();
		break;

	default:
		break;
	}
}
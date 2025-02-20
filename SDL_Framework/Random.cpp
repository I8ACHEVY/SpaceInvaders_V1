#include "Random.h"

Random* Random::sInstance = nullptr;

Random* Random::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Random();
	}
	return sInstance;
}

void Random::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Random::Random() {
	unsigned seed =
		(unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	mGenerator.seed(seed);
}

Random::~Random() {

}

unsigned Random::RandomInt() {
	return mGenerator();
}

float Random::RandomFloat() {
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	
	return dist(mGenerator);
}

float Random::RandomRange(float lo, float hi) {
	std::uniform_real_distribution<float> dist(lo, hi);

	return dist(mGenerator);
}

int Random::RandomRange(int lo, int hi) {
	std::uniform_int_distribution<int> dist(lo, hi);

	return dist(mGenerator);
}
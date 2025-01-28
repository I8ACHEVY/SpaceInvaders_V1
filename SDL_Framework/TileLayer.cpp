#include "TileLayer.h"
#include "PhysicsManager.h"

namespace SDL_Framework {
	TileLayer::TileLayer(int numRows, int numTilesPerRow, float spacing) {
		const std::vector<float> xPositions = {400, 500, 600, 700}; 
		for (int j = 0; j < numRows; j++) {
			for (int i = 0; i < numTilesPerRow; i++) {
				Tile* tile = new Tile(i, false);
				float xPos = xPositions[i % xPositions.size()]; 
				tile->Position(Vector2(xPos, j * (tile->GetScaledDimensions().y + spacing) + 760));
				mTiles.push_back(tile);
			}
		}
	}
	TileLayer::~TileLayer() {
		for (Tile* tile : mTiles) {
			delete tile;
			tile = nullptr;
		}
		mTiles.clear();
	}
	void TileLayer::Render() {
		for (Tile* tile : mTiles) {
			tile->Render();
		}
	}
	
	void TileLayer::Update() {
		for (Tile* tile : mTiles) {
			tile->Update();
		}
	}
}

// render 
//int numRows = 3;
//int numTilesPerRow = 10;
//float spacing = 10.0f;

//mTileLayer = new TileLayer(numRows, numTilesPerRow, spacing);
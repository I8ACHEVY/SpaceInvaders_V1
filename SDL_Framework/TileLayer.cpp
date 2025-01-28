#include "TileLayer.h"
#include "PhysicsManager.h"

namespace SDL_Framework {
	TileLayer::TileLayer(int numRows, int numTilesPerRow, float spacing) {
		for (int j = 0; j < numRows; j++) {
			for (int i = 0; i < numTilesPerRow; i++) {
				Tile* tile = new Tile(i, false);
				tile->Position(Vector2(i * (tile->GetScaledDimensions().x + spacing),
									   j * (tile->GetScaledDimensions().y + spacing) + 500));
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
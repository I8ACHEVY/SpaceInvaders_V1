#include "TileLayer.h"
#include "PhysicsManager.h"

namespace SDL_Framework {
    TileLayer::TileLayer(int numRows, int numTilesPerRow, float spacing, float offsetX, float offsetY) {
        const std::vector<float> xPositions = {300, 316, 332}; 
        int tileCount = 0;
        for (int j = 0; j < numRows; j++) {
            for (int i = 0; i < numTilesPerRow; i++) {
                if (tileCount >= 5) return;
                Tile* tile = new Tile(i, false);

                float xPos = xPositions[i % xPositions.size()] + offsetX;

				float yPos = j * (tile->GetScaledDimensions().y + spacing) + 790 + offsetY;

				if (j == 0 || (j == 1 && (i == 0 || i == numTilesPerRow - 1))) {
					tile->Position(Vector2(xPos, yPos));
					mTiles.push_back(tile);
					tileCount++;
				}
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
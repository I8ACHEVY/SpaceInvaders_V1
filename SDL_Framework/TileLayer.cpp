#include "TileLayer.h"

namespace SDL_Framework {
	TileLayer::TileLayer(int rows, int columns) {
		tiles.resize(rows);
		for (int i = 0; i < rows; i++) {
			std::vector<Tile> row;

			for (int j = 0; j < columns; j++) {
				row.push_back(Tile(j, false));
			}
			tiles[i] = std::move(row);
		}
	}
	TileLayer::~TileLayer() {
		for (int i = 0; i < tiles.size(); i++) {
			for (int j = 0; j < tiles[i].size(); j++) {
				tiles[i].clear();
			}
			tiles[i].clear();
		}
		tiles.clear();
	}
	void TileLayer::Render() {
		for (int i = 0; i < tiles.size(); i++) {
			for (int j = 0; j < tiles[i].size(); j++) {
				tiles[i][j].Render();
			}
		}
	}
	void TileLayer::RemoveTile(int row, int column) {
		tiles[row][column].Hit(nullptr);
	}
    bool TileLayer::IsTileHit(int row, int column, const Bullet& bullet) {
        tiles[row][column].Hit(const_cast<Bullet*>(&bullet));
		return mWasHit = true;
    }
}
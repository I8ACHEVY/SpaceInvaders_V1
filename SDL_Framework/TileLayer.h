#pragma once
#include "Tile.h"
#include "GameEntity.h"
#include <vector>

namespace SDL_Framework {

	class TileLayer : public GameEntity {

	public:

		TileLayer(int numRows, int numTilesPerRow, float spacing);
		~TileLayer();

		void Render();

		void Update();

	private:
		std::vector<Tile*> mTiles;

	};
}
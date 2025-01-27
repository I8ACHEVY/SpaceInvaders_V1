#pragma once
#include "Tile.h"
#include "Bullet.h"

namespace SDL_Framework {

	class TileLayer {

	public:
		std::vector<std::vector<Tile>> tiles;

		TileLayer(int rows, int columns);
		~TileLayer();

		void Render();

		void RemoveTile(int rod, int column);

		bool IsTileHit(int row, int column, const Bullet& bullet);

	private:

		bool mWasHit;

	};
}
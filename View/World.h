#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <utility>
#include "Tile.h"
#include "Camera.h"

namespace model {

	class World {
		private:
			// TODO: Test with width != height.
			//X axis world dimension in tiles
			unsigned int dimentionX;

			//Y axis world dimension in tiles
			unsigned int dimentionY;

			//World's tiles height
			unsigned int tileHeight;

			//World's tiles width
			unsigned int tileWidth;

			std::vector<model::Tile*> tileArray;

			void setDimentionX(unsigned int dimentionX);

			void setDimentionY(unsigned int dimentionY);

			void setTileHeight(unsigned int tileHeight);

			void setTileWidth(unsigned int tileWidth);

		public:
			World();

			unsigned int getDimentionX();

			unsigned int getDimentionY();

			unsigned int getTileHeight();

			unsigned int getTileWidth();

			std::vector<model::Tile*>& getTileArray();

			void addTile(model::Tile* tile);

			void initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tileHeight, unsigned int tileWidth);

			void update();

			//TODO: Utility function. Might be unnecessary.
			std::pair<int,int> tileToPixelCoordinates(std::pair<int,int> tileCoordinates);

			std::pair<int,int> pixelToTileCoordinates(std::pair<int,int> pixelCoordinates);

			void cleanUp();

			~World();
	};

} // namespace model

namespace view {

	class World {
		public:
			World();

			model::World worldModel; //porque dentro de la clase esta declarado un objeto de la misma clase?? Hugo

			//TODO: the camera should be retrieved from the model.
			void render(model::Camera& camera);

			~World();
	};

} // namespace view

#endif //WORLD

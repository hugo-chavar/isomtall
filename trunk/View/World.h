#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <utility>
#include "TileView.h"
#include "Camera.h"
#include "Stage.h"
#include "Entity.h"
#include "Game.h"
#include <list>

using namespace model;
using namespace std;

namespace view {

	class World {
	private:
	
		//Se cargan una vez solamente los sprites
		vector<Sprite*> spriteArray;


		//std::vector<model::Tile*> tileArray;
		std::vector<TileView*> tileArray;

	public:
		World();

		//model::World worldModel;

		void update(); 
		// model::World worldModel; se reemplaza por Stage
		Stage worldModel;
		

		list<Entity *> entityList;
		//TODO: the camera should be retrieved from the model.
		void render(Camera& camera);

		void addTile(TileView* tile);

		std::vector<TileView*>& getTileArray();

				//TODO: Utility function. Might be unnecessary.
		std::pair<int,int> tileToPixelCoordinates(std::pair<int,int> tileCoordinates);

		std::pair<int,int> pixelToTileCoordinates(std::pair<int,int> pixelCoordinates);

		void initialize();

		~World();
	};

} // namespace view

#endif //WORLD

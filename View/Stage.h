#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <utility>
#include "TileView.h"
#include "Camera.h"
#include "Stage.h"
#include "Entity.h"
#include "Game.h"
#include "Personaje.h"
#include <list>

using namespace std;

namespace view {

	class Stage {
	private:
	
		//Se cargan una vez solamente los sprites
		vector<Sprite*> spriteArray;
		Personaje* pj;

		//std::vector<model::Tile*> tileArray;
		std::vector<TileView*> tileArray;

	public:
		Stage();

		//model::World worldModel;

		void update(); 
		// model::World worldModel; se reemplaza por Stage
		model::Stage worldModel;
		

		list<Entity *> entityList;
		//TODO: the camera should be retrieved from the model.
		void render(Camera& camera);

		void addTile(TileView* tile);

		std::vector<TileView*>& getTileArray();

		//std::pair<int,int> tileToPixelCoordinates(std::pair<int,int> tileCoordinates);

		//std::pair<int,int> pixelToTileCoordinates(std::pair<int,int> pixelCoordinates);

		void initialize();

		~Stage();
	};

} // namespace view

#endif //WORLD

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
#include "SpriteAnimado.h"
#include <list>

using namespace std;

namespace view {

	class Stage {
	private:
	
		//Se cargan una vez solamente los sprites
		vector<Sprite*> spriteArray;
		Personaje* _personaje;
		map<string,int> mapEntityToSprite;
		//list<Entity *> entityList;
		vector<vector<Entity*>> entityList;
		//std::vector<model::Tile*> tileArray;
		std::vector<TileView*> tileArray;

		void view::Stage::renderTile(int Xt, int Yt,Camera& camera);

	public:
		Stage();

		//model::World worldModel;

		void update(); 
		// model::World worldModel; se reemplaza por Stage
		model::Stage worldModel;
		

		//TODO: the camera should be retrieved from the model.
		void render(Camera& camera);

		void addTile(TileView* tile);

		std::vector<TileView*>& getTileArray();

		//std::pair<int,int> tileToPixelCoordinates(std::pair<int,int> tileCoordinates);

		//std::pair<int,int> pixelToTileCoordinates(std::pair<int,int> pixelCoordinates);

		bool initialize();

		~Stage();

		Personaje* personaje();
	};

} // namespace view

#endif //WORLD

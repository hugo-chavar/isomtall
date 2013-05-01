#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <utility>
#include <list>
//del modelo
#include "DataTypes.h"
#include "StageModel.h"
#include "Game.h"
//de la vista
#include "TileView.h"
#include "Camera.h"
#include "Entity.h"
#include "Personaje.h"
#include "SpriteAnimado.h"


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
		vector<TileView*> tileArray;
		map<KeyPair, TileView*> _tilesMap;

		void renderTile(int Xt, int Yt,Camera& camera);
		void loadGround();

	public:
		Stage();

		void update(); 
		StageModel* worldModel;

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

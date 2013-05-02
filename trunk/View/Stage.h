#ifndef _STAGE_H_
#define _STAGE_H_

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
	public:
		Stage();
		void update(); 
		void render(Camera& camera);

		//void addTile(TileView* tile);

		//std::vector<TileView*>& getTileArray();

		//std::pair<int,int> tileToPixelCoordinates(std::pair<int,int> tileCoordinates);

		//std::pair<int,int> pixelToTileCoordinates(std::pair<int,int> pixelCoordinates);

		bool initialize();

		~Stage();

		Personaje* personaje();

	private:
		//Se cargan una vez solamente los sprites
		vector<Sprite*> spriteArray;
		Personaje* _personaje;
		StageModel* worldModel;
		map<string,int> mapEntityToSprite;
		//list<Entity *> entityList;
		vector<vector<Entity*>> entityList;
		//std::vector<model::Tile*> tileArray;
		//vector<TileView*> tileArray;
		map<KeyPair, TileView*> tilesMap;
		TileView* firstTile;

		void renderTile(int Xt, int Yt,Camera& camera);
		void loadSprites();
		void generateStage();
		void deleteStage();
		TileView* createTile(TileModel* tile);
	};

}

#endif //_STAGE_H_

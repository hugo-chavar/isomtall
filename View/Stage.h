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
#include "RenderHelper.h"
#include "ItemView.h"


using namespace std;

namespace view {

	class Stage {
	public:
		Stage();
		~Stage();
		void update(); 
		void render(Camera& camera);
		bool initialize();
		void setTilesInCamera(int h, int v);
		StageModel* getWorldModel();
		TileView* getTileAt(KeyPair k);
		void initItemsFromString(std::string ItemsData);
		bool addOtherEntity(pair <int,int> position, string entityName);
		void removeOtherEntity(pair <int,int> tile);
		void updateItems(string serializedItemUpdates);
		void cleanUp();
	private:
		vector<Sprite*> spriteArray;
		vector<ItemView*> itemArray;
		StageModel* worldModel;
		map<string, int> mapEntityToSprite;
		map<KeyPair, TileView*> tilesMap;
		TileView* firstTile;
		vector <TileView*> tileLevels;
		int minLevelsInCamera;
		RenderHelper renderHelper;
		void calculateTilesToRender(Camera& camera);
		void loadSprites();
		void generateStage();
		void deleteStage();
		TileView* createTile(TileModel* tile);

		TileView* getFirstMatch(std::pair<int,int> k);
		TileView* getLastMatch(TileView* firstMatch, std::pair<int,int> k);
		void fixKeyLeftBottom(int level, std::pair<int,int> &k);
		void fixKeyRightBottom(int level, std::pair<int,int> &k);
		int fixLevel(std::pair<int,int> k);
		int fixStartLevel(int endLevel, std::pair<int,int> &ref);
		void alignLevel(std::pair<int,int> &k1, std::pair<int,int> &k2);
		void updateTiles();
		void updateSprites();
		ItemView* findDeathItem(string name);
		void updateItem(string serializedItemUpdate);
	};

}

#endif //_STAGE_H_

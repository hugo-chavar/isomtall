#ifndef _RENDERHELPER_H_
#define _RENDERHELPER_H_

#include "TileView.h"
#include "Camera.h"

using namespace std;

class RenderHelper {

public:
	RenderHelper();
	~RenderHelper();
	void clear();
	void startRenderingEntities();
	void setStartLevel(int);
	void setEndLevel(int);
	void setEmptyLevel();
	bool incomplete();
	bool hasLevelsToRender();
	bool currentIsEmpty();
	bool belongsToLevel(pair<int,int> );
	bool shouldRenderThis(pair<int,int>, pair<int,int> );
	pair<int,int> maxLevel(pair<int,int>, pair<int,int> );
	bool flip();
	void addLevel(TileView* ,TileView*);
	void renderNextLevel(Camera& camera);
	void renderGround(Camera& camera);

private:
	int startLevel;
	int endLevel;
	int currentLevel;
	int emptyStartLevel;
	int emptyEndLevel;
	list<pair<TileView*,TileView*>> limits;
	list<pair<TileView*, TileView*>>::iterator levelIterator;
	bool coin;

};


#endif //_RENDERHELPER_H_
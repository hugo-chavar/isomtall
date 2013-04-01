#include <map>
#include "..\Common\Logger.h"
#include "..\Common\DataTypes.h" 
#include "Tile.h"

using namespace std;
using namespace common;

namespace model
{
	//typedef pair<int,int> Key; //lo traigo del DataTypes.h

	class Stage
	{
	public:
		unsigned int width(); //este es el get
		unsigned int height();//este es el get
		void width(unsigned int); //este es el set
		void height(unsigned int); //este es el set
		unsigned int tileWidth(); 
		unsigned int tileHeight();
		void tileWidth(unsigned int);
		void tileHeight(unsigned int);
		void addTile(unsigned int, unsigned int, Tile*);
		void initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tileHeight, unsigned int tileWidth);
		void update();
	private:
		unsigned int _width;
		unsigned int _height;
		unsigned int _tileWidth;
		unsigned int _tileHeight;
		map<Key,Tile*> scene;

		//para insertar (no testeado) en scene un tile en la pos x=12, y=20:
		//Key clave(12,20);
		//scene.insert(std::make_pair(clave, &unTile));
	};

	

}
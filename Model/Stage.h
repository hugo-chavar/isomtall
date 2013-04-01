#include <map>
#include "..\Common\DataTypes.h" 
#include "Tile.h"

using namespace std;

namespace model
{
	//typedef pair<int,int> Key; //lo traigo del DataTypes.h

	class Stage
	{
	public:
		int width(); //este es el get
		int height();//este es el get
		void width(int); //este es el set
		void height(int); //este es el set
	private:
		int _width;
		int _height;
		map<Key,Tile*> scene;

		//para insertar en scene un tile en la pos x=12, y=20:
		//Key clave(12,20);
		//scene.insert(std::make_pair(clave, &unTile));
	};

	

}
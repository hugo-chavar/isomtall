#ifndef _ENTITYOBJECT_H_
#define _ENTITYOBJECT_H_

#include <string>

using namespace std;

namespace model
{
	class EntityObject
	{

	public:
		EntityObject();
		int positionX(); //este es el get
		int positionY();//este es el get
		void position(int,int); //este es el set
		string imagePath(); //este es el get
		void imagePath(string); //este es el set
	private:
		int _positionX;
		int _positionY;
		string _imagepath;
	};

}

#endif //_ENTITYOBJECT_H_
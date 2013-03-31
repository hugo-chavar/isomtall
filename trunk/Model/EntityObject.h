#include <string>

using namespace std;

namespace model
{
	class EntityObject
	{

	public:
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
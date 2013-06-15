#include "Shield.h"
#define DEFAULT_RESISTANCE 50
#define DEFAULT_ABSORTION 10


Shield::Shield(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself):ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
	vector<string> arguments;
	string _arguments=Game::instance().world()->getItemInfo(_name);
	stringUtilities::splitString(_arguments,arguments,',');
	if(_arguments.size()>0 && arguments.size()==2)
	{
		this->resistance=stringUtilities::stringToFloat(stringUtilities::substrAfterFirst(arguments[0],'='));
		this->absortion=stringUtilities::stringToFloat(stringUtilities::substrAfterFirst(arguments[1],'='));
	}
	else
	{
		this->resistance=DEFAULT_RESISTANCE;
		this->absortion=DEFAULT_ABSORTION;
	}

}


Shield::~Shield(void)
{
}

void Shield::modifyCharacter(Personaje* personaje)
{
	personaje->setShield(this->resistance,this->absortion);
}
#include "RunningBoots.h"


RunningBoots::RunningBoots(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
	vector<string> arguments;
	string _arguments=Game::instance().world()->getItemInfo(_name);
	stringUtilities::splitString(_arguments,arguments,',');
	if(_arguments.size()>0 && arguments.size()==1)
		this->factor=stringUtilities::stringToFloat(stringUtilities::substrAfterFirst(arguments[0],'='));
	else
		this->factor=FACTORVEL;
}


RunningBoots::~RunningBoots(void)
{
}

void RunningBoots::modifyCharacter(Personaje* personaje)
{
	personaje->increaseSpeed(this->factor);
}
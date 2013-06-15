#include "Lamp.h"

#define DEFAULT_INCREMENT 3

Lamp::Lamp(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
	vector<string> arguments;
	string _arguments=Game::instance().world()->getItemInfo(_name);
	stringUtilities::splitString(_arguments,arguments,',');
	if(_arguments.size()>0 && arguments.size()==1)
		this->incremento=stringUtilities::stringToInt(stringUtilities::substrAfterFirst(arguments[0],'='));
	else
		this->incremento=DEFAULT_INCREMENT;
}


Lamp::~Lamp(void)
{
}

void Lamp::modifyCharacter(Personaje* personaje)
{
	//int incrementar = 3; //TODO: Yami, traelo del parser
	personaje->personajeModelo()->getVision()->increaseRangeVision(this->incremento);
}
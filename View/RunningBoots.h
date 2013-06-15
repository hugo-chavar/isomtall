#pragma once
#include "ItemView.h"
#define FACTORVEL 1.5 //factor de aumento del rango de velocidad

class RunningBoots : public ItemView
{
private:
	float factor;
public:
	RunningBoots(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~RunningBoots(void);
	void modifyCharacter(Personaje* personaje);
};


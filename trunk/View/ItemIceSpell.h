#ifndef _ITEM_ICE_SPELL_H_
#define _ITEM_ICE_SPELL_H_

#include "ItemView.h"

class ItemIceSpell : public ItemView { 
public:
	ItemIceSpell(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~ItemIceSpell(void);
	void modifyCharacter(Personaje* personaje);
};

#endif // _ITEM_ICE_SPELL_H_

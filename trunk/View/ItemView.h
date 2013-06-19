#pragma once
#include "Entity.h"
#include "Game.h"
#include "Personaje.h"
#include "stringUtilities.h"


class ItemView: public Entity,public Daniable
{

protected:

	//unsigned state;
	//bool hidden;
	//bool alive;

	//Andy agrego
	int regenerationTime;
	bool canReviveForHimself;
	//Andy agrego

	SDL_Rect hiddenSpriteRect;
	Sprite * hiddenSprite;
	void setHiddenRectangle(std::pair<int, int> pos, Sprite* sprite );
	bool isWood();
	//string name;

public:
	//string getName();
	virtual void modifyCharacter(Personaje* personaje);
	ItemView(int tileX,int tileY,Sprite* spriteCargado,Sprite * _hiddenSprite,unsigned _state,string _name);
	~ItemView();
	void update();
	void render(Camera& camera);
	bool isHidden();
	void uncover();
	void revive(unsigned _state,pair <int,int> pos);
	bool isAlive();
	void kill();

	//MetodosSinglePlayer
	ItemView(std::string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	void updateSinglePlayer();
	void killSinglePlayer();
	void reviveSinglePlayer(unsigned _state,std::pair <int,int> _pos);

	std::string getName();
	void recibirDano(float dano);
	bool isItem();
	bool getCanReviveForHimself();
	//MetodosSinglePlayer
};


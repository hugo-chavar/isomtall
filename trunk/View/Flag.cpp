#include "Flag.h"
#include "GameView.h"


Flag::Flag() {
	vidaActual = 100; // HARCODEADO
	entity =  Game::instance().yParser.findAnimatedEntityType("bandera");
	bool validPosition = false;
	std::pair<int,int> position;
	while (!validPosition) {
		position.first = rand() % Game::instance().world()->width();
		position.second = rand() % Game::instance().world()->height();
		if ((!GameView::instance().getWorldView()->getTileAt(position)->hasOtherEntity()) && (!GameView::instance().getWorldView()->getTileAt(position)->getRelatedTile()))
			validPosition = true;
	}
	position.first = 4;
	position.second = 3;
	this->setPosition(position);
	//tileActual.first = 4;//position.first;
	//tileActual.second = 3;//position.second;
	GameView::instance().getWorldView()->addOtherEntity(this->getPosition(), entity->name());
	Game::instance().world()->getTileAt(this->getPosition())->setOtherEntity(entity);
}

Flag::~Flag() { }

string Flag::getName() {
	return entity->name();
}

void Flag::destroy() {
	GameView::instance().getWorldView()->removeOtherEntity(this->getPosition());
	Game::instance().world()->getTileAt(this->getPosition())->setOtherEntity(NULL);
}
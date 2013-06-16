#include "ImpactAmmo.h"
#include "GameView.h"

ImpactAmmo::ImpactAmmo():Ammunition() {
}

ImpactAmmo::~ImpactAmmo(){
}

void ImpactAmmo::verify() {
	Movable::verify();
	this->impact(GameView::instance().getDaniableInTile(this->getCurrentTile()));
}

void ImpactAmmo::impact(Daniable*) {
	//only to override
}
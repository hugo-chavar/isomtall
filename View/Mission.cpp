#include "Mission.h"
#include "GameView.h"

Mission::Mission() { }

Mission::~Mission() {
	for (unsigned int i = 0; i < flags.size(); i++) {
		delete flags[i];
	}
	flags.clear();
}

void Mission::initialize() {
	int numberOfFlags = 1 + rand() % 5;
	for (int i=0; i<numberOfFlags; i++) {
		flags.push_back(new Flag());
	}
}

int Mission::findFlag(Flag* flag) {
	for (unsigned int i=0; i<flags.size(); i++) {
		if (flags[i] == flag)
			return i;
	}
	return -1;
}

bool Mission::isAFlag(Daniable* entity) {
	for (unsigned int i=0; i<flags.size(); i++) {
		if (flags[i] == entity) {
			return true;
		}					
	}
	return false;
}

void Mission::missionUpdate(Daniable* victim, string attacker) {
	if (isAFlag(victim)) {
		Flag* flag = static_cast<Flag*>(victim);
		if (!flag->Daniable::isAlive()) {
			int flagNumber = findFlag(flag);
			pair <int,int> position = flags[flagNumber]->getPosition();
			GameView::instance().getWorldView()->removeOtherEntity(position);
			flags[flagNumber]->destroy();
			delete flags[flagNumber];
			flags.erase(flags.begin()+flagNumber);
			GameView::instance().getWorldView()->addOtherEntity(position, "banderaDestruida");
		}
	}
}

bool Mission::isGameOver() {
	return (flags.empty());
}

Daniable* Mission::manageAttack(pair <int,int> tile) {
	vector <Flag*>::iterator it;
	for (it=flags.begin(); it!=flags.end(); it++)
		if ((*it)->getPosition() == tile)
			return *it;
	return NULL;
}
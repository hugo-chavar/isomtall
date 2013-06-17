#ifndef __MISSION_H__
#define __MISSION_H__

#include <vector>
#include "Flag.h"
#include "Daniable.h"

using namespace std;


class Mission {

public:
	Mission();
	~Mission();
	void initialize();
	void missionUpdate(Daniable* victim, string attacker);
	string manageMissionInitialSynch();
	string manageMissionChange();
	Daniable* manageAttack(pair <int,int> tile);
	bool isGameOver();

private:
	int findFlag(Flag* flag);
	bool isAFlag(Daniable* entity);
	vector <Flag*> flags;

};

#endif
#include "HechizoProteccion.h"
#include "Personaje.h"
#include "GameView.h"



HechizoProteccion::HechizoProteccion(float coste, std::string spellId) : Hechizo(coste, spellId) {
}


HechizoProteccion::~HechizoProteccion() {
}

bool HechizoProteccion::startSpell(std::string actualCaster) {
	Personaje* invocador = NULL;
	invocador = GameView::instance().getMyPersonaje();
	if (invocador == NULL) {
		return false;
	}
	if (invocador->useMagic(cost)) {
		//ACA COMENTE FER
		//invocador->setInvulnerable(true);
		//invocador->setProtCost(this->cost);
		//invocador->setProtTime(0.0);
		return true;
	}
	return false;
}
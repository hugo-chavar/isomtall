#include "HechizoTerremoto.h"
#include "Personaje.h"
#include "GameView.h"

HechizoTerremoto::HechizoTerremoto(float coste, std::string spellId) : Hechizo(coste, spellId)
{
}


HechizoTerremoto::~HechizoTerremoto(void)
{
}

bool HechizoTerremoto::startSpell(std::string actualCaster) {
	Personaje* invocador = NULL;
	invocador = GameView::instance().getMyPersonaje();
	if (invocador == NULL) {
		return false;
	}
	if (invocador->useMagic(cost)) {
		//Realizar el terremoto
		GameView::instance().getCamera()->setVibrating();
		return true;
	}
	return false;
}
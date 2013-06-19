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
		this->setRange(5);
		this->activate();
		this->range.fill();
		std::pair<int, int > aux;
		while (this->range.hasNext()) {
			aux = this->range.next();
			Daniable* daniable = GameView::instance().getDaniableInTile(aux);
			if (daniable) {
				daniable->recibirDano(30.0);
				if (!(daniable->isAlive()))
					GameView::instance().getMission()->missionUpdate(daniable, this->getOwner());
			}
		}
		return true;
	}
	return false;
}
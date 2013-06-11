#include "Personaje.h"
#include "../Model/PersonajeConstantes.h"
#include "SDL_ttf.h"
#include "Logger.h"
#include "StringUtilities.h"

#include "Game.h"
#include "GameView.h"

#define BAR_HEIGHT 4

Personaje::Personaje(PersonajeModelo* pj) {
	this->font = NULL;
	modelo = pj;
	tileActual = pj->getPosition();
	this->setCurrentSpritePosition(this->calculateSpritePosition(pj->getEstado()));
	velocidad = pj->getVelocidad();
	delta.first = 0;
	delta.second = 0;
	ePot.first = 0;
	ePot.second = 0;
	serr = 0;
	//if (!(this->getPlayerName().empty())) {
	//	crearNombre(this->getPlayerName());
	//}
	this->labelName = NULL;
	this->playerName = "";
	this->lifeBarG = NULL;
	this->lifeBarR = NULL;
	this->magicBarNeg = NULL;
	this->magicBarPos = NULL;
	this->barWidth = 0;
	this->vidaActual = modelo->getVidaMaxima();
	this->magiaActual = modelo->getMagiaMaxima();
	this->setFogged(false);
	this->setCenteredInTile(true);
	this->setActive(false);
	this->resetSpriteState();
}

void Personaje::createStatsBar() {
	int height;
	
	height = BAR_HEIGHT;
	barWidth = (int) (spriteRect.w * 0.75);

	this->magicBarPos = SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_SWSURFACE, barWidth, height, 32, 0, 0, 0, 0));
	this->magicBarNeg = SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_SWSURFACE, barWidth, height, 32, 0, 0, 0, 0));

    this->lifeBarG = SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_SWSURFACE, barWidth, height, 32, 0, 0, 0, 0));
	this->lifeBarR = SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_SWSURFACE, barWidth, height, 32, 0, 0, 0, 0));
}

void Personaje::updateStatsBar() {
	int porcActualVida = (int) ((vidaActual)*100/(modelo->getVidaMaxima()));
	int porcActualMagia = (int) ((magiaActual)*100/(modelo->getMagiaMaxima()));

	magicBarPos->w = ((barWidth) * porcActualMagia)/100;
	lifeBarG->w = ((barWidth) * porcActualVida)/100;
}

void Personaje::createLabelName() {
	this->labelName = TTF_RenderText_Blended(this->font, this->getPlayerName().c_str(), Camera::WHITE_COLOR );
}

void Personaje::loadSprites() {
	AnimatedEntity* animatedEntity;
	animatedEntity = new AnimatedEntity();
	animatedEntity->copy(modelo->getAnimation());
	modelo->restartDirectories();
	animatedEntity->loadImages(modelo->nextDirectory());
	this->addFirstSprite(animatedEntity);

	while (modelo->hasDirectoryRemaining()) {
		animatedEntity->loadImages(modelo->nextDirectory());
		this->addNextSprite(animatedEntity);
		animatedEntity->clearImages();
	}

	delete animatedEntity;
	animatedEntity = NULL;
	this->createStatsBar();
}

void Personaje::clearSprites() {
	vector<SpriteAnimado*>::iterator it;
	for (it = sprites.begin(); it != sprites.end(); it++) {
		delete *it;
	}
	sprites.clear();
}

void Personaje::addNextSprite(AnimatedEntity* entity) {
	SpriteAnimado* newSprite = new SpriteAnimado(entity);
	sprites.push_back(newSprite);
}

void Personaje::addFirstSprite(AnimatedEntity* entity) {
	SpriteAnimado* newSprite = new SpriteAnimado(entity);
	sprites.push_back(newSprite);
	this->setRectangle(modelo->getPosition(), newSprite);
}

bool Personaje::isCenteredInTile() {
	return centeredInTile;
}

void Personaje::setCenteredInTile(bool centroTile) {
	centeredInTile = centroTile;
}

void Personaje::detenerAnimacion() {
	modelo->terminarAnimacion();
	int currentAnimationNumber = modelo->getEstado();
	this->setCurrentSpritePosition(this->calculateSpritePosition(currentAnimationNumber));
}

void Personaje::animar() {
	if (!this->modelo->estaAnimandose())
		return;
	int currentAnimationNumber = modelo->getEstado();
	if (this->calculateSpritePosition(currentAnimationNumber) != this->getCurrentSpritePosition()) {
		if (this->getCurrentSpritePosition() > static_cast<int>(sprites.size()-1)) {
			GameView::instance().getErrorImage()->restart();
		} else {
			sprites[this->getCurrentSpritePosition()]->restart();
		}
		if (this->calculateSpritePosition(currentAnimationNumber) > static_cast<int>(sprites.size()-1)) {
			GameView::instance().getErrorImage()->restart();
		} else {
			sprites[this->calculateSpritePosition(currentAnimationNumber)]->restart();
		}
	}
	this->setCurrentSpritePosition(this->calculateSpritePosition(currentAnimationNumber));
	if (!this->hasValidSprite()) {
		if (GameView::instance().getErrorImage()->lastFrame())
			this->detenerAnimacion();
	} else {
		if (sprites[this->getCurrentSpritePosition()]->lastFrame())
			this->detenerAnimacion();
	}
}

void Personaje::update() {

	if (this->isCenteredInTile()) {
		this->personajeModelo()->getVision()->updatePosition(modelo->getPosition());
	}
	modelo->update();
	this->updateStatsBar();
	//sprites[this->getCurrentSpritePosition()]->actualizarFrame();
}

void Personaje::calcularSigTileAMover(){
	int currentAnimationNumber = 0;
	std::pair<int, int> tile;
	int previousSpritePosition = this->getCurrentSpritePosition();

	if (this->isCenteredInTile()) {
		serr = 0;
		tileActual = modelo->getPosition();
		currentAnimationNumber = modelo->mover(tile, velocidad);
		this->setCurrentSpritePosition(this->calculateSpritePosition(currentAnimationNumber));
		if (previousSpritePosition != this->getCurrentSpritePosition()) {
			ePot.first = 0;
			ePot.second = 0;
		} 
		//std::string aux = stringUtilities::floatToString(velocidad);
		//common::Logger::instance().log("Velocidad: "+ aux);
		if (velocidad != 0) {
			//modelo->setIsInCenterTile(false);
			modelo->setCurrent(tile.first, tile.second);
		}
	}
}

//void Personaje::moverSprite(std::pair<float, float>& factor){
//	
//	if (delta.first != 0) { //Hay movimieto en x
//		ePot.first = ePot.first + factor.first;	//Aumento la cantidad de movimiento, cuantos pixels se va a mover
//		moverSpriteEnX(); //Mueve en x
//	}
//	if (delta.second != 0) { //Si hay movimiento en y, y no esta activada la correcci�n en diagonal
//		ePot.second = ePot.second + factor.second;									//O si esta activada la correcci�n pero se completo el movimineto en x
//		moverSpriteEnY();															//Caso en que la velocidad no es entera
//	}
//}
//
//void Personaje::moverSpriteEnX() {
//	float factorT = 0;	//El truncamiento de la variable factor
//	if (ePot.first >= 1) {	//Si la cantidad de movimiento es mayor a un pixel o mas
//		if (delta.second != 0) { //Si tambi�n hay movimiento en y seteo el control del movimiento diagonal
//			serr++;
//		}
//		//TODO: mejorar el codigo repetido:, notar que dice: if(negativo) sumar else restar..
//		factorT = std::floor(ePot.first);	//Trunco para obtener una cantidad entera
//		ePot.first -= factorT;	//Saco la cantidad entera de la cantidad de movimiento
//		if (delta.first < 0) {	//Si me muevo hacia las x negativas
//			delta.first += factorT;
//			if (delta.first > 0) {	//Si me paso, por los decimales
//				spriteRect.x -= (Sint16) (factorT - delta.first); //Muevo el sprite en x
//				ePot.first += delta.first;
//				delta.first = 0;	//Termino el movimietno en x
//			} else {				//Mientras siga pudiendo moverse
//				spriteRect.x -= (Sint16) factorT;
//			}
//		} else {
//			delta.first -= factorT;
//			if (delta.first < 0) {
//				spriteRect.x += (Sint16)(factorT + delta.first);
//				ePot.first -= delta.first;
//				delta.first = 0;
//			} else {
//				spriteRect.x += (Sint16)factorT;
//			}
//		}
//	}
//}

//void Personaje::moverSpriteEnY() {
//	float factorT = 0;	//El truncamiento de la variable factor
//	//TODO: mejorar el codigo repetido:, notar que dice: if(negativo) sumar else restar..
//	if (((ePot.second >= 1)/*&&(serr != 1))||((serr == 1)&&(delta.first == 0)&&(ePot.second >= 1)*/)) {
//		serr = 0;
//		factorT = std::floor(ePot.second);
//		ePot.second -= factorT;
//		if (delta.second < 0) {
//			delta.second += factorT;
//			if (delta.second > 0) {
//				spriteRect.y -= (Sint16)(factorT - delta.second);
//				ePot.second += delta.second;
//				delta.second = 0;
//			} else {
//				spriteRect.y -= (Sint16)factorT;
//			}
//		} else {
//			delta.second -= factorT;
//			if (delta.second < 0) {
//				spriteRect.y += (Sint16)(factorT + delta.second);
//				ePot.second -= delta.second;
//				delta.second = 0;
//			} else {
//				spriteRect.y += (Sint16)factorT;
//			}
//		}
//	}
//}

void Personaje::renderStatsBars(Camera& camera) {
	SDL_Rect gLifeBarBox;
	SDL_Rect rLifeBarBox;

	SDL_Rect pMagicBarBox;
	SDL_Rect nMagicBarBox;

	pMagicBarBox.w = static_cast<Sint16>(magicBarPos->w); pMagicBarBox.h = static_cast<Sint16>(magicBarPos->h);
	nMagicBarBox.w = static_cast<Sint16>(magicBarNeg->w); nMagicBarBox.h = static_cast<Sint16>(magicBarNeg->h);

	gLifeBarBox.w = static_cast<Sint16>(lifeBarG->w); gLifeBarBox.h = static_cast<Sint16>(lifeBarG->h);
	rLifeBarBox.w = static_cast<Sint16>(lifeBarR->w); rLifeBarBox.h = static_cast<Sint16>(lifeBarR->h);

	SDL_FillRect(lifeBarR, NULL, SDL_MapRGB (lifeBarR->format, 255, 0, 0));
	SDL_FillRect(lifeBarG, NULL, SDL_MapRGB (lifeBarG->format, 0, 128, 0));

	SDL_FillRect(magicBarNeg, NULL, SDL_MapRGB (magicBarNeg->format, 149, 149, 255));
	SDL_FillRect(magicBarPos, NULL, SDL_MapRGB (magicBarPos->format, 0, 0, 255));

	gLifeBarBox.x = static_cast<Sint16>(spriteRect.x + (0.125*spriteRect.w)); gLifeBarBox.y = static_cast<Sint16>(spriteRect.y + spriteRect.h - BAR_HEIGHT);
	rLifeBarBox.x = gLifeBarBox.x; rLifeBarBox.y = gLifeBarBox.y;

	pMagicBarBox.x = static_cast<Sint16>(spriteRect.x + (0.125*spriteRect.w)); pMagicBarBox.y = static_cast<Sint16>(spriteRect.y + spriteRect.h - 2*BAR_HEIGHT);
	nMagicBarBox.x = pMagicBarBox.x; nMagicBarBox.y = pMagicBarBox.y;

	camera.render(rLifeBarBox, lifeBarR);
	camera.render(gLifeBarBox, lifeBarG);

	camera.render(nMagicBarBox, magicBarNeg);
	camera.render(pMagicBarBox, magicBarPos);
}

void Personaje::render(Camera& camera) {
	SDL_Rect cuadroMensaje;

	cuadroMensaje.x = static_cast<Sint16>((2*spriteRect.x + spriteRect.w - this->labelName->w)/2);
	cuadroMensaje.y = spriteRect.y;
	if (this->isImmobilized()) {
		if (this->isFogged()) {
			if (!this->hasValidSprite()) {
				camera.render(spriteRect,GameView::instance().getErrorImage()->getSurfaceAt(freezedSpriteState)->getBlackShadow());
			} else {
				camera.render(spriteRect,sprites[this->getCurrentSpritePosition()]->getSurfaceAt(freezedSpriteState)->getBlackShadow());
			}
		} else {
			if (!this->hasValidSprite()) {
				camera.render(spriteRect,GameView::instance().getErrorImage()->getSurfaceAt(freezedSpriteState)->getWhiteShadow());
			} else {
				camera.render(spriteRect,sprites[this->getCurrentSpritePosition()]->getSurfaceAt(freezedSpriteState)->getWhiteShadow());
			}
		}
	}
	if (!this->hasValidSprite()) {
		camera.render(this->spriteRect, GameView::instance().getErrorImage()->getSurfaceAt(freezedSpriteState)->getSurfaceToShow(this->isFogged()));
	} else {
		camera.render(this->spriteRect, sprites[this->getCurrentSpritePosition()]->getSurfaceAt(freezedSpriteState)->getSurfaceToShow(this->isFogged()));
	}
	SDL_SetClipRect(this->labelName, (&cuadroMensaje));
	camera.render(cuadroMensaje, this->labelName);
	this->renderStatsBars(camera);
}

int Personaje::calculateSpritePosition(int currentAnimationNumber) {
	if ((currentAnimationNumber < MOVIMIENTO)||(currentAnimationNumber >= (MOVIMIENTO + FACTOR_ORIENTACION))) {
		delta.first = 0;
		delta.second = 0;
	}
	switch (currentAnimationNumber) {
	case PARADO_N: return STOP_N;
	case PARADO_NE: return STOP_NE;
	case PARADO_NOE: return STOP_NOE;
	case PARADO_S: return STOP_S;
	case PARADO_SE: return STOP_SE;
	case PARADO_SOE: return STOP_SOE;
	case PARADO_E: return STOP_E;
	case PARADO_O: return STOP_O;
	case CAMINANDO_N: { 
		delta.first = 0;
		delta.second = -32;
		return WALK_N;
					  }
	case CAMINANDO_NE: {
		delta.first = 32;
		delta.second = -16;
		return WALK_NE;
					   }
	case CAMINANDO_NOE: {
		delta.first = -32;
		delta.second = -16;
		return WALK_NOE;
						}
	case CAMINANDO_S: {
		delta.first = 0;
		delta.second = 32;
		return WALK_S;
					  }
	case CAMINANDO_SE: {
		delta.first = 32;
		delta.second = 16;
		return WALK_SE;
					   }
	case CAMINANDO_SOE: {
		delta.first = -32;
		delta.second = 16;
		return WALK_SOE;
						}
	case CAMINANDO_O: {
		delta.first = -64;
		delta.second = 0;
		return WALK_O;
					  }
	case CAMINANDO_E: {
		delta.first = 64;
		delta.second = 0;
		return WALK_E;
					  }
	case FREEZAR_N: return FREEZE_N;
	case FREEZAR_NE: return FREEZE_NE;
	case FREEZAR_NOE: return FREEZE_NOE;
	case FREEZAR_S: return FREEZE_S;
	case FREEZAR_SE: return FREEZE_SE;
	case FREEZAR_SOE: return FREEZE_SOE;
	case FREEZAR_E: return FREEZE_E;
	case FREEZAR_O: return FREEZE_O;
	case ATACAR_N: return ATTACK_N;
	case ATACAR_NE: return ATTACK_NE;
	case ATACAR_NOE: return ATTACK_NOE;
	case ATACAR_S: return ATTACK_S;
	case ATACAR_SE: return ATTACK_SE;
	case ATACAR_SOE: return ATTACK_SOE;
	case ATACAR_E: return ATTACK_E;
	case ATACAR_O: return ATTACK_O;
	case DEFENDER_N: return DEFEND_N;
	case DEFENDER_NE: return DEFEND_NE;
	case DEFENDER_NOE: return DEFEND_NOE;
	case DEFENDER_S: return DEFEND_S;
	case DEFENDER_SE: return DEFEND_SE;
	case DEFENDER_SOE: return DEFEND_SOE;
	case DEFENDER_E: return DEFEND_E;
	case DEFENDER_O: return DEFEND_O;
	default: return ESTADO_ERROR;
	}
}

Personaje::~Personaje(){
	if (this->sprites.size() > 0) {
		this->clearSprites();
	}
	SDL_FreeSurface(this->labelName);
	SDL_FreeSurface(this->lifeBarG);
	SDL_FreeSurface(this->lifeBarR);
	SDL_FreeSurface(this->magicBarNeg);
	SDL_FreeSurface(this->magicBarPos);
}

PersonajeModelo* Personaje::personajeModelo() {
	return modelo;
}

std::pair<int,int> Personaje::getPosicionEnTiles() {
	return modelo->getPosition();
}

std::pair<int,int> Personaje::getPosicionAnteriorEnTiles() {
	return tileActual;
}

//tilex, tiley; pixelx, pixely; isFreezed; nro_status; nro_surface
std::string Personaje::updateToString() {

	std::string out = stringUtilities::pairIntToString(modelo->getPosition());
	out.append(";");
	out.append(stringUtilities::pairIntToString(this->getPixelPosition()));
	out.append(";");
	if (this->isFogged()) {
		out.append("F");
	} else {
		out.append("N");
	}
	out.append(";");
	out.append(stringUtilities::intToString(this->getCurrentSpritePosition()));
	out.append(";");
	if (this->hasValidSprite()) {
		out.append(stringUtilities::intToString(sprites[this->getCurrentSpritePosition()]->getCurrentSurfaceNumber()));
	} else {
		// en caso de problemas con el sprite mando un 0
		out.append(stringUtilities::intToString(0));
	}
	out.append(";");
	if (this->isCenteredInTile()) {
		out.append("T");
	} else {
		out.append("F");
	}
	out.append(";");
	out.append(this->modelo->getVision()->updateToString());
	return out;
}

//tilex, tiley; pixelx, pixely; isFreezed; nro_status; nro_surface
void Personaje::updateFromString(std::string data) {
	vector <std::string> splittedData;
	stringUtilities::splitString(data, splittedData, ';');
	std::pair<int,int> tilePosition = stringUtilities::stringToPairInt(splittedData[0]);
	this->tileActual = tilePosition;
	this->modelo->setPosition(tilePosition);
	this->modelo->getVision()->updatePosition(modelo->getPosition());
	std::pair<int,int> pixels = stringUtilities::stringToPairInt(splittedData[1]);
	this->setPixelPosition(pixels);
	this->setFogged(splittedData[2] == "F");
	this->setCurrentSpritePosition(stringUtilities::stringToInt(splittedData[3]));
	if (this->hasValidSprite()) {
		this->sprites[this->getCurrentSpritePosition()]->setCurrentSurfaceNumber(stringUtilities::stringToInt(splittedData[4]));
	}
	//else {
	//	//TODO: Fer: esta linea que sigue esta mal.. corregir urgente
	//	GameView::instance().getErrorImage()->setCurrentSurfaceNumber(stringUtilities::stringToInt(splittedData[4]));
	//}
	this->setCenteredInTile(splittedData[5] == "T");
	this->vidaActual = stringUtilities::stringToFloat(splittedData[6]);
	this->magiaActual = stringUtilities::stringToFloat(splittedData[7]);
	this->modelo->getVision()->updateFromString(splittedData[8]);
	//common::Logger::instance().log("simulation posicion:"+splittedData[1]+" posicionTile:"+splittedData[0]+" SpritePosition:"+splittedData[3]);
	this->update();
	this->setActive(true);
	GameView::instance().getWorldView()->getTileAt(std::make_pair<unsigned,unsigned>(2,2))->getOtherEntity()->iceUp(20);
}

int Personaje::getCurrentSpritePosition() {
	return this->currentSpritePosition;
}

void Personaje::setCurrentSpritePosition(int pos) {
	this->currentSpritePosition = pos;
}

std::pair<int,int> Personaje::getPixelPosition() {
	return std::make_pair<int,int>(spriteRect.x, spriteRect.y);
}

void Personaje::setPixelPosition(std::pair<int,int> pixel) {
	spriteRect.x = static_cast<Sint16>(pixel.first);
	spriteRect.y = static_cast<Sint16>(pixel.second);
}

//tilex,tiley;pixelx,pixely;isFreezed;nro_status;nro_surface~datos_vision
std::string Personaje::initToString() {
	std::string out = this->updateToString();
	out.append("~");
	out.append(this->modelo->getVision()->initToString());
	return out;
}

//tilex,tiley;pixelx,pixely;isFreezed;nro_status;nro_surface~datos_vision
void Personaje::initFromString(std::string data) {
	//Logger::instance().log(data);
	vector <std::string> splittedData;
	stringUtilities::splitString(data, splittedData, '~');
	this->updateFromString(splittedData[0]);
	this->modelo->getVision()->initFromString(splittedData[1]);
}

void Personaje::setPlayerName(std::string name) {
	this->playerName = name;
	if (!(this->getPlayerName().empty())) {
		this->createLabelName();
	}
}

std::string Personaje::getPlayerName() {
	return this->playerName;
}

std::string Personaje::idToString() {
	std::string out = this->getPlayerName();
	out.append(";");
	out.append(modelo->getName());
	return out;
}

void Personaje::setActive(bool value) {
	this->active = value;
}

bool Personaje::isActive() {
	return this->active;
}

void Personaje::setFont(TTF_Font* font) {
	this->font = font;
}

bool Personaje::hasValidSprite() {
	return ((this->getCurrentSpritePosition() <= static_cast<int>(sprites.size()-1))&&(this->getCurrentSpritePosition() >= 0));
}
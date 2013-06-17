#include "Personaje.h"
#include "../Model/PersonajeConstantes.h"
#include "SDL_ttf.h"
#include "Logger.h"
#include "StringUtilities.h"
#include "Sword.h"
#include "Bow.h"

#include "Game.h"
#include "GameView.h"

#define BAR_HEIGHT 4

Personaje::Personaje(PersonajeModelo* pj,std::string char_id) {
	this->font = NULL;
	modelo = pj;
	this->character_id=char_id;
	this->setPosition(pj->getPosition());
	this->setCurrentSpritePosition(this->calculateSpritePosition(pj->getEstado()));
	velocidad = pj->getVelocidad();
	delta.first = 0;
	delta.second = 0;
	ePot.first = 0;
	ePot.second = 0;
	serr = 0;
	currentEnemy = NULL;
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
	this->shieldResistance = 0;
	this->shieldAbsortion=0;
	this->setFogged(false);
	this->setCenteredInTile(true);
	this->setActive(false);
	this->resetSpriteState();

	//Loading relationship between animations and sounds.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Looking north
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Looking north-east.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Looking north-west.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Looking south.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Looking south-east.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Looking south-west.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Looking east.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Looking west.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Walking north
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Walking north-east.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Walking north-west.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Walking south.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Walking south-east.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Walking south-west.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Walking east.
	this->getAnimationFxRelation().push_back(SOUND_INDEX_NO_SOUND); // Walking west.
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

bool Personaje::isCenteredInTileInSinglePlayer() {
	centeredInTile = ((delta.first == 0) && (delta.second == 0));
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
	if (!this->modelo->estaAnimandose() || this->isImmobilized())
		return;
	int currentAnimationNumber = modelo->getEstado();
	if (this->calculateSpritePosition(currentAnimationNumber) != this->getCurrentSpritePosition()) {
		if (!this->hasValidSprite()) {
			GameView::instance().getErrorImage()->restart();
		} else {
			sprites[this->getCurrentSpritePosition()]->restart();
		}
		if (!this->hasValidSprite()) {
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
	common::Logger::instance().log("Character pos: " + this->positionToString());
	modelo->update();
	this->updateStatsBar();
	//if ((int)(this->sprites.size()-1) >= (this->getCurrentSpritePosition())) {
	if (this->hasValidSprite()) {
		if (this->sprites[this->getCurrentSpritePosition()]->getCurrentSurfaceNumber() == 0)/* && GameView::instance().getMyPersonaje()->personajeModelo()->getVision()->isInsideVision(this->getPosition()))*/ {
			GameView::instance().getGameSounds().playSoundEffect(this->getAnimationFxRelation()[this->getCurrentSpritePosition()]);
		}
	}
}

void Personaje::updateSinglePlayer() {
	this->isCenteredInTileInSinglePlayer();
	this->setFogged(!modelo->isActive());
	this->mover();
	if (this->isCenteredInTile()) {
		this->animar();
		this->personajeModelo()->getVision()->updatePosition(modelo->getPosition());
	}
	modelo->update();
	if (this->isImmobilized())
		return;
	if (this->getCurrentSpritePosition() > static_cast<int>(sprites.size()-1)) {
		GameView::instance().getErrorImage()->updateFrame();
	} else {
		sprites[this->currentSpritePosition]->updateFrame();
	}
	if ((int)(this->sprites.size()-1) >= ((int)this->getCurrentSpritePosition())) {
		if (this->sprites[this->getCurrentSpritePosition()]->getCurrentSurfaceNumber() == 0)/* && GameView::instance().getMyPersonaje()->personajeModelo()->getVision()->isInsideVision(this->getPosition()))*/ {
			GameView::instance().getGameSounds().playSoundEffect(this->getAnimationFxRelation()[this->getCurrentSpritePosition()]);
		}
	}
	this->updateStatsBar();
}

void Personaje::mover() {
	if (this->isCenteredInTile() && (this->isImmobilized() || this->modelo->estaAnimandose()))
		return;

	std::pair<float, float> factor;	//Cuantos pixels se mueve por ciclo
	factor.first = 0;
	factor.second = 0;
	
	perseguirEnemigo();
	calcularSigTileAMover();
	calcularvelocidadRelativa(factor);
	if (this->getCurrentSpritePosition() != ESTADO_ERROR) {
		moverSprite(factor);
	}
}

void Personaje::calcularSigTileAMover(){
	int currentAnimationNumber = 0;	//animacion del personaje en el sistema de PersonajeModelo
	std::pair<int, int> tile;	//Un tile
	int previousSpritePosition = this->getCurrentSpritePosition();

	if (this->isCenteredInTile()) {
		serr = 0;
		this->setPosition(modelo->getPosition());
		//tileActual = modelo->getPosition();
		//modelo->setIsInCenterTile(true);
		this->eatIfItem(this->getPosition());
		if (this->currentEnemy != NULL) {
			//prepare things to attack
			this->getWeapons()[this->selectedWeapon]->setPosition(this->getPosition());
			this->getWeapons()[this->selectedWeapon]->setDirection(this->modelo->getDirection());
			if (this->getWeapons()[this->selectedWeapon]->readyToStrike(this->currentEnemy->getPosition())) {
				this->modelo->setNoTarget(); 
			} else
				currentAnimationNumber = modelo->mover(tile, velocidad);
		} else {
			currentAnimationNumber = modelo->mover(tile, velocidad);
		}
		if (this->modelo->estaAnimandose())
			return;
		this->setCurrentSpritePosition(this->calculateSpritePosition(currentAnimationNumber));
		if (currentSpritePosition < 0)
			this->currentSpritePosition = 0;
		if (previousSpritePosition != this->currentSpritePosition) {
			ePot.first = 0;
			ePot.second = 0;
		} 
		//std::string aux = stringUtilities::floatToString(velocidad);
		//common::Logger::instance().log("Velocidad: "+ aux);
		if (velocidad != 0) {
			//modelo->setIsInCenterTile(false);
			modelo->setPosition(tile);
		} else {

			this->atacar();
		}
		if (modelo->getIsReseting()) {
			this->setRectangle(this->getPosition(), sprites[this->currentSpritePosition]);
			currentEnemy = NULL;
			this->heal();
			this->rechargeMagic();
			modelo->setIsReseting();
		}
	}
}

void Personaje::moverSprite(std::pair<float, float>& factor){
	
	if (delta.first != 0) { //Hay movimieto en x
		ePot.first = ePot.first + factor.first;	//Aumento la cantidad de movimiento, cuantos pixels se va a mover
		moverSpriteEnX(); //Mueve en x
	}
	if (delta.second != 0) { //Si hay movimiento en y, y no esta activada la corrección en diagonal
		ePot.second = ePot.second + factor.second;									//O si esta activada la corrección pero se completo el movimineto en x
		moverSpriteEnY();															//Caso en que la velocidad no es entera
	}
}

void Personaje::moverSpriteEnX() {
	float factorT = 0;	//El truncamiento de la variable factor
	if (ePot.first >= 1) {	//Si la cantidad de movimiento es mayor a un pixel o mas
		if (delta.second != 0) { //Si también hay movimiento en y seteo el control del movimiento diagonal
			serr++;
		}
		factorT = std::floor(ePot.first);	//Trunco para obtener una cantidad entera
		ePot.first -= factorT;	//Saco la cantidad entera de la cantidad de movimiento
		if (delta.first < 0) {	//Si me muevo hacia las x negativas
			delta.first += factorT;
			if (delta.first > 0) {	//Si me paso, por los decimales
				spriteRect.x -= (Sint16) (factorT - delta.first); //Muevo el sprite en x
				ePot.first += delta.first;
				delta.first = 0;	//Termino el movimietno en x
			} else {				//Mientras siga pudiendo moverse
				spriteRect.x -= (Sint16) factorT;
			}
		} else {
			delta.first -= factorT;
			if (delta.first < 0) {
				spriteRect.x += (Sint16)(factorT + delta.first);
				ePot.first -= delta.first;
				delta.first = 0;
			} else {
				spriteRect.x += (Sint16)factorT;
			}
		}
	}
}

void Personaje::moverSpriteEnY() {
	float factorT = 0;	//El truncamiento de la variable factor
	
	if (((ePot.second >= 1)/*&&(serr != 1))||((serr == 1)&&(delta.first == 0)&&(ePot.second >= 1)*/)) {
		serr = 0;
		factorT = std::floor(ePot.second);
		ePot.second -= factorT;
		if (delta.second < 0) {
			delta.second += factorT;
			if (delta.second > 0) {
				spriteRect.y -= (Sint16)(factorT - delta.second);
				ePot.second += delta.second;
				delta.second = 0;
			} else {
				spriteRect.y -= (Sint16)factorT;
			}
		} else {
			delta.second -= factorT;
			if (delta.second < 0) {
				spriteRect.y += (Sint16)(factorT + delta.second);
				ePot.second -= delta.second;
				delta.second = 0;
			} else {
				spriteRect.y += (Sint16)factorT;
			}
		}
	}
}

void Personaje::manejarDano(float danoRecibido)
{
	if(!this->hasShield())
		vidaActual -= danoRecibido;
	else
	{
		float diference=danoRecibido-this->shieldAbsortion;
		if(diference>=0)
		{
			this->shieldResistance-=this->shieldAbsortion;
			vidaActual -=diference;
		}
		else
		{
		this->shieldResistance-=this->shieldAbsortion-diference;
		}
	}
}

void Personaje::recibirDano(float dano) {
	
	if (this->isFogged()) {
		return;
	}
	float danoRecibido = Game::instance().getRandom() * dano;
	this->manejarDano(danoRecibido);
	//vidaActual -= danoRecibido;
	if (vidaActual > 0) {
		this->modelo->herir();
	} else {
		this->modelo->morir();
		GameView::instance().getWorldView()->relocateItem(this->getPosition());
	}
}
//
//void Personaje::resolverAtaque() {
//	float precision = Game::instance().getRandom();
//	if (precision >= this->modelo->getPrecisionMinima()) {
//		this->currentEnemy->recibirDano(this->modelo->getDanoMaximo());
//		//YAMI if (!(this->currentEnemy->isAlive())) {
//		//YAMI GameView::instance().getMission()->missionUpdate(currentEnemy, this->getPlayerName());
//		//}
//	}
//}

void Personaje::atacar() {
	if (currentEnemy != NULL) {
		//this->getWeapons()[this->selectedWeapon]->setPosition(this->getPosition());
		//this->getWeapons()[this->selectedWeapon]->setDirection(this->modelo->getDirection());
		if (!this->getWeapons()[this->selectedWeapon]->sameDirection(currentEnemy->getPosition()))
			return;
		if (!this->getWeapons()[this->selectedWeapon]->isInsideRange(currentEnemy->getPosition()))
			return;
		switch (this->selectedWeapon) {
			case WEAPON_SWORD: {
			//ataque con espada
				//if ((currentEnemy->getPosition() == this->modelo->obtenerFrentePersonaje())) {
					//this->resolverAtaque();
					this->getWeapons()[this->selectedWeapon]->strike(currentEnemy);
					this->modelo->atacar();
					currentEnemy = NULL;
				//}
				break;
			}
			case WEAPON_BOW: {
				//ataque con arco y flecha
				break;
			}
		}
	}
}

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

	pMagicBarBox.x = static_cast<Sint16>(spriteRect.x + (0.125*spriteRect.w)); pMagicBarBox.y = static_cast<Sint16>(spriteRect.y + spriteRect.h - 2*BAR_HEIGHT - 1);
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

void Personaje::setDestino(int xTile, int yTile){
	modelo->setDestino(xTile, yTile);
	setCurrentEnemy(xTile, yTile);
}

void Personaje::setCurrentEnemy(int tileX, int tileY) {
	std::pair<int, int> tileDestino(tileX, tileY);

	if (modelo->isThereAnEnemy(tileX, tileY)) {
		currentEnemy = GameView::instance().getDaniableInTile(tileDestino);
		if (currentEnemy == this) {
			currentEnemy = NULL;
		}
	}
}

void Personaje::perseguirEnemigo() {
	
	if (currentEnemy == NULL) {
		this->modelo->setFollowingEnemy(false);
		return;
	}
	if ((currentEnemy->getPosition() != modelo->getTarget()) && (modelo->canSee(currentEnemy->getPosition()))) {
		setDestino(currentEnemy->getPosition().first, currentEnemy->getPosition().second);
		this->modelo->setFollowingEnemy(true);
		return;
	}
	if (!modelo->canSee(currentEnemy->getPosition())) {
		currentEnemy = NULL;
	}
	this->modelo->setFollowingEnemy(false);
}

void Personaje::animateModel(char animacion) {
	modelo->animar(animacion);
}

void Personaje::calcularvelocidadRelativa(std::pair<float, float>& factor) {
	float deltaTime = this->getDeltaTime()*100;
	if (delta.first != 0) { //Hay movimiento en x
		if (delta.second != 0) { //Diagonal
			factor.first = static_cast<float>((velocidad*deltaTime) *0.707);
			factor.second = static_cast<float>((velocidad*deltaTime) *0.707/2);
		} else { //Horizontal
			factor.first = (velocidad*deltaTime);
		}
	} else { //No hay movimiento en x
		if (delta.second != 0){ //Vertical
			factor.second = ((velocidad*deltaTime)/2);
		} else {//Quieto
			factor.first = 0;
			factor.second = 0;
		}

	}
}

int Personaje::calculateSpritePosition(int currentAnimationNumber) {
	int orientacion = modelo->getOrientacion();
	
	if ((currentAnimationNumber != MOVIMIENTO)) {
		delta.first = 0;
		delta.second = 0;
		if ((orientacion < 0)||(orientacion > 7)) {
			return ESTADO_ERROR;
		}
	} else {
		switch (orientacion) {
		case NORTE: {
			delta.first = 0;
			delta.second = -32;
			break;
					}
		case NORESTE: {
			delta.first = 32;
			delta.second = -16;
			break;
					  }
		case NOROESTE: {
			delta.first = -32;
			delta.second = -16;
			break;
						}
		case SUR: {
			delta.first = 0;
			delta.second = 32;
			break;
					}
		case SUDESTE: {
			delta.first = 32;
			delta.second = 16;
			break;
						}
		case SUDOESTE: {
			delta.first = -32;
			delta.second = 16;
			break;
						}
		case OESTE: {
			delta.first = -64;
			delta.second = 0;
			break;
					}
		case ESTE: {
			delta.first = 64;
			delta.second = 0;
			break;
					}
		default: return ESTADO_ERROR;
		}
	}
	return ((currentAnimationNumber - 1)*8 + orientacion);
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
	//Destroying weapons
	for (unsigned int i = 0; i < this->getWeapons().size(); i++) {
		delete this->getWeapons()[i];
	}
}

PersonajeModelo* Personaje::personajeModelo() {
	return modelo;
}

std::pair<int,int> Personaje::getPosicionEnTiles(){
	return modelo->getPosition();
}

std::pair<int,int> Personaje::getPosicionActualEnTiles(){
	float deltaAbsX = std::abs(delta.first);
	float deltaAbsY = std::abs(delta.second);

	if ((deltaAbsX <= 32) && (deltaAbsY == 0)) {
		return modelo->getPosition();
	}
	if ((deltaAbsX == 0) && (deltaAbsY <= 16)) {
		return modelo->getPosition();
	}
	if ((deltaAbsX <= 16) && (deltaAbsY <= 8)) {
		return modelo->getPosition();
	}
	return this->getPosition();
}

//tilex, tiley; pixelx, pixely; isFreezed; nro_status; nro_surface
std::string Personaje::updateToString() {

	std::string out = modelo->positionToString();
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
	//std::pair<int,int> tilePosition = stringUtilities::stringToPairInt(splittedData[0]);
	//this->tileActual = tilePosition;
	this->setPosition(this->modelo->getPosition());
	this->modelo->positionFromString(splittedData[0]);
	this->modelo->getVision()->updatePosition(modelo->getPosition());
	std::pair<int,int> pixels = stringUtilities::stringToPairInt(splittedData[1]);
	//common::Logger::instance().log("Character pix: " + splittedData[1]);
	this->setPixelPosition(pixels);
	this->setFogged(splittedData[2] == "F");
	this->setCurrentSpritePosition(stringUtilities::stringToInt(splittedData[3]));
	if (this->hasValidSprite()) {
		this->sprites[this->getCurrentSpritePosition()]->setCurrentSurfaceNumber(stringUtilities::stringToInt(splittedData[4]));
	}
	this->setCenteredInTile(splittedData[5] == "T");
	this->vidaActual = stringUtilities::stringToFloat(splittedData[6]);
	this->magiaActual = stringUtilities::stringToFloat(splittedData[7]);
	this->shieldResistance = stringUtilities::stringToFloat(splittedData[8]);
	this->modelo->getVision()->updateFromString(splittedData[9]);
	//common::Logger::instance().log("simulation posicion:"+splittedData[1]+" posicionTile:"+splittedData[0]+" SpritePosition:"+splittedData[3]);
	this->update();
	this->setActive(true);
	//GameView::instance().getWorldView()->getTileAt(std::make_pair<unsigned,unsigned>(2,2))->getOtherEntity()->iceUp(20);
}

int Personaje::getCurrentSpritePosition() {
	return this->currentSpritePosition;
}

void Personaje::setCurrentSpritePosition(int pos) {
	if (pos == ESTADO_ERROR) {
		this->currentSpritePosition = 0;
		return;
	}
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

float Personaje::getShieldResistance(){
	return shieldResistance;
}

std::vector<unsigned int>& Personaje::getAnimationFxRelation() {
	return this->animationFxRelation;
}

void Personaje::increaseSpeed(float factor)
{
	this->modelo->increaseSpeed(factor);
}

void Personaje::heal() {

	vidaActual = modelo->getVidaMaxima();
}

void Personaje::rechargeMagic() {

	magiaActual = modelo->getMagiaMaxima();
}

bool Personaje::isItem()
{
	return false;
}

void Personaje::eatIfItem(std::pair<int, int> destino)
{
	Entity * entity= GameView::instance().getWorldView()->getTileAt(destino)->getOtherEntity();
	if(entity!=NULL)
	{
		if(entity->isItem())
		{
			ItemView* item=(ItemView*)entity;
			if(item->isAlive())
			{
				item->modifyCharacter(this);
				item->kill();
			}
		}
	}
}

void Personaje::setShield(float resistance,float absortion)
{
	this->shieldResistance=resistance;
	this->shieldAbsortion=absortion;
}

bool Personaje::useMagic(float usedMagic) {
	if(magiaActual >= usedMagic) {
		magiaActual -= usedMagic;
		return true;
	}
	return false;
}

bool Personaje::hasShield()
{
	return (this->shieldResistance>0);
}

std::vector<Weapon*>& Personaje::getWeapons() {
	return this->weapons;
}

void Personaje::loadWeapons() {
	//Initializing weapons
	Sword* sword = new Sword();
	sword->setOwner(this->getPlayerName());
	
	sword->initialize(true,1,this->modelo->getDanoMaximo(),this->modelo->getPrecisionMinima());
	this->getWeapons().push_back(sword);

	Bow* bow = new Bow();
	bow->setOwner(this->getPlayerName());
	bow->initialize(true,5,this->modelo->getDanoMaximo(),this->modelo->getPrecisionMinima());
	this->getWeapons().push_back(bow);
	this->selectedWeapon = WEAPON_SWORD; //selectedWeapon es la posicion en el vector de weapons, ver PersonajeConstantes.h
}
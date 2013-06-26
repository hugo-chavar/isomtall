#include "GameView.h"
#include "TileModel.h"
#include "Constants.h"


GameView::GameView() {
	this->personajes.clear();
	this->errorImage = NULL;
	this->setStatus(STATUS_START_SCREEN);
	this->camera.initialize();
	this->menu = NULL;
	this->menu = new GameMenu();
	this->addFontSize(20);
	this->addFontSize(23);
	this->addFontSize(10);
	this->addFontSize(16);
	this->addFontSize(12);
	this->menu->initialize();
	this->winner = "";
	this->needsUpdateFiles = true;
	this->needsConnectToServer = true;
	
}

GameView::~GameView() {
	//Logger::instance().log("GameView::~GameView()");
	//map<string, Personaje*>::iterator it;
	//it = personajes.begin();
	//for( ;it != personajes.end(); it++) {
	//	if ((*it).second)
	//		delete (*it).second;
	//}
	if (errorImage != NULL) {
		delete errorImage;
	}

	if (this->menu)
		delete this->menu;
}

void GameView::initialize() {
	this->camera.configure();
	bool mapInitialized = false;
	bool chatInitialized = false;
	this->chat.setBigFont(this->getFontSize(16));
	this->chat.setSmallFont(this->getFontSize(10));
	mapInitialized = worldView.initialize();
	this->characterFactory.initialize();
	chatInitialized = chat.initialize(camera);
	worldView.setTilesInCamera(this->camera.getWidth(), this->camera.getHeight());
	this->personaje = this->characterFactory.createViewCharacter(this->getPlayerCharacterId(), this->getPlayerName());
	this->addPersonaje(this->getPlayerName(), this->personaje);
	if (!mapInitialized)
		this->setStatus(STATUS_INIT_ERROR);


	if (mapInitialized) {
		this->camera.setCenterPixel(this->personaje->getRealPixelPosition());
		//this->camera.setCenterPixel(this->personaje->getPixelPosition());
		AnimatedEntity errorEntity;
		errorEntity.loadImages(ERROR_ANIMATED_DIR);
		errorEntity.delay(0);
		this->errorImage = new SpriteAnimado(&errorEntity);
		statTable.initialize();
		statTable.setFont(this->getFontSize(12));
	}
	
	if (this->isSinglePlayer)
		mission.initialize();

	this->menu->setNotificationFont(this->getFontSize(20));
	this->menu->setNotificationMessage("UPDATING FILES..");
	this->menu->setNotificationFontColor(Camera::RED_COLOR);
	this->menu->setNotificationMessage("SERVER CONNECTION LOST");
	this->menu->setNotificationMessage("ERROR LOADING CLIENT");
	this->menu->setNotificationMessage("SERVER UNREACHABLE");
	this->menu->setNotificationMessage("UPDATED FAILED CONNECTION LOST");
	this->menu->setNotificationMessage("USER NAME UNAVAILABLE");
	this->menu->setNotificationMessage("CONNECTION LOGIN FAILED");
	


	this->getGameSounds().initialize();
	this->getGameSounds().startBackgroundMusic();
}

void GameView::restart() {
	this->camera.configure();
	bool mapInitialized = false;

	this->chat.setIsTyping(false);
	mapInitialized = worldView.initialize();

	if (this->isSinglePlayer) {	
		map<string, Personaje*>::iterator it;
		it = personajes.find(this->getPlayerName());
		personajes.erase(it);
		this->characterFactory.remove(this->personaje);
		//delete (this->personaje);
		Game::instance().world()->loadNamedChars();
		this->personaje = characterFactory.createViewCharacter(this->getPlayerCharacterId(), this->getPlayerName());
		this->addPersonaje(this->getPlayerName(), this->personaje);
		this->personaje->setActive(true);
		mission.initialize();
	}

	if (mapInitialized) {
		this->camera.setCenterPixel(this->personaje->getRealPixelPosition());
		//statTable.initialize();
		//statTable.setFont(this->getFontSize(12));
	}

	//this->getGameSounds().startBackgroundMusic();
}

GameView& GameView::instance() {
	static GameView singleton;
	return singleton;
}

view::Stage* GameView::getWorldView() {
	return &worldView;
}

Mission* GameView::getMission() {
	return &mission;
}

Camera* GameView::getCamera() {
	return &camera;
}

view::ChatView* GameView::getChat() {
	return &chat;
}

Personaje* GameView::getPersonaje(string name) {
	Personaje* personaje = NULL;
	map<string, Personaje*>::iterator it;
	it = this->personajes.find(name);

	if (it != this->personajes.end())
		personaje = it->second;

	return personaje;
}

void GameView::newPersonaje(string name, string char_id) {
	Personaje* personaje = characterFactory.createViewCharacter(char_id, name);
	this->addPersonaje(name, personaje);
}

void GameView::addPersonaje(string name,Personaje * personaje) {
	this->personajes.insert(std::make_pair<string,Personaje *>(name,personaje));
	this->setCharacterVision(personaje->personajeModelo()->getVision());
}

Personaje* GameView::getMyPersonaje() {
	if (this->personaje) {
		return this->personaje;
	}
	//Logger::instance().nullPointer("function Personaje* GameView::getMyPersonaje");
	return NULL;
}

void GameView::setPlayerName(string name) {
	this->playerName = name;
}

string GameView::getPlayerName() {
	return this->playerName;
}

void GameView::setPlayerCharacterId(string char_id) {
	playerCharacterId = char_id;
}

string GameView::getPlayerCharacterId() {
	return this->playerCharacterId;
}

void GameView::cleanUp() {

	this->_login.cleanUp();


	if (this->getModelUpdater()->isConnected()) {
		Instruction instructionOut;
		instructionOut.setOpCode(OPCODE_DISCONNECT_FROM_SIMULATION);
		this->getModelUpdater()->addInstruction(instructionOut);
		this->getModelUpdater()->stopUpdating(false);
	}
	this->camera.cleanUp();
	if (this->chat.isInitialized())
		this->chat.modelChat->cleanUp();

	while (!this->fonts.empty())
	{
		TTF_CloseFont(this->fonts.begin()->second);
		this->fonts.erase(this->fonts.begin());
	}

	this->getGameSounds().cleanUp();
}

void GameView::render() {

	SDL_FillRect(this->camera.cameraSurface, NULL, 0);
	
	switch (this->getStatus()) {
		case STATUS_SIMULATION_CONNECTED: {
			this->worldView.render(this->camera);
			this->statTable.update(this->getMyPersonaje());
			this->statTable.render(this->camera);
			if (chat.isTyping())
				this->chat.render(this->camera);
			break;
		}
		case STATUS_SIMULATION_PLAYING_SINGLEPLAYER:
			{
			this->worldView.render(this->camera);
			this->statTable.update(this->getMyPersonaje());
			this->statTable.render(this->camera);
			}
			break;
		case STATUS_GAME_OVER: {
			this->worldView.render(this->camera);
			this->statTable.update(this->getMyPersonaje());
			this->statTable.render(this->camera);
			if (chat.isTyping())
				this->chat.render(this->camera);
			this->menu->render(this->camera);
			break;
		}
		default: {
			this->menu->render(this->camera);
		}
	}

	SDL_Flip(this->camera.cameraSurface);

}

SpriteAnimado* GameView::getErrorImage() {
	return errorImage;
}

void GameView::update() {

	this->camera.update();

	switch (this->getStatus()) {
		case STATUS_START_SCREEN: {
			this->camera.unconfigure();
			//
		}
		break;
		case STATUS_EXIT: {
			this->camera.unconfigure();
			Mix_HaltMusic();
		}
		break;
		case STATUS_UPDATING_FILES: {
			if (this->needsUpdateFiles) {
				YAMLParser connectionParser;
				ClientUpdater clientUpdater;
				int serverPortNumber;
				std::string serverIpAddress;
				connectionParser.parse(CONNECTION_DIRECTORY, true);
				serverPortNumber = connectionParser.getConfigPort();
				serverIpAddress = connectionParser.getConfigIp();
				clientUpdater.setServerIp(serverIpAddress);
				clientUpdater.setServerPort(serverPortNumber);
				clientUpdater.updateClient();
				Game::instance().configuration()->serverPort(serverPortNumber);
				Game::instance().configuration()->serverIp(serverIpAddress);
				this->needsUpdateFiles = false;
			} else {
				this->setStatus(STATUS_FILES_UPDATED_OK);
			}
		}
		break;
		case STATUS_FILES_UPDATED_OK: {
			if (this->needsConnectToServer) {
				Instruction instruction;
				instruction.clear();
				instruction.setOpCode(OPCODE_LOGIN_REQUEST);
				instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID,this->getPlayerName());
				instruction.insertArgument( INSTRUCTION_ARGUMENT_KEY_CHARACTER, this->getPlayerCharacterId());
				this->getLogin()->getLoginUpdater().addInstruction(instruction);
				this->_login.initialize();
				this->getModelUpdater()->startUpdating();
				this->isSinglePlayer=false;
				Game::instance().initialize();
				this->initialize();
				this->setStatus(STATUS_LOGIN_REQUESTED);
				this->needsConnectToServer = false;
			} else {
				this->setStatus(STATUS_SIMULATION_CONNECTED);
				this->camera.configure();
				this->camera.setCenterPixel(this->personaje->getRealPixelPosition());
				this->getChat()->setIsTyping(true);
			}
		}
		break;
		case STATUS_INIT_ERROR:
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			this->menu->setNotificationMessage("ERROR LOADING CLIENT");
			this->menu->setDisplayNotification(true);
			
		break;
		case STATUS_SERVER_UNREACHEABLE:
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			this->menu->setNotificationMessage("SERVER UNREACHABLE");
			this->menu->setDisplayNotification(true);
		break;
		case STATUS_READY_TO_UPDATE:
			this->menu->setNotificationFontColor(Camera::GREEN_COLOR);
			this->menu->setDisplayNotification(true);
			this->menu->setNotificationMessage("UPDATING FILES..");
			this->setStatus(STATUS_UPDATING_FILES);
		break;
		case STATUS_SIMULATION_SINGLE_PLAYER:
			{
			this->menu->setDisplayNotification(false);
			this->menu->hideButtons();
			this->isSinglePlayer=true;
			Game::instance().initialize();
			this->initialize();
			this->camera.configure();
			//this->camera.setCenterPixel(this->personaje->getPixelPosition());
			this->camera.setCenterPixel(this->personaje->getRealPixelPosition());
			this->getMyPersonaje()->setActive(true);
			this->setStatus(STATUS_SIMULATION_PLAYING_SINGLEPLAYER);

			//this->camera.unconfigure();
			//this->menu->setNotificationFontColor(Camera::BLUE_COLOR);
			//this->menu->setNotificationMessage("SINGLE PLAYER NOT IMPLEMENTED");
			//this->menu->setDisplayNotification(true);
			}
		break;
		case STATUS_UPDATING_CONNECTION_LOST:
			this->camera.unconfigure();
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			this->menu->setNotificationMessage("UPDATED FAILED CONNECTION LOST");
			this->menu->setDisplayNotification(true);
		break;
		case STATUS_SIMULATION_PLAYING_SINGLEPLAYER:
			this->menu->setDisplayNotification(false);
			//GameView::instance().getGameMenu()->setDisplayBackground(false);
			this->menu->hideButtons();
			this->worldView.updateSinglePlayer();
			this->getMyPersonaje()->updateSinglePlayer();
			if (this->mission.isGameOver()) {
				this->winner = this->playerName;
				this->setStatus(STATUS_GAME_OVER);
			}
		break;
		case STATUS_INITIALIZING:
			this->menu->hideButtons();
			this->menu->setNotificationFontColor(Camera::GREEN_COLOR);
			this->menu->setNotificationMessage("RETRIEVING CURRENT STAGE..");
			this->menu->setDisplayNotification(true);
		break;
		case STATUS_SIMULATION_CONNECTED:
			this->menu->setDisplayNotification(false);
			this->menu->hideButtons();
			this->worldView.update();
			this->updateOthersVision();
			this->chat.update(camera);
		break;
		case STATUS_SIMULATION_CONNECTION_LOST:
			this->camera.unconfigure();
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			this->menu->setNotificationMessage("SERVER CONNECTION LOST");
			this->menu->setDisplayNotification(true);
			Mix_HaltMusic();
		break;
		case STATUS_LOGIN_USER_FAILED:
			this->camera.unconfigure();
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			this->menu->setNotificationMessage("USER NAME UNAVAILABLE");
			this->menu->setDisplayNotification(true);
			this->getGameSounds().stopBackgroundMusic();
		break;
		case STATUS_LOGIN_CONNECTION_LOST:
			this->camera.unconfigure();
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			this->menu->setNotificationMessage("CONNECTION LOGIN FAILED");
			this->menu->setDisplayNotification(true);
			Mix_HaltMusic();
		break;
		case STATUS_SIMULATION_TRY_CONNECT:
			//this->camera.unconfigure();
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			this->menu->setNotificationMessage("IT SEEMS SERVER IS DOWN");
			this->menu->setDisplayNotification(true);

		break;
		case STATUS_SIMULATION_READY_TO_RECONNECT:
			this->camera.configure();
			this->camera.setCenterPixel(this->personaje->getRealPixelPosition());
			this->setStatus(STATUS_SIMULATION_CONNECTED);
		break;
		case STATUS_GAME_OVER:
			//this->camera.unconfigure();
			this->getChat()->setIsTyping(false);
			if (this->winner.compare(this->playerName) == 0) {
				this->menu->setNotificationFontColor(Camera::GREEN_COLOR);
				this->menu->setNotificationMessage("CONGRATULATIONS! YOU WON!");
			}
			else {
				this->menu->setNotificationFontColor(Camera::BLUE_COLOR);
				this->menu->setNotificationMessage("PLAYER "+this->winner+" WON");
			}
			this->menu->hideBackground();
			this->menu->setDisplayNotification(true);
		break;
		case STATUS_RESTART_GAME:
			this->camera.unconfigure();
			this->menu->setNotificationFontColor(Camera::BLUE_COLOR);
			this->menu->setNotificationMessage("WAITING FOR ALL PLAYERS TO CONNECT");
			this->menu->setDisplayNotification(true);
		break;
		default: {
			this->menu->setDisplayNotification(false);
			bool loginOK = (GameView::instance().getStatus() != STATUS_LOGIN_USER_FAILED)&&(GameView::instance().getStatus() != STATUS_LOGIN_CONNECTION_LOST);
			if ( loginOK || (GameView::instance().getStatus() == STATUS_LOGIN_REQUESTED)) {
				Instruction instruction;
				instruction.clear();
				instruction.setOpCode(OPCODE_CONNECT_TO_CHAT);
				instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID, GameView::instance().getPlayerName());
				GameView::instance().getChat()->modelChat->getMessagesList().push_back("Connecting to chat");
				GameView::instance().getChat()->modelChat->getChatUpdater().addInstruction(instruction);

				instruction.clear();
				instruction.setOpCode(OPCODE_CONNECT_TO_SIMULATION);
				instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID, GameView::instance().getPlayerName());
				this->getModelUpdater()->addInstruction(instruction);
				this->setStatus(STATUS_SIMULATION_TRY_CONNECT);
			}
		}
		break;
	}
}

bool GameView::insidePlayerVision(std::pair<int,int> pos) {
	bool inside = this->getMyPersonaje()->personajeModelo()->getVision()->isInsideVision(pos);

	if (!inside) {
		TileModel* relatedTile = this->worldView.getWorldModel()->getTileAt(pos); //->getRelatedTile()
		if (relatedTile)
			relatedTile = relatedTile->getRelatedTile();
		if (relatedTile) {
			while ( (!inside) && (relatedTile != this->getWorldView()->getWorldModel()->getTileAt(pos)) ) {
				pair<int, int> posRelated = relatedTile->getPosition();
				inside = this->getMyPersonaje()->personajeModelo()->getVision()->isInsideVision(posRelated);
				relatedTile = relatedTile->getRelatedTile();
			}
		}
	}
	return inside;
}

bool GameView::isKnownByPlayer(std::pair<int,int> pos) { 
	if (this->getMyPersonaje()->personajeModelo()->getVision()->isAllKnown())
		return true;
	return  this->getMyPersonaje()->personajeModelo()->getVision()->testPosition(pos);
}

void GameView::startRenderingCharacters() { 
	this->itPersonajes = this->personajes.begin();
}

Personaje* GameView::nextCharacter() { 
	Personaje* aux = NULL;
	if (this->itPersonajes != this->personajes.end()) {
		aux = this->itPersonajes->second;
		this->itPersonajes++;
	}
	return aux;
}

bool GameView::isThereAChar(string & name,int x,int y,float cameraX,float cameraY) {
	pair<int,int> tilePos = Game::instance().world()->destination(x,y,cameraX,cameraY);
	if(Game::instance().world()->isInsideWorld(tilePos))
	{
		map <string, Personaje*>::iterator it;
		for(it=this->personajes.begin(); it!=this->personajes.end(); it++)
		{
			pair<int,int> posChar = (*it).second->getPosition();
			if(posChar == tilePos)
			{
				name = (*it).first;
				return true;
			}
		}
	}
	return false;
}

void GameView::setStatus(unsigned status) {
	this->gameStatus = status;
}

unsigned GameView::getStatus() {
	return this->gameStatus;
}

GameMenu* GameView::getGameMenu() {
	return this->menu;
}

void GameView::manageMissionInit(string argument) {
	std::vector <std::string> data;
	stringUtilities::splitString(argument, data, ';');
	if (data[0].compare("flagMission") == 0) {
		std::string name = data[1];
		pair <int,int> position;
		for (unsigned int i=2; i<data.size(); i++) {
			position = stringUtilities::stringToPairInt(data[i]);
			this->worldView.addOtherEntity(position, name);
		}
	}
}

void GameView::manageMissionUpdate(string argument) {
	std::vector <std::string> data;
	stringUtilities::splitString(argument, data,':');
	for (unsigned int i=0; i<data.size(); i++) {
		std::vector <std::string> change;
		stringUtilities::splitString(data[i], change, ';');
		if (change[0].compare("flagMission") == 0) {
			if (change[1].compare("D") == 0) {
				pair <int,int> position = stringUtilities::stringToPairInt(change[3]);
				this->worldView.removeOtherEntity(position);
			}
			if (change[1].compare("A") == 0) {
				pair <int,int> position = stringUtilities::stringToPairInt(change[3]);
				this->worldView.addOtherEntity(position, change[2]);
			}
		} else {
			if (change[0].compare("GameOver") == 0) {
				this->setWinner(change[1]);
				this->setStatus(STATUS_GAME_OVER);
			}
		}
	}
}

void GameView::setWinner(string userID) {
	this->winner = userID;
}

ModelUpdater* GameView::getModelUpdater() {
	return &this->_modelUpdater;
}

model::Login* GameView::getLogin() {
	return &_login;
}

bool GameView::isGameOver() {
	if (this->getStatus() == STATUS_GAME_OVER)
		return true;
	return false;
}

bool GameView::showingMenu() {
	//TODO: adaptar segun se vaya avanzando.. esto esta para modificarse!
	bool start = (GameView::instance().getStatus() == STATUS_START_SCREEN);
	bool unreachable = (GameView::instance().getStatus() == STATUS_SERVER_UNREACHEABLE);
	bool connectionLost = (GameView::instance().getStatus() == STATUS_SIMULATION_CONNECTION_LOST);
	bool singlePlayer = (GameView::instance().getStatus() == STATUS_SIMULATION_SINGLE_PLAYER);
	bool gameOver = (GameView::instance().getStatus() == STATUS_GAME_OVER);
	return (start || unreachable || connectionLost || singlePlayer || gameOver) ;
}

void GameView::addFontSize(int size) {
	TTF_Font* font = TTF_OpenFont(DEFAULT_FONT_PATH, size);
	this->fonts[size] = font;
}

TTF_Font* GameView::getFontSize(int size) {
	return this->fonts.at(size);
}

StatsTable* GameView::getStatsTable() {
	return &(this->statTable);
}

GameSounds& GameView::getGameSounds() {
	return this->gameSounds;
}

bool GameView::isSinglePlayerGame()
{
	return this->isSinglePlayer;
}

Daniable* GameView::getDaniableInTile(std::pair <int, int> tile) {
	
	if(Game::instance().world()->isInsideWorld(tile))
	{
		Daniable* item=GameView::instance().getWorldView()->getItemInTile(tile.first,tile.second);
		if(item)
		{
			return item;
		}
		return mission.manageAttack(tile);
	}
	return NULL;
}

void GameView::updateEvents(string serializedEventsUpdates)
{
	if(serializedEventsUpdates.size()<1)
		return;
	std::vector <string> updateVector;
	stringUtilities::splitString(serializedEventsUpdates,updateVector,':');
	for(unsigned i=0;i<updateVector.size();i++)
	{
		this->updateEvent(updateVector[i]);
	}
}

void GameView::updateEvent(string serializedItemUpdate)
{
	std::vector<string> vector;
	stringUtilities::splitString(serializedItemUpdate,vector,';');
	int evento=stringUtilities::stringToInt(vector[0]);
	switch (evento){
		case EVENT_VIBRATING:
			this->camera.setVibrating();
		break;
		case EVENT_SOUND_ARROW:
			if(GameView::instance().getMyPersonaje()->personajeModelo()->canSee(stringUtilities::stringToPairInt(vector[1])))
				GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_ARROW);
					break;
		case EVENT_SOUND_ATTACK_ON_SHIELD:
			if(GameView::instance().getMyPersonaje()->personajeModelo()->canSee(stringUtilities::stringToPairInt(vector[1])))
				GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_ATTACK_ON_SHIELD);
					break;
		case EVENT_SOUND_ATTACK_ON_WOOD:
			if(GameView::instance().getMyPersonaje()->personajeModelo()->canSee(stringUtilities::stringToPairInt(vector[1])))
				GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_ATTACK_ON_WOOD);
					break;
		case EVENT_SOUND_EAT_ITEM:
			if(GameView::instance().getMyPersonaje()->personajeModelo()->canSee(stringUtilities::stringToPairInt(vector[1])))
				GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_EAT_ITEM);
					break;
		case EVENT_SOUND_REGENERATION:
			if(GameView::instance().getMyPersonaje()->personajeModelo()->canSee(stringUtilities::stringToPairInt(vector[1])))
				GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_REGENERATION);
					break;
		case EVENT_SOUND_EXPLOSION:
			if(GameView::instance().getMyPersonaje()->personajeModelo()->canSee(stringUtilities::stringToPairInt(vector[1])))
				GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_EXPLOSION);
					break;
		case EVENT_SOUND_MAGIC:
			if(GameView::instance().getMyPersonaje()->personajeModelo()->canSee(stringUtilities::stringToPairInt(vector[1])))
				GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_MAGIC);
					break;
		case EVENT_ICESPELL_ITEMIMPACT:
			{
			std::pair<int,int> pos=stringUtilities::stringToPairInt(vector[1]);
			Entity* entity=this->getWorldView()->getTileAt(pos)->getOtherEntity();
			if(entity)
				{
				entity->iceUp();
				if(GameView::instance().getMyPersonaje()->personajeModelo()->canSee(pos))
					GameView::instance().getGameSounds().playSoundEffect(SOUND_INDEX_ICE);
				}
			}
			break;
		case EVENT_STOP_ITEMICEUP:
			{
			std::pair<int,int> pos=stringUtilities::stringToPairInt(vector[1]);
			Entity* entity=this->getWorldView()->getTileAt(pos)->getOtherEntity();
			if(entity)
				entity->notIceUp();
			}
			break;
		case EVENT_AMMUNITION_CHANGE:
			{
				GameView::instance().getWorldView()->manageAmmunitionChange(vector[1]);
				//Agregar logica al recibir evento en una Ammunition
			}
			break;
		case EVENT_AMMUNITION_DEATH:
			{
		
			}
			break;
	}
	/*if(serializedItemUpdate=="vibrar")
	{
		this->camera.setVibrating();
	}*/
	//Agregar logica para otros eventos
}

std::vector<CharacterVision *>* GameView::getCharactersVisions()
{
	return &this->charactersVisions;
}

void GameView::setCharacterVision(CharacterVision * other)
{
	this->charactersVisions.push_back(other);
}

void GameView::updateOthersVision()
{
	itPersonajes=personajes.begin();
	for(itPersonajes;itPersonajes!=personajes.end();itPersonajes++)
		{
			if((*itPersonajes).second!=this->personaje)
				{
				(*itPersonajes).second->personajeModelo()->update();
				}
		}
}

void GameView::deleteCharacterVision(CharacterVision* other)
{
	std::vector<CharacterVision*>::iterator it=this->charactersVisions.begin();
	for(it;it<this->charactersVisions.end();it++)
	{
		if((*it)==other)
		{
			this->charactersVisions.erase(it);
		}
	}
}

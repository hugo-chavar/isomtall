#include "GameView.h"
#include "TileModel.h"
#include "Constants.h"



GameView::GameView() {
	this->errorImage = NULL;
	this->_music = NULL;
	this->setStatus(STATUS_START_SCREEN);
	this->camera.initialize();
	this->menu = NULL;
	this->menu = new GameMenu();
	this->addFontSize(20);
	this->addFontSize(23);
	this->addFontSize(10);
	this->addFontSize(16);
	
	this->menu->initialize(/*this->camera*/);
	this->menu->setNotificationMessage("   SERVER CONNECTION LOST");
	
}

GameView::~GameView() {
	map<string, Personaje*>::iterator it;
	it = personajes.begin();
	for( ;it != personajes.end(); it++) {
		if ((*it).second)
			delete (*it).second;
	}
	if (errorImage != NULL) {
		delete errorImage;
	}

	if (this->menu)
		delete this->menu;
}

void GameView::initialize() {
	this->camera.configure();
	bool mapInitialized = false;
	//bool textInitialized = true;
	bool chatInitialized = false;
	//bool notificationInitialized = false;
	this->serverReached = true;

	this->chat.setIsTyping(false);
	
	this->chat.setBigFont(this->getFontSize(16));
	this->chat.setSmallFont(this->getFontSize(10));

	////Initialize SDL_ttf
	//if (TTF_Init() == -1)
	//	textInitialized = false;

	//this->notification.setImagePath(DEFAULT_NOTIFICATIONBOX_PATH);
	//notificationInitialized = this->notification.initialize(camera);
	//if ( (this->getStatus() == STATUS_FILES_UPDATED_OK) ||(this->getStatus() == STATUS_SIMULATION_CONNECTED)) {
		mapInitialized = worldView.initialize();
		chatInitialized = chat.initialize(camera);
		worldView.setTilesInCamera(this->camera.getWidth(), this->camera.getHeight());
		this->personaje = characterFactory.createViewCharacter(this->getPlayerCharacterId(), this->getPlayerName());
		this->addPersonaje(this->getPlayerName(), this->personaje);
		if (!mapInitialized)
			this->setStatus(STATUS_INIT_ERROR);
	//}


	if (mapInitialized) {
		//TODO: cambiar por this->camera.setCenterPixel(worldView.personaje()->getPixelPosition());
		std::pair<int,int> posPersonaje = this->personaje->getPixelPosition();
		this->camera.setOffsetX(static_cast<float>(posPersonaje.first-332));
		this->camera.setOffsetY(static_cast<float>(posPersonaje.second-204));
		AnimatedEntity errorEntity;
		errorEntity.loadImages(ERROR_ANIMATED_DIR);
		errorEntity.delay(0);
		this->errorImage = new SpriteAnimado(&errorEntity);
	}


	this->menu->setNotificationFont(this->getFontSize(20));
	//Initialize SDL_Mixer
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096);
	//Load background music
	this->setMusic(Mix_LoadMUS("../Music/music.ogg"));

	this->startBackgroundMusic();

}

GameView& GameView::instance() {
	static GameView singleton;
	return singleton;
}

view::Stage* GameView::getWorldView() {
	return &worldView;
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
}

Personaje* GameView::getMyPersonaje() {
	if (this->personaje) {
		return this->personaje;
	}
	Logger::instance().nullPointer("function Personaje* GameView::getMyPersonaje");
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
	if ((this->getStatus() == STATUS_SIMULATION_CONNECTED)||(this->getStatus() == STATUS_SIMULATION_CONNECTION_LOST)) {
		this->chat.modelChat->cleanUp();
	}

	//Free background music.
	Mix_FreeMusic(this->getMusic());
	//Free SDL_mixer.
	Mix_CloseAudio();

	while (!this->fonts.empty())
	{
		TTF_CloseFont(this->fonts.begin()->second);
		this->fonts.erase(this->fonts.begin());
	}


}

void GameView::render() {

	SDL_FillRect(this->camera.cameraSurface, NULL, 0);

	if (this->getStatus() != STATUS_SIMULATION_CONNECTED) {
		this->menu->render(this->camera);
	} else {
		this->worldView.render(this->camera);
		if (chat.isTyping())
			this->chat.render(this->camera);
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
			//this->startBackgroundMusic();
		}
		break;
		case STATUS_UPDATING_FILES: {
			//descarga de archivos
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
		}
		break;
		case STATUS_FILES_UPDATED_OK: {
			//loggeo al server
			Instruction instruction;
			instruction.setOpCode(OPCODE_LOGIN_REQUEST);
			instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID,this->getPlayerName());
			instruction.insertArgument( INSTRUCTION_ARGUMENT_KEY_CHARACTER, this->getPlayerCharacterId());
			this->getLogin()->getLoginUpdater().addInstruction(instruction);
			this->_login.initialize();
			this->getModelUpdater()->startUpdating();
			Game::instance().initialize();
			this->initialize();

			//check where this should be
			//bool filesOK = (GameView::instance().getStatus() == STATUS_FILES_UPDATED_OK);
			bool loginOK = (GameView::instance().getStatus() != STATUS_LOGIN_USER_FAILED)&&(GameView::instance().getStatus() != STATUS_LOGIN_CONNECTION_LOST);
			bool simulationOK = (GameView::instance().getStatus() != STATUS_SIMULATION_CONNECTION_LOST)&&(GameView::instance().getStatus() != STATUS_SERVER_UNREACHEABLE);
			if ( loginOK && simulationOK /*&& filesOK*/) {
				//Instruction instruction;
				instruction.clear();
				instruction.setOpCode(OPCODE_CONNECT_TO_CHAT);
				instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID, GameView::instance().getPlayerName());
				GameView::instance().getChat()->modelChat->getMessagesList().push_back("Connecting to chat");
				GameView::instance().getChat()->modelChat->getChatUpdater().addInstruction(instruction);

				instruction.clear();
				instruction.setOpCode(OPCODE_CONNECT_TO_SIMULATION);
				instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID, GameView::instance().getPlayerName());
				this->getModelUpdater()->addInstruction(instruction);

			}
		}
		break;
		case STATUS_INIT_ERROR:
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			//this->menu->setNotificationFontSize(20);
			this->menu->setNotificationMessage("      ERROR LOADING CLIENT");
			this->menu->setDisplayNotification(true);
			
		break;
		case STATUS_SERVER_UNREACHEABLE:
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			//this->menu->setNotificationFontSize(20);
			this->menu->setNotificationMessage("        SERVER UNREACHABLE");
			this->menu->setDisplayNotification(true);
		break;
		case STATUS_READY_TO_UPDATE:
			this->menu->setNotificationFontColor(Camera::GREEN_COLOR);
			//this->menu->setNotificationFontSize(this->getFontSize(20));
			this->menu->setDisplayNotification(true);
			this->menu->setNotificationMessage("         UPDATING FILES..");
			this->setStatus(STATUS_UPDATING_FILES);
		break;
		case STATUS_SIMULATION_SINGLE_PLAYER:
			this->menu->setNotificationFontColor(Camera::BLUE_COLOR);
			//this->menu->setNotificationFontSize(this->getFontSize(20));
			this->menu->setNotificationMessage("  SINGLE PLAYER NOT IMPLEMENTED");
			this->menu->setDisplayNotification(true);
		break;
		case STATUS_UPDATING_CONNECTION_LOST:
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			//this->menu->setNotificationFontSize(this->getFontSize(20));
			this->menu->setNotificationMessage("UPDATED FAILED CONNECTION LOST");
			this->menu->setDisplayNotification(true);
		break;
		case STATUS_SIMULATION_CONNECTED:
			this->worldView.update();
			this->chat.update(camera);
		break;
		case STATUS_SIMULATION_CONNECTION_LOST:
			this->camera.unconfigure();
			this->menu->setNotificationMessage("   SERVER CONNECTION LOST");
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			//this->menu->setNotificationFontSize(this->getFontSize(20));
			this->menu->setDisplayNotification(true);
			Mix_HaltMusic();
		break;
		case STATUS_LOGIN_USER_FAILED:
			this->menu->setNotificationMessage(" USER NAME UNAVAILABLE");
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			//this->menu->setNotificationFontSize(this->getFontSize(20));
			this->menu->setDisplayNotification(true);
		break;
		case STATUS_LOGIN_CONNECTION_LOST:
			this->menu->setNotificationMessage(" CONNECTION LOGIN FAILED");
			this->menu->setNotificationFontColor(Camera::RED_COLOR);
			//this->menu->setNotificationFontSize(16);
			this->menu->setDisplayNotification(true);
		break;
	}
}

bool GameView::insidePlayerVision(std::pair<int,int> pos) {
	bool inside = this->getMyPersonaje()->personajeModelo()->getVision()->isInsideVision(pos);

	if (!inside) {
		TileModel* relatedTile = this->worldView.getWorldModel()->getTileAt(pos)->getRelatedTile();
		if (relatedTile) {//TODO: mejorar para optimizar codigo
			// preguntar si es drawable() e ir salteando..
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
			pair<int,int> posChar = (*it).second->getPosicionEnTiles();
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

Mix_Music* GameView::getMusic() {
	return this->_music;
}

void GameView::setMusic(Mix_Music* music) {
	this->_music = music;
}

void GameView::startBackgroundMusic() {
	Mix_PlayMusic(this->getMusic(),-1);
}

void GameView::toggleBackgroundMusic() {
	if(Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
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

ModelUpdater* GameView::getModelUpdater() {
	return &this->_modelUpdater;
}

model::Login* GameView::getLogin() {
	return &_login;
}

bool GameView::showingMenu() {
	//TODO: adaptar segun se vaya avanzando.. esto esta para modificarse!
	bool start = (GameView::instance().getStatus() == STATUS_START_SCREEN);
	bool unreachable = (GameView::instance().getStatus() == STATUS_SERVER_UNREACHEABLE);
	bool connectionLost = (GameView::instance().getStatus() == STATUS_SIMULATION_CONNECTION_LOST);
	bool singlePlayer = (GameView::instance().getStatus() == STATUS_SIMULATION_SINGLE_PLAYER);
	return (start || unreachable || connectionLost || singlePlayer) ;
}

void GameView::addFontSize(int size) {
	TTF_Font* font = TTF_OpenFont(DEFAULT_FONT_PATH, size);
	this->fonts[size] = font;
}

TTF_Font* GameView::getFontSize(int size) {
	return this->fonts.at(size);
}
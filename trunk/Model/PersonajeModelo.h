#ifndef PERSONAJEMODELO_H
#define PERSONAJEMODELO_H

#include <utility>
#include "Positionable.h"
#include "Directionable.h"
#include "Constants.h"
#include "DirList.h"
#include "AnimatedEntity.h"
#include "CharacterVision.h"


class PersonajeModelo: public Positionable, public Directionable {

public:
	PersonajeModelo();
	PersonajeModelo(int ActualX, int ActualY);
	~PersonajeModelo();
	PersonajeModelo& operator=(const PersonajeModelo&);
	void setEstado(int state);
	//void setCurrent(int x, int y);
	void setDestino(int x, int y);
	void setVelocidad(float vel);
	void setIsActivo(bool active);
	bool getIsActivo();
	int getEstado();
	float getVelocidad();
	bool estaAnimandose();
	void terminarAnimacion();
	void animar(char opcion);
	std::pair<int, int> obtenerFrentePersonaje();
	int mover(std::pair<int, int>& destino, float &velocidadAni);	//Devuelve el estado, que son las orientaciones. Devuelve la velocidad del movimiento, la corrección de la vista no se la hace
	
	std::string nextDirectory();
	bool hasDirectoryRemaining();
	void setAnimation(AnimatedEntity* entity);
	AnimatedEntity* getAnimation();
	int fps();
	int delay();
	std::string getName();
	void setName(string nombreJugador);
	void createVision(int range);
	CharacterVision* getVision();
	void update();
	void setAnimating(bool value);
	int getRefPixelX();
	int getRefPixelY();
	void restartDirectories();
	float getVidaMaxima();
	void setVidaMaxima(float vida);
	float getMagiaMaxima();
	void setMagiaMaxima(float magia);

	void setActive(bool active);
	bool isActive();
	int getOrientacion();
	void increaseSpeed(float factor);
	bool getIsReseting();
	void setIsReseting();
	bool isThereAnEnemy(int tileX, int tileY);
	void atacar();
	float getDanoMaximo();
	float getPrecisionMinima();
	void setDanoMaximo(float dano);
	void setPrecisionMinima(float precision);

	void setFollowingEnemy(bool enemy);
	std::pair <int, int> getTarget();
	bool canSee(std::pair<int, int> tile);

	void herir();
	void morir();
	void setNoTarget();
	//void setPosition(std::pair<int, int> pos);

	//void setCurrentWeaponIndex(unsigned int currentWeaponIndex);
private:

	int siCaminaDetenerse();
	int cambiarEstado(int x, int y, int cambio);
	//int obtenerOrientacion(int x, int y);	//Obtiene el sentido según el signo de x e y
	bool esNecesarioCalcularNuevoPath();
	void limpiarPath();
	int quedarseQuieto(float &velocidadAni);
	//Modifica las variables del modelo para representar el movimiento
	void moverse(std::pair<int, int>& destino, float &velocidadAni);
	void defender();

	void initialize(int pos_x, int pos_y);
	void changeToState(int addedState);
	void changeToAnimation(int animationNumber);
	
	//std::pair<int, int> current;
	std::pair<int, int> target;
	std::pair<int, int> targetParcial;
	int* xPath;
	int* yPath;
	int posMov;
	int caminoSize;
	bool isAnimating;
	int animacionActual;
	int estado;
	int orientacion;
	float velocidad;
	bool isActivo;
	AnimatedEntity * animation;
	std::string name;
	CharacterVision* vision;
	float vidaMaxima;
	float magiaMaxima;

	int obtenerOrientacionRespectoAUnTile(int x, int y);	//Obtiene el sentido según el signo de x e y
	void orientar(std::pair<int, int> destino); //orienta el personaje para que mire hacia destino
	bool followingEnemy();
	

	bool perseguirEnemigo();
	void resolverAnimacion(int animacionNueva);
	void resetChar();

	std::pair<int, int> startPosition;
	//std::pair<int, int> current;
	bool isReseting;
	bool active;
	//bool isInCenterTile;
	bool following;

	//std::vector<model::Weapon*> weapons;

	//unsigned int currentWeaponIndex;

	//std::vector<model::Weapon*>& getWeapons();

	//------------------------ATRIBUTOS (PONGAN ACA LOS ATRIBUTOS DEL PJ: VIDA, MAGIA, DAÑO, ETC)------------------------
	float precisionMinima;
	float danoMaximo;
};


#endif
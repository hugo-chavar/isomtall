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
	//------ getters/setters-----------
	void setEstado(int state);
	void setDestino(int x, int y);
	void setVelocidad(float vel);
	void setActive(bool active);
	bool isActive();
	int getEstado();
	float getVelocidad();
	bool estaAnimandose();
	float getDanoMaximo();
	float getPrecisionMinima();
	void setFollowingEnemy(bool enemy);
	std::pair <int, int> getTarget();
	std::string getName();
	void setName(string nombreJugador);
	void setAnimating(bool value);
	int getRefPixelX();
	int getRefPixelY();
	float getVidaMaxima();
	void setVidaMaxima(float vida);
	float getMagiaMaxima();
	void setMagiaMaxima(float magia);
	void setPrecisionMinima(float precision);
	void setDanoMaximo(float dano);
	void setAnimation(AnimatedEntity* entity);
	CharacterVision* getVision();
	AnimatedEntity* getAnimation();
	bool getIsReseting();
	void setIsReseting();
	int getOrientacion();

	//-----------------Functional methods -----------------------
	void terminarAnimacion();
	int mover(std::pair<int, int>& destino, float &velocidadAni);	//Devuelve el estado, que son las orientaciones. Devuelve la velocidad del movimiento, la corrección de la vista no se la hace
	std::string nextDirectory();
	bool hasDirectoryRemaining();
	
	
	int fps();
	int delay();

	
	
	void update();

	void restartDirectories();
	void increaseSpeed(float factor);
	void atacar();
	void defender();
	void herir();
	void morir();
	void hacerMagia();
	void setNoTarget();
	bool canSee(std::pair<int, int> tile);
	bool isThereAnEnemy(int tileX, int tileY);
	void createVision(int range);

	void orientar(std::pair<int, int> destino); //orienta el personaje para que mire hacia destino
	void changeToAnimation(int animationNumber);
	//void resolverAnimacion(int animacionNueva);

private:

	int siCaminaDetenerse();
	int cambiarEstado(int x, int y, int cambio);
	//int obtenerOrientacion(int x, int y);	//Obtiene el sentido según el signo de x e y
	bool esNecesarioCalcularNuevoPath();
	void limpiarPath();
	int quedarseQuieto(float &velocidadAni);
	//Modifica las variables del modelo para representar el movimiento
	void moverse(std::pair<int, int>& destino, float &velocidadAni);

	void initialize(int pos_x, int pos_y);
	void resetChar();
	void changeToState(int addedState);
	
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

	int obtenerOrientacionRespectoAUnTile(int x, int y);	//Obtiene el sentido según el signo de x e y
	
	bool followingEnemy();

	bool perseguirEnemigo();
	

	std::pair<int, int> startPosition;
	bool isReseting;
	bool active;
	//bool isInCenterTile;
	bool following;

	//------------------------ATRIBUTOS (PONGAN ACA LOS ATRIBUTOS DEL PJ: VIDA, MAGIA, DAÑO, ETC)------------------------
	float precisionMinima;
	float vidaMaxima;
	float magiaMaxima;
	float danoMaximo;
};


#endif
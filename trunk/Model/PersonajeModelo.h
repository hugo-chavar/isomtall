#ifndef PERSONAJEMODELO_H
#define PERSONAJEMODELO_H

#include <utility>
#include "Positionable.h"
#include "Directionable.h"
#include "Constants.h"
#include "DirList.h"
#include "AnimatedEntity.h"
#include "CharacterVision.h"


class PersonajeModelo: public Positionable, Directionable {

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
private:

	int siCaminaDetenerse();
	int cambiarEstado(int x, int y, int cambio);
	int obtenerOrientacion(int x, int y);	//Obtiene el sentido según el signo de x e y
	bool esNecesarioCalcularNuevoPath();
	void limpiarPath();
	int quedarseQuieto(float &velocidadAni);
	//Modifica las variables del modelo para representar el movimiento
	void moverse(std::pair<int, int>& destino, float &velocidadAni);
	//void activarDesactivar();
	void atacar();
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
	//bool isInCenterTile;
	//std::map< char, int > mapKeyPressedToAnimation;
};


#endif
#ifndef PERSONAJEMODELO_H
#define PERSONAJEMODELO_H

#include <utility>
#include "Constants.h"
#include "DirList.h"
#include "AnimatedEntity.h"
#include "CharacterVision.h"


class PersonajeModelo {

public:
	PersonajeModelo();
	PersonajeModelo(int ActualX, int ActualY);
	void setEstado(int state);
	void setCurrent(int x, int y);
	void setDestino(int x, int y);
	void setVelocidad(float vel);
	void getCurrent(std::pair<int, int>& actual);
	void setIsActivo();
	bool getIsActivo();
	int getEstado();
	float getVelocidad();
	int mover(std::pair<int, int>& destino, float &velocidadAni);	//Devuelve el estado, que son las orientaciones. Devuelve la velocidad
	~PersonajeModelo();											//del movimiento, la corrección de la vista no se la hace
	string nextDirectory();
	bool hasDirectoryRemaining();
	void animation(AnimatedEntity*);
	AnimatedEntity* animation();
	int fps();
	int delay();
	bool estaAnimando();
	void terminarAnimacion();
	void animar(char opcion);
	string getName();
	void setName(string nombreJugador);
	std::pair<int, int> getPosition();
	void createVision(int range);
	CharacterVision* getVision();
	void update();
private:

	int siCaminaDetenerse();
	int cambiarEstado(int x, int y, int cambio);
	int obtenerOrientacion(int x, int y);	//Obtiene el sentido según el signo de x e y
	bool esNecesarioCalcularNuevoPath();
	void limpiarPath();
	int quedarseQuieto(float &velocidadAni);
	//Modifica las variables del modelo para representar el movimiento
	void moverse(std::pair<int, int>& destino, float &velocidadAni);
	void activarDesactivar();
	void atacar();
	
	std::pair<int, int> current;
	std::pair<int, int> target;
	std::pair<int, int> targetParcial;
	int* xPath;
	int* yPath;
	int posMov;
	int caminoSize;
	bool animando;
	int animacionActual;
	int estado;
	int orientacion;
	float velocidad;
	bool isActivo;
	AnimatedEntity * _animation;
	string name;
	CharacterVision* vision;
};


#endif
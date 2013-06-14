///Constantes del Personaje
//Mantener la diferencia de 10 entre las constantes
#ifndef PERSONAJECONSTANTES_H
#define PERSONAJECONSTANTES_H

//Fuente de texto

#define FUENTE "../Fonts/Arial.ttf"

#define VIVO 1
#define MUERTO 0

//Codigo de las animaciones

#define ESTADO_ERROR -1
#define ESTADO_MOVIMIENTO 1
#define SIN_CAMBIO 0
#define PARADO 1
#define MOVIMIENTO 2
#define FREEZAR 3
#define ATACAR 4
#define DEFENDER 5
#define HERIR 6
#define MORIR 7

//Orientacion

#define NORTE 0
#define NORESTE 1
#define NOROESTE 2
#define SUR 3
#define SUDESTE 4
#define SUDOESTE 5
#define ESTE 6
#define OESTE 7

//Atributos

#define DEFAULT_CHARACTER_MIN_PRECISION 0.5
#define DEFAULT_CHARACTER_MAX_DAMAGE 20.0
#define DEFAULT_CHARACTER_MAX_LIFE 200.0
#define DEFAULT_CHARACTER_MAX_MAGIC 100.0

#endif
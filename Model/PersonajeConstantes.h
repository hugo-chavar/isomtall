//Constantes del Personaje
//Mantener la diferencia de 10 entre las constantes
#ifndef PERSONAJECONSTANTES_H
#define PERSONAJECONSTANTES_H

//Factor de separación. Permite que las orientaciones esten alineadas (p.e. norte siempre termina en 0)

#define FACTOR_ORIENTACION 10

//Cambios de estado

#define ERROR -1
#define ESTADO_MOVIMIENTO 1
#define SIN_CAMBIO 0
#define MOVIMIENTO 20

//Codigo de las animaciones

#define STOP_N 0
#define STOP_NE 1
#define STOP_NOE 2
#define STOP_S 3
#define STOP_SE 4
#define STOP_SOE 5
#define STOP_E 6
#define STOP_O 7
#define WALK_N 8
#define WALK_NE 9
#define WALK_NOE 10
#define WALK_S 11
#define WALK_SE 12
#define WALK_SOE 13
#define WALK_E 14
#define WALK_O 15

//Parado esperando

#define PARADO_N 10
#define PARADO_NE 11
#define PARADO_NOE 12
#define PARADO_S 13
#define PARADO_SE 14
#define PARADO_SOE 15
#define PARADO_E 16
#define PARADO_O 17

//Caminando

#define CAMINANDO_N 20
#define CAMINANDO_NE 21
#define CAMINANDO_NOE 22
#define CAMINANDO_S 23
#define CAMINANDO_SE 24
#define CAMINANDO_SOE 25
#define CAMINANDO_E 26
#define CAMINANDO_O 27

//Animacion
#define ANIMACION_N 30
#define ANIMACION_NE 31
#define ANIMACION_NOE 22
#define ANIMACION_S 33
#define ANIMACION_SE 34
#define ANIMACION_SOE 35
#define ANIMACION_E 36
#define ANIMACION_O 37


#endif
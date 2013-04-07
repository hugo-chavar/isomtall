//Constantes del Personaje
//Mantener la diferencia de 10 entre las constantes
#ifndef PERSONAJECONSTANTES_H
#define PERSONAJECONSTANTES_H

//Factor de separación. Permite que las orientaciones esten alineadas (p.e. norte siempre termina en 0)

#define FACTOR_ORIENTACION 10

//Cambios de estado

#define ERROR -1;
#define ESTADO_MOVIMIENTO 1
#define SIN_CAMBIO 0

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



#endif
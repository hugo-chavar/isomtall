//Constantes del Personaje
//Mantener la diferencia de 10 entre las constantes
#ifndef PERSONAJECONSTANTES_H
#define PERSONAJECONSTANTES_H

//Fuente de texto

#define FUENTE "../Fonts/Arial.ttf"

//Factor de separación. Permite que las orientaciones esten alineadas (p.e. norte siempre termina en 0)

#define FACTOR_ORIENTACION 10

//Cambios de estado

#define ESTADO_ERROR -1
#define ESTADO_MOVIMIENTO 1
#define SIN_CAMBIO 0
#define PARADO 10
#define MOVIMIENTO 20
#define FREEZAR 30
#define ATACAR 40

//Orientacion

#define NORTE 0
#define NORESTE 1
#define NOROESTE 2
#define SUR 3
#define SUDESTE 4
#define SUDOESTE 5
#define ESTE 6
#define OESTE 7

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
#define FREEZE_N 16
#define FREEZE_NE 17
#define FREEZE_NOE 18
#define FREEZE_S 19
#define FREEZE_SE 20
#define FREEZE_SOE 21
#define FREEZE_E 22
#define FREEZE_O 23
#define ATTACK_N 24
#define ATTACK_NE 25
#define ATTACK_NOE 26
#define ATTACK_S 27
#define ATTACK_SE 28
#define ATTACK_SOE 29
#define ATTACK_E 30
#define ATTACK_O 31

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

//Freezar
#define FREEZAR_N 30
#define FREEZAR_NE 31
#define FREEZAR_NOE 32
#define FREEZAR_S 33
#define FREEZAR_SE 34
#define FREEZAR_SOE 35
#define FREEZAR_E 36
#define FREEZAR_O 37

//Atacar
#define ATACAR_N 40
#define ATACAR_NE 41
#define ATACAR_NOE 42
#define ATACAR_S 43
#define ATACAR_SE 44
#define ATACAR_SOE 45
#define ATACAR_E 46
#define ATACAR_O 47

#endif
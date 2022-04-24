#pragma once
#include "Tablero.h"

class Partida
{
private:
	Tablero tablero;
	int opcion; //sirve para determinar si vamos a jugar Jugador vs Jugador (1) o Jugador vs Maquina (2)
	bool turno;
public:
	void comienzo_partida();

};
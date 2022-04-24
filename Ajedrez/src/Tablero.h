#pragma once
#include "ListaPiezas.h"

class Tablero
{
private:
	int opcion; //sirve para distinguir si vamos a jugar Jugador vs Jugador (1) o Jugador vs Máquina (2)
	int turno; //sirve para controlar quien juega, 0 juegan blancas y 1 juegan negras
	ListaPiezas piezas; //almacen de todas las piezas presentes en el tablero
	float x_ojo;
	float y_ojo;
	float z_ojo;
public:
	~Tablero();
	void tecla(unsigned char key);
	void comienzo_partida();
	void ejecutar_movimiento();
	void mueve();
	void dibuja();
};
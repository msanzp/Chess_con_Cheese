#pragma once
#include "ListaPiezas.h"
#include "freeglut.h"
#include <math.h>
#include <iostream>

class Tablero
{
private:
	int opcion; //sirve para distinguir si vamos a jugar Jugador vs Jugador (1) o Jugador vs Máquina (2)
	int turno; //sirve para controlar quien juega, 0 juegan blancas y 1 juegan negras
	ListaPiezas piezas; //almacen de todas las piezas presentes en el tablero
	float x_ojo;//Posicion del ojo para visualizar el tablero
	float y_ojo;
	float z_ojo;
public:
	~Tablero();
	void tecla(unsigned char key);
	void comienzo_partida();//Inicializa los parámetros de las piezas y las guarda en la lista
	void ejecutar_movimiento();//Realiza las comprobaciones necesarias y desplaza la pieza si es posible
	void mueve();//??
	void dibuja();//Muestra por pantalla el tablero y las piezas
};
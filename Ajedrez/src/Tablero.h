#pragma once
#include "ListaPiezas.h"
#include "freeglut.h"

struct Posicion {
	int posX;
	int posY;
};

class Tablero
{
private:
	bool casilla_origen; // esta variable sirve para saber si tengo que seleccionar la casilla de origen
	bool casilla_destino; // esta variable sirve para saber si tengo que seleccionar la casilla de destino
	bool movimiento_realizado; // esta variable sirve para saber cuando hemos realizado un movimiento
	Posicion pieza_selecionada; // sirve para pintar todos los posibles movimientos que puede hacer una pieza seleccionada
	Posicion origen; // sirve para determinar la posicion de origen de la pieza que quiero mover
	Posicion destino; // sirve para determinar la posicion de destino de la pieza que quiero mover

	ListaPiezas piezas; //almacen de todas las piezas presentes en el tablero
public:
	float x_ojo;
	float y_ojo;
	float z_ojo;

	~Tablero();
	void comienzo_partida();
	void juego_local(int* turno, int opcion_graficos); // esta funcion controla el funcionamiento de cada jugada

	// funciones set
	void setCoordenadaX_origen(int x) { origen.posX = x; }
	void setCoordenadaY_origen(int y) { origen.posY = y; }
	void setCoordenadaX_destino(int x) { destino.posX = x; }
	void setCoordenadaY_destino(int y) { destino.posY = y; }

	// funciones get
	bool getCasilla_origen() { return casilla_origen; }
	bool getCasilla_destino() { return casilla_destino; }

	// funciones que sirven para dibujar el tablero
	void dibuja2D(int turno);
	void dibuja3D();
	void actualizarpantalla(int turno, int opcion_graficos);

	// funciones para el control por ratón
	int coordenadaX(int x);
	int coordenadaY(int y);
};
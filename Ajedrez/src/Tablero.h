#pragma once
#include "ListaPiezas.h"
#include "freeglut.h"

struct Posicion_inicial {
	int posX;
	int posY;
};

class Tablero
{
private:
	int opcion_juego; // sirve para determinar si queremos jugar JUGADOR VS JUGADOR o JUGADOR VS MAQUINA
	int opcion_color; // si jugamos JUGADOR VS MAQUINA, sirve para determinar si queremos jugar con las negras o con las blancas
	int opcion_graficos; // sirve para determinar si queremos jugar en 2D o en 3D
	int turno; //sirve para controlar quien juega, 0 juegan blancas y 1 juegan negras
	Posicion_inicial posicion_inicial; // sirve para pintar todos los posibles movimientos que puede hacer una pieza seleccionada

	ListaPiezas piezas; //almacen de todas las piezas presentes en el tablero
	float x_ojo;
	float y_ojo;
	float z_ojo;
public:
	~Tablero();
	void tecla(unsigned char key);
	void comienzo_partida();
	void ejecutar_movimiento(); // esta funcion controla el funcionamiento de cada jugada
	void mueve();

	// funciones que sirven para dibujar el tablero
	void dibuja(); // dibuja las casillas y las piezs sobre el tablero
	void actualizarpantalla();
};
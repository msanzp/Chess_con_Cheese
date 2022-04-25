#pragma once
#include "Rey.h"
#include "Reina.h"
#include "Alfil.h"
#include "Caballo.h"
#include "Torre.h"
#include "Peon.h"
#include <math.h>
#include <iostream>

#define MAX_PIEZAS 30 //número máximo de piezas de cada tipo

// esta clase solamente sirve para agrupar todas las piezas del mismo tipo

struct Posicion {
	bool presencia;
	char color;
};

class ListaPiezas {
private:
	Rey* reyes[MAX_PIEZAS]; //almacén de piezas tipo rey
	Reina* reinas[MAX_PIEZAS]; //almacén de piezas tipo reina
	Torre* torres[MAX_PIEZAS]; //almacén de piezas tipo torre
	Caballo* caballos[MAX_PIEZAS]; //almacén de piezas tipo caballo
	Alfil* alfiles[MAX_PIEZAS]; //almacén de piezas tipo alfil
	Peon* peones[MAX_PIEZAS]; //almacén de piezas tipo peón
	int numeroreyes; //número de reyes presentes en la partida
	int numeroreinas; //número de reinas presentes en la partida
	int numerotorres; //número de torres presentes en la partida
	int numerocaballos; //número de caballos presentes en la partida
	int numeroalfiles; //número de alfiles presentes en la partida
	int numeropeones; //número de peones presentes en la partida
	Posicion posiciones[8][8];//almacen de las posiciones en el tablero
public:
	ListaPiezas();
	virtual ~ListaPiezas();
	void dibuja(); // dibuja todas las piezas en el tablero

	//Funcion de introduccion de las posiciones
	void introducir_posiciones();
	
	// funciones para comprobar la validez de los movimientos
	bool comprobar_posicion(int x, int y); // devuelve false si la posición no está ocupada
	bool comprobar_movimiento(int origen_x, int origen_y, int destino_x, int destino_y); // devuelve false si el movimiento no corresponde con el tipo de pieza
	bool comprobar_trayectoria(int origen_x, int origen_y, int destino_x, int destino_y); // devuelve false si la trayectoria esta libre
	void ejecuta_movimiento(int origen_x, int origen_y, int destino_x, int destino_y);

	// funciones para comprobar si el rey se encuentra en jaque
	int comprobar_jaque(Rey* r);

	//funciones para introducir piezas en los vectores
	bool agregar(Rey* k);
	bool agregar(Reina* q);
	bool agregar(Torre* t);
	bool agregar(Caballo* c);
	bool agregar(Alfil* a);
	bool agregar(Peon* p);

	//funciones para eliminar piezas de los vectores
	void eliminar(Rey* k);
	void eliminar(Reina* q);
	void eliminar(Torre* t);
	void eliminar(Caballo* c);
	void eliminar(Alfil* a);
	void eliminar(Peon* p);

	//función para eliminar todas las piezas cuando se termine la partida
	void destruirContenido();
};
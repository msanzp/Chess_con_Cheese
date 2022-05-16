#pragma once
#include "Rey.h"
#include "Reina.h"
#include "Alfil.h"
#include "Caballo.h"
#include "Torre.h"
#include "Peon.h"

#define MAX_PIEZAS 30 //número máximo de piezas de cada tipo

// esta clase solamente sirve para agrupar todas las piezas del mismo tipo

class ListaPiezas {
private:
	int numero_jugadas; // esta variable sirve para que los peones puedan comer al paso
	
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
	int numeropiezas; //numero de piezas comidas en la partida	
	Pieza* borradas[MAX_PIEZAS]; //array que representa las fichas comidas y despues representadas al margen
public:
	ListaPiezas();
	ListaPiezas(const ListaPiezas& copia); // este constructor copia sirve para evaluar el jaque del movimiento que voy a realizar
	virtual ~ListaPiezas();
	void dibuja2D(int pieza_seleccionadaX, int pieza_seleccionadaY);
	void dibuja3D();
	
	// funciones para comprobar la validez de los movimientos
	bool comprobar_posicion(int x, int y, int turno); // devuelve TRUE si la posición está ocupada por una ficha de mi color
	bool comprobar_posicion(int x, int y); // devuelve TRUE si la posición está ocupada por una ficha cualquiera
	bool comprobar_movimiento(int origen_x, int origen_y, int destino_x, int destino_y, int turno); // devuelve FALSE si el movimiento no se puede realizar
	bool comprobar_trayectoria(int origen_x, int origen_y, int destino_x, int destino_y, int turno); // devuelve TRUE si la trayectoria NO esta libre

	void ejecuta_movimiento(int origen_x, int origen_y, int destino_x, int destino_y, int turno);
	void ejecuta_movimientocopia(int origen_x, int origen_y, int destino_x, int destino_y, int turno);

	// esta funcion sirve para que el rey no se pueda mover a una posición donde se encuentra en jaque
	bool comprobar_jaque(int x, int y, int turno); // version complicada del jaque sin llamar a comprobar_movimiento
	bool comprobar_jaque2(int x, int y, int turno); // version sencilla del jaque llamando a comprobar_movimiento
	bool comprobar_jaquemate(int turno, ListaPiezas L); // devuelve FALSE si la posicion seleccionada no esta en jaque
	bool comprobar_ahogado(int turno); // version complicada del jaque sin llamar a comprobar_movimiento

	// reglas del ajedrez un poco más raras
	bool comprobar_comeralpaso(int origen_x, int origen_y, int destino_x, int destino_y, int turno, Peon p);
	bool comprobar_enroque();

	// funciones get y set que necesitaremos
	int getNumeroReyes() { return numeroreyes; } // esta funcion sirve para comprobar al comienzo de la jugada que el rey no está en jaque
	int getNumeroReinas() { return numeroreinas; } // esta funcion sirve para comprobar al comienzo de la jugada que el rey no está en jaque
	int getNumeroTorres() { return numerotorres; } // esta funcion sirve para comprobar al comienzo de la jugada que el rey no está en jaque
	int getNumeroCaballos() { return numerocaballos; } // esta funcion sirve para comprobar al comienzo de la jugada que el rey no está en jaque
	int getNumeroAlfiles() { return numeroalfiles; } // esta funcion sirve para comprobar al comienzo de la jugada que el rey no está en jaque
	int getNumeroPeones() { return numeropeones; } // esta funcion sirve para dibujar que puedo comer al paso
	Rey getRey(int i) { return *reyes[i]; } // esta funcion sirve para dibujar que puedo comer al paso
	Reina getReina(int i) { return *reinas[i]; } // esta funcion sirve para dibujar que puedo comer al paso
	Torre getTorre(int i) { return *torres[i]; } // esta funcion sirve para dibujar que puedo comer al paso
	Caballo getCaballo(int i) { return *caballos[i]; } // esta funcion sirve para dibujar que puedo comer al paso
	Alfil getAlfil(int i) { return *alfiles[i]; } // esta funcion sirve para dibujar que puedo comer al paso
	Peon getPeon(int i) { return *peones[i]; } // esta funcion sirve para dibujar que puedo comer al paso

	//funciones para introducir piezas en los vectores
	bool agregar(Rey* k);
	bool agregar(Reina* q);
	bool agregar(Torre* t);
	bool agregar(Caballo* c);
	bool agregar(Alfil* a);
	bool agregar(Peon* p);

	bool añadir(Pieza* p);
	void dibujaBorradas2D();

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
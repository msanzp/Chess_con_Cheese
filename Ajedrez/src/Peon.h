#pragma once
#include "Pieza.h"

class Peon : public Pieza {
private:
	bool primermovimiento; // Cuando no se ha movido el peon este valor es true
	int jugada_primer_movimiento = 0; // esta variable sirve para comer al paso
public:
	Peon(int x, int y, char c, bool primer_movimiento);

	// funciones get y set
	void setJugadaPrimerMovimiento(int t) { jugada_primer_movimiento = t; }
	void setPrimerMovimiento() { primermovimiento = false; } // Cuando se mueve el peon por primerza vez se cambia primermovimiento a false
	int getJugadaPrimerMovimiento() { return jugada_primer_movimiento; }  // Cuando se mueve el peon por primerza vez se guarda la jugada en la que se ha producido
	bool getPrimerMovimiento() { return primermovimiento; }

	// función que comprueba que el peon se mueve 1 hacia adelante o 2 si es el primer movimiento
	bool comprobar_movimiento(int x, int y);
};
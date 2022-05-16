#pragma once
#include "Pieza.h"

class Rey : public Pieza {
private:
	bool primermovimiento; // esta variable me servirá para el enroque
public:
	Rey(int x, int y, char c, bool p);

	// funciones get y set
	void setPrimerMovimiento() { primermovimiento = false; } // Cuando se mueve el rey por primerza vez se cambia primermovimiento a false
	bool getPrimerMovimiento() { return primermovimiento; }

	// función que comprueba que el rey solamente se mueve 1 casilla
	bool comprobar_movimiento(int x, int y);
};
#pragma once
#include "Pieza.h"

class Rey : public Pieza {
private:
	bool primermovimiento; // esta variable me servir� para el enroque
public:
	Rey(int x, int y, char c, bool p);

	// funciones get y set
	void setPrimerMovimiento() { primermovimiento = false; } // Cuando se mueve el rey por primerza vez se cambia primermovimiento a false
	bool getPrimerMovimiento() { return primermovimiento; }

	// funci�n que comprueba que el rey solamente se mueve 1 casilla
	bool comprobar_movimiento(int x, int y);
};
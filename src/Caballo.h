#pragma once
#include "Pieza.h"

class Caballo : public Pieza {
private:
	
public:
	Caballo(int x, int y, char c);
	bool comprobar_movimiento(int x, int y); // sirve para determinar si el movimiento a realizar es o no válido
};
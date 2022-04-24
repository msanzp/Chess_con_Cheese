#pragma once
#include "Pieza.h"

class Reina : public Pieza {
private:
	
public:
	Reina(int x, int y, char c);
	void dibuja();
	bool comprobar_movimiento(int x, int y); // sirve para determinar si el movimiento a realizar es o no válido
};
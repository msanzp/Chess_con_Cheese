#pragma once
#include "Pieza.h"
#include <math.h>
#include "freeglut.h"

class Alfil : public Pieza {
private:
	
public:
	Alfil(int x, int y, char c);
	bool comprobar_movimiento(int x, int y); // sirve para determinar si el movimiento a realizar es o no v?lido
};
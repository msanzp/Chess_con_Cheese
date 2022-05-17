#include "freeglut.h"
#include "Caballo.h"
#include <math.h>

Caballo::Caballo(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
}

bool Caballo::comprobar_movimiento(int x, int y) {
	if ((fabs(posX - x) == 2) && (fabs(posY - y) == 1))
		return true;
	if ((fabs(posX - x) == 1) && (fabs(posY - y) == 2))
		return true;
	return false;
}
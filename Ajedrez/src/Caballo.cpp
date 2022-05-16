#include "freeglut.h"
#include "Caballo.h"
#include <math.h>

Caballo::Caballo(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
	// 0=rey, 1=reina, 2=alfil, 3=peon, 4=caballo, 5=torre
	tipo = 4;
}

bool Caballo::comprobar_movimiento(int x, int y) {
	if ((fabs(posX - x) == 2) && (fabs(posY - y) == 1))
		return true;
	if ((fabs(posX - x) == 1) && (fabs(posY - y) == 2))
		return true;
	return false;
}
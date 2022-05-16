#include "Alfil.h"

Alfil::Alfil(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
	// 0=rey, 1=reina, 2=alfil, 3=peon, 4=caballo, 5=torre
	tipo = 2;
}

bool Alfil::comprobar_movimiento(int x, int y) {
	if (fabs(posX - x) == fabs(posY - y))
		return true;
	else
		return false;
}
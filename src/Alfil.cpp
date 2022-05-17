#include "Alfil.h"

Alfil::Alfil(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
}

bool Alfil::comprobar_movimiento(int x, int y) {
	if (fabs(posX - x) == fabs(posY - y))
		return true;
	else
		return false;
}
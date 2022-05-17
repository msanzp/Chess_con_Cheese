#include "freeglut.h"
#include "Reina.h"
#include <math.h>

Reina::Reina(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
}

bool Reina::comprobar_movimiento(int x, int y) {
	if (fabs(posX - x) == fabs(posY - y))
		return true;
	if ((fabs(posX - x) == 0) && (fabs(posY - y) != 0))
		return true;
	if ((fabs(posX - x) != 0) && (fabs(posY - y) == 0))
		return true;
	return false;
}
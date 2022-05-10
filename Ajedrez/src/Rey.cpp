#include "freeglut.h"
#include "Rey.h"
#include <math.h>

Rey::Rey(int x, int y, char c, bool p) {
	color = c;
	posX = x;
	posY = y;
	primermovimiento = p;
}

bool Rey::comprobar_movimiento(int x, int y){
	if ((fabs(posX - x) == 1) && (fabs(posY - y) == 0))
		return true;
	if ((fabs(posX - x) == 0) && (fabs(posY - y) == 1))
		return true;
	if ((fabs(posX - x) == 1) && (fabs(posY - y) == 1))
		return true;
	return false;
}
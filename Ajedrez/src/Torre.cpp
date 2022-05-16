#include "freeglut.h"
#include "Torre.h"
#include <math.h>

Torre::Torre(int x, int y, char c, bool p) {
	color = c;
	posX = x;
	posY = y;
	primermovimiento = p;
	// 0=rey, 1=reina, 2=alfil, 3=peon, 4=caballo, 5=torre
	tipo = 5;
}

bool Torre::comprobar_movimiento(int x, int y) {
	if ((fabs(posX - x) == 0) && (fabs(posY - y) != 0))
		return true;
	if ((fabs(posX - x) != 0) && (fabs(posY - y) == 0))
		return true;
	return false;
}
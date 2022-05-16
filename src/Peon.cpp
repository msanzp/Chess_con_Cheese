#include "freeglut.h"
#include "Peon.h"
#include <math.h>

Peon::Peon(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
	// 0=rey, 1=reina, 2=alfil, 3=peon, 4=caballo, 5=torre
	tipo = 3;
}

bool Peon::comprobar_movimiento(int x, int y) {
	int variaciony;
	if (color == 'w')
		variaciony = y - posY;
	else
		variaciony = posY - y;

	if (primermovimiento == true) {
		if ((posX - x == 0) && (variaciony == 1 || variaciony == 2)) // No se puede poner valor absoluto debido a que el peon solo se desplaza en un sentido
			return true;
		else
			return false;
	}
	else {
		if ((posX - x == 0) && (variaciony == 1))
			return true;
		else
			return false;
	}
}
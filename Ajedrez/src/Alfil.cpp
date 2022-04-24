#include "freeglut.h"
#include "Alfil.h"
#include <math.h>

Alfil::Alfil(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
}

void Alfil::dibuja() {
	if (color == 'w')
		glColor3ub(255, 255, 255);
	if (color == 'b')
		glColor3ub(255, 0, 0);
	glTranslatef(posX * 4 - 2, posY * 4 - 2, 0);
	glutSolidSphere(1.5, 20, 20);
	glTranslatef(-(posX * 4 - 2), -(posY * 4 - 2), 0);
}

bool Alfil::comprobar_movimiento(int x, int y) {
	if (fabs(posX - x) == fabs(posY - y))
		return true;
	else
		return false;
}
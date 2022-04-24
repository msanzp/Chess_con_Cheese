#include "freeglut.h"
#include "Caballo.h"
#include <math.h>

Caballo::Caballo(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
}

void Caballo::dibuja() {
	if (color == 'w')
		glColor3ub(255, 255, 255);
	if (color == 'b')
		glColor3ub(255, 0, 0);
	glTranslatef(posX * 4 - 2, posY * 4 - 2, 0);
	glutSolidSphere(1.5, 20, 20);
	glTranslatef(-(posX * 4 - 2), -(posY * 4 - 2), 0);
}

bool Caballo::comprobar_movimiento(int x, int y) {
	if ((fabs(posX - x) == 2) && (fabs(posY - y) == 1))
		return true;
	else if ((fabs(posX - x) == 1) && (fabs(posY - y) == 2))
		return true;
	else
		return false;
}
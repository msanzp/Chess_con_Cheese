#include "freeglut.h"
#include "Torre.h"
#include <math.h>

Torre::Torre(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
}

void Torre::dibuja() {
	if (color == 'w')
		glColor3ub(255, 255, 255);
	if (color == 'b')
		glColor3ub(255, 0, 0);
	glTranslatef(posX * 4 - 2, posY * 4 - 2, 0);
	glutSolidSphere(1.5, 20, 20);
	glTranslatef(-(posX * 4 - 2), -(posY * 4 - 2), 0);
}

bool Torre::comprobar_movimiento(int x, int y) {
	if ((fabs(posX - x) == 0) && (fabs(posY - y) != 0))
		return true;
	else if ((fabs(posX - x) != 0) && (fabs(posY - y) == 0))
		return true;
	else
		return false;
}
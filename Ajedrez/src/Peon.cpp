#include "freeglut.h"
#include "Peon.h"
#include <math.h>

Peon::Peon(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
}

void Peon::dibuja() {
	if (color == 'w')
		glColor3ub(255, 255, 255);
	if (color == 'b')
		glColor3ub(255, 0, 0);
	glTranslatef(posX * 4 - 2, posY * 4 - 2, 0);
	glutSolidSphere(1.5, 20, 20);
	glTranslatef(-(posX * 4 - 2), -(posY * 4 - 2), 0);
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
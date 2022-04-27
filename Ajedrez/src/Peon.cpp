#include "Peon.h"


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

void Peon::CambiaPrimeraJugada() {
	PrimeraJugada = false;
}

bool Peon::comprobar_movimiento(int x, int y) {
	int res;
	if (color == 'w')
		 res = y - posY;
	else res = posY - y;

	if (PrimeraJugada == true) {
		if ((posX - x == 0) && (res==1 || res==2))//No se puede poner valor absoluto debido a que el peon solo se desplaza en un sentido
			return true;
		else
			return false;
	}
	else {
		if ((posX - x == 0) && (res == 1))
			return true;
		else
			return false;
	}
}
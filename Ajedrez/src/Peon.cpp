#include "freeglut.h"
#include "Peon.h"
#include <math.h>

Peon::Peon(int x, int y, char c) {
	color = c;
	posX = x;
	posY = y;
}

void Peon::dibuja() {
	glEnable(GL_TEXTURE_2D);
	for (int j = 1; j < 9; j++) {
		for (int i = 1; i < 9; i++) {
			if (posX == j && posY == i) {
				if (j % 2 == 1) {//Bucle para las coordenadas y
					if (i % 2 == 1) {//Bucle para las coordenadas x
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonblanco_fondonegro.png").id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonnegro_fondonegro.png").id);
					}
					else {
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonblanco_fondoblanco.png").id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonnegro_fondoblanco.png").id);
					}
				}
				else {
					if (i % 2 == 0) {
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonblanco_fondonegro.png").id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonnegro_fondonegro.png").id);
					}
					else {
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonblanco_fondoblanco.png").id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonnegro_fondoblanco.png").id);
					}

				}
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(posX * 4 - 4, posY * 4 - 4, 0);
				glTexCoord2d(1, 1);		glVertex3f(posX * 4, posY * 4 - 4, 0);
				glTexCoord2d(1, 0);		glVertex3f(posX * 4, posY * 4, 0);
				glTexCoord2d(0, 0);		glVertex3f(posX * 4 - 4, posY * 4, 0);
				glEnd();
			}
		}
	}
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
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
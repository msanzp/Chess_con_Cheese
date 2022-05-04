#include "freeglut.h"
#include "Rey.h"
#include <math.h>

Rey::Rey(int x, int y, char c, bool p) {
	color = c;
	posX = x;
	posY = y;
	primermovimiento = p;
}

void Rey::dibuja() {
	glEnable(GL_TEXTURE_2D);
	for (int j = 1; j < 9; j++) {
		for (int i = 1; i < 9; i++) {
			if (posX == j && posY == i) {
				if (j % 2 == 1) {//Bucle para las coordenadas y
					if (i % 2 == 1) {//Bucle para las coordenadas x
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reyblanco_fondonegro.png").id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reynegro_fondonegro.png").id);
					}
					else {
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reyblanco_fondoblanco.png").id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reynegro_fondoblanco.png").id);
					}
				}
				else {
					if (i % 2 == 0) {
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reyblanco_fondonegro.png").id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reynegro_fondonegro.png").id);
					}
					else {
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reyblanco_fondoblanco.png").id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reynegro_fondoblanco.png").id);
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

bool Rey::comprobar_movimiento(int x, int y){
	if ((fabs(posX - x) == 1) && (fabs(posY - y) == 0))
		return true;
	if ((fabs(posX - x) == 0) && (fabs(posY - y) == 1))
		return true;
	if ((fabs(posX - x) == 1) && (fabs(posY - y) == 1))
		return true;
	return false;
}
#include "Tablero.h"
#include <iostream>

using namespace std;

Tablero::~Tablero() {
	piezas.destruirContenido();
}

void Tablero::comienzo_partida()
{
	turno = 0; // siempre empiezan jugando las blancas
	casilla_origen = true;
	casilla_destino = false;
	pieza_selecionada.posX = pieza_selecionada.posY = 0;

	//creamos los reyes
	Rey* reyblanco = new Rey(5, 1, 'w', true);
	Rey* reynegro = new Rey(5, 8, 'b', true);
	piezas.agregar(reyblanco);
	piezas.agregar(reynegro);
	
	//creamos las reinas
	Reina* reinablanca = new Reina(4, 1, 'w');
	Reina* reinanegra = new Reina(4, 8, 'b');
	piezas.agregar(reinablanca);
	piezas.agregar(reinanegra);

	//creamos los alfiles
	Alfil* alfilblanco1 = new Alfil(3, 1,'w');
	Alfil* alfilblanco2 = new Alfil(6, 1, 'w');
	Alfil* alfilnegro1 = new Alfil(6, 8, 'b');
	Alfil* alfilnegro2 = new Alfil(3, 8, 'b');
	piezas.agregar(alfilblanco1);
	piezas.agregar(alfilblanco2);
	piezas.agregar(alfilnegro1);
	piezas.agregar(alfilnegro2);

	//creamos los caballos
	Caballo* caballoblanco1 = new Caballo(2, 1, 'w');
	Caballo* caballoblanco2 = new Caballo(7, 1, 'w');
	Caballo* caballonegro1 = new Caballo(7, 8, 'b');
	Caballo* caballonegro2 = new Caballo(2, 8, 'b');
	piezas.agregar(caballoblanco1);
	piezas.agregar(caballoblanco2);
	piezas.agregar(caballonegro1);
	piezas.agregar(caballonegro2);

	//creamos las torres
	Torre* torreblanca1 = new Torre(1, 1, 'w', true);
	Torre* torreblanca2 = new Torre(8, 1, 'w', true);
	Torre* torrenegra1 = new Torre(8, 8, 'b', true);
	Torre* torrenegra2 = new Torre(1, 8, 'b', true);
	piezas.agregar(torreblanca1);
	piezas.agregar(torreblanca2);
	piezas.agregar(torrenegra1);
	piezas.agregar(torrenegra2);

	//creamos los peones
	for (int i = 1; i < 9; i++) {
		Peon* aux1 = new Peon(i, 2, 'w');
		Peon* aux2 = new Peon(i, 7, 'b');
		piezas.agregar(aux1);
		piezas.agregar(aux2);
	}

	x_ojo = 16;
	y_ojo = 16;
	z_ojo = 50;
}

void Tablero::ejecutar_movimiento()
{
	bool jaque = false;
	bool jaque_mate = false;
	char color = 'w'; // esta variable sirve para saber que color de pieza mueve el jugador del turno
	if (turno == 1)
		color = 'b';

	if (piezas.comprobar_jaquemate(turno, piezas) == false && piezas.comprobar_ahogado(turno) == false)	{
		if (origen.posX != 0 && origen.posY != 0) {
			if (piezas.comprobar_posicion(origen.posX, origen.posY, turno) == true) {
				casilla_origen = false;
				casilla_destino = true;
				pieza_selecionada.posX = origen.posX;
				pieza_selecionada.posY = origen.posY;
				actualizarpantalla();
				if (destino.posX != 0 && destino.posY != 0) {
					if (piezas.comprobar_posicion(destino.posX, destino.posY, turno) == true) {
						origen.posX = destino.posX;
						origen.posY = destino.posY;
						destino.posX = destino.posY = 0;
						pieza_selecionada.posX = origen.posX;
						pieza_selecionada.posY = origen.posY;
						actualizarpantalla();
					}
					else if (piezas.comprobar_movimiento(origen.posX, origen.posY, destino.posX, destino.posY, turno) == true) {
						ListaPiezas piezas2 = (piezas);
						piezas2.ejecuta_movimientocopia(origen.posX, origen.posX, destino.posX, destino.posY, turno);
						for (int i = 0; i < piezas2.getNumeroReyes(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getRey(i).getColor() == color)
								jaque = piezas2.comprobar_jaque2(piezas2.getRey(i).getX(), piezas2.getRey(i).getY(), turno);
						}
						if (jaque == true) {
							origen.posX = origen.posY = 0;
							destino.posX = destino.posY = 0;
							casilla_origen = true;
							casilla_destino = false;
						}
						else {
							piezas.ejecuta_movimiento(origen.posX, origen.posY, destino.posX, destino.posY, turno);
							pieza_selecionada.posX = pieza_selecionada.posY = 0;
							origen.posX = origen.posY = 0;
							destino.posX = destino.posY = 0;
							if (turno == 0)
								turno = 1;
							else
								turno = 0;
							casilla_origen = true;
							casilla_destino = false;
						}	
					}
					else {
						destino.posX = destino.posY = 0;
						casilla_origen = true;
						casilla_destino = false;
					}
				}
			}
			else {
				origen.posX = origen.posY = 0;
				casilla_origen = true;
				casilla_destino = false;
			}
		}
	}
	else {
		if(piezas.comprobar_jaquemate(turno, piezas) == true)
			cout << "JAQUE MATE" << endl;
		if (piezas.comprobar_ahogado(turno) == true)
			cout << "TABLAS" << endl;
	}
}

void Tablero::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		16, 16, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	glDisable(GL_LIGHTING);

	// DIBUJO DEL TABLERO
	// creamos los cuadrados de colores del tablero
	glEnable(GL_TEXTURE_2D);
	for (int j = 1; j < 9; j++)	{
		for (int i = 1; i < 9; i++) {
			if (piezas.comprobar_posicion(j, i) == false) {
				if (j % 2 == 1) {//Bucle para las coordenadas y
					if (i % 2 == 1)//Bucle para las coordenadas x
						glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/fondonegro.png").id);
					else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/fondoblanco.png").id);
				}
				else {
					if (i % 2 == 0)
						glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/fondonegro.png").id);
					else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/fondoblanco.png").id);
				}
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(j * 4 - 4, i * 4 - 4, 0);
				glTexCoord2d(1, 1);		glVertex3f(j * 4, i * 4 - 4, 0);
				glTexCoord2d(1, 0);		glVertex3f(j * 4, i * 4, 0);
				glTexCoord2d(0, 0);		glVertex3f(j * 4 - 4, i * 4, 0);
				glEnd();
			}
		}
	}
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// damos un marco al tablero
	glBegin(GL_POLYGON);
	glColor3ub(204, 102, 0);
	glVertex3f(-1.5, -1.5, -1);
	glVertex3f(-1.5, 33.5, -1);
	glVertex3f(33.5, 33.5, -1);
	glVertex3f(33.5, -1.5, -1);
	glEnd();
	
	// DIBUJAMOS POSICIÓN DE PIEZA SELECCIONADA Y POSIBLES DESTINOS
	bool posible_destino; // sirve para determinar si la posición de destino es válida
	bool pieza_en_destino; // sirve para saber si la posición de destino está ocupada por una pieza del otro

	bool otro_turno;
	if (turno == 0)
		otro_turno = 1;
	else
		otro_turno = 0;

	if ((pieza_selecionada.posX != 0) && (pieza_selecionada.posY != 0)){
		// iluminamos la casilla de la pieza seleccionada
		glBegin(GL_POLYGON);
		glColor3ub(0, 255, 0);
		glVertex3f(pieza_selecionada.posX * 4 - 4, pieza_selecionada.posY * 4, 0.1);
		glVertex3f(pieza_selecionada.posX * 4, pieza_selecionada.posY * 4, 0.1);
		glVertex3f(pieza_selecionada.posX * 4, pieza_selecionada.posY * 4 - 4, 0.1);
		glVertex3f(pieza_selecionada.posX * 4 - 4, pieza_selecionada.posY * 4 - 4, 0.1);
		glEnd();

		// marcamos todos los posibles destinos de la pieza seleccionada
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				posible_destino = piezas.comprobar_movimiento(pieza_selecionada.posX, pieza_selecionada.posY, i, j, turno);
				pieza_en_destino = piezas.comprobar_posicion(i, j, otro_turno);
				for (int h = 0; h < piezas.getNumeroPeones(); h++) {
					bool comeralpaso = false; // sirve para dibujar que podemos comer cuando comemos al paso
					if (pieza_selecionada.posX == piezas.getPeon(h).getX() && pieza_selecionada.posY == piezas.getPeon(h).getY())
						comeralpaso = piezas.comprobar_comeralpaso(pieza_selecionada.posX, pieza_selecionada.posY, i, j, turno, piezas.getPeon(h));
					// ponemos un anillo verde en todos aquellos puntos a los que podamos ir comiendo ficha					
					if (posible_destino == true && (pieza_en_destino == true || comeralpaso == true)) {
						glTranslatef(i * 4 - 2, j * 4 - 2, 0);
						glutSolidTorus(0.2, 1.8, 20, 20);
						glTranslatef(-(i * 4 - 2), -(j * 4 - 2), 0);
					}
					// ponemos un cuadrado verde en todos aquellos puntos a los que podamos ir sin comer ficha, a excepción de comer al paso
					if (posible_destino == true && pieza_en_destino == false) {
						glBegin(GL_POLYGON);
						glColor3ub(0, 255, 0);
						glVertex3f(i * 4 - 2.5, j * 4 - 1.5, 0.1);
						glVertex3f(i * 4 - 1.5, j * 4 - 1.5, 0.1);
						glVertex3f(i * 4 - 1.5, j * 4 - 2.5, 0.1);
						glVertex3f(i * 4 - 2.5, j * 4 - 2.5, 0.1);
						glEnd();
					}
				}
			}
		}
	}
	
	glEnable(GL_LIGHTING);

	// DIBUJAMOS LAS PIEZAS
	piezas.dibuja();
}

void Tablero::actualizarpantalla() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	dibuja();
	glutSwapBuffers();
}

int Tablero::coordenadaX(int x) {
	if (x >= 135 && x <= 162)
		return 1;
	else if (x >= 163 && x <= 269)
		return 2;
	else if (x >= 270 && x <= 334)
		return 3;
	else if (x >= 335 && x <= 401)
		return 4;
	else if (x >= 402 && x <= 467)
		return 5;
	else if (x >= 468 && x <= 532)
		return 6;
	else if (x >= 533 && x <= 598)
		return 7;
	else if (x >= 599 && x <= 664)
		return 8;
	else
		return 0;
}

int Tablero::coordenadaY(int y) {
	if (y >= 37 && y <= 102)
		return 8;
	else if (y >= 103 && y <= 169)
		return 7;
	else if (y >= 170 && y <= 234)
		return 6;
	else if (y >= 235 && y <= 298)
		return 5;
	else if (y >= 299 && y <= 365)
		return 4;
	else if (y >= 366 && y <= 433)
		return 3;
	else if (y >= 434 && y <= 498)
		return 2;
	else if (y >= 499 && y <= 563)
		return 1;
	else
		return 0;
}
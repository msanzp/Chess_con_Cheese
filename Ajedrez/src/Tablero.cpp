#include "Tablero.h"
#include <iostream>

using namespace std;

Tablero::~Tablero() {
	piezas.destruirContenido();
}

void Tablero::tecla(unsigned char key)
{

}

void Tablero::comienzo_partida()
{
	turno = 0; // siempre empiezan jugando las blancas
	posicion_inicial.posX =	posicion_inicial.posY = 0;

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
	int origen_x, origen_y; // para determinar las coordenadas de la pieza a ser movida
	int destino_x, destino_y; // para determinar las coordenadas de la posición de destino
	bool jaque = false;
	bool jaque_mate = false;
	char color = 'w'; // esta variable sirve para saber que color de pieza mueve el jugador del turno

	if (piezas.comprobar_jaquemate(turno, piezas) == false)	{
		if (turno == 0)
			cout << "TURNO DE LAS BLANCAS" << endl;
		if (turno == 1) {
			color = 'b';
			cout << "TURNO DE LAS NEGRAS" << endl;
		}
		do {
			jaque = false;
			do {
				posicion_inicial.posX = posicion_inicial.posY = 0;
				actualizarpantalla();
				do {
					cout << "Posición de la pieza que desea mover:" << endl;
					cin >> origen_x >> origen_y;
				} while (piezas.comprobar_posicion(origen_x, origen_y, turno) == false); // el bucle se repite si en la casilla introducida no hay pieza del color del jugador al que le toca mover
				posicion_inicial.posX = origen_x;
				posicion_inicial.posY = origen_y;
				actualizarpantalla();
				// introducimos la casilla a donde queremos mover nuestra pieza
				cout << "Posición de destino de la pieza:" << endl;
				cin >> destino_x >> destino_y;
			} while (piezas.comprobar_movimiento(origen_x, origen_y, destino_x, destino_y, turno) == false); // el bucle se repite si el movimiento no es válido

			// una vez escogido el movimiento, comprobamos que nuestro ney no se encuentra en jaque
			ListaPiezas piezas2 = (piezas);
			piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
			for (int i = 0; i < piezas2.getNumeroReyes(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
				if (piezas2.getRey(i).getColor() == color)
					jaque = piezas2.comprobar_jaque2(piezas2.getRey(i).getX(), piezas2.getRey(i).getY(), turno);
			}
		} while (jaque == true);
		piezas.ejecuta_movimiento(origen_x, origen_y, destino_x, destino_y, turno);
		cout << "Movimiento realizado" << endl;
		// cambiamos el turno para la siguiente ronda
		if (turno == 0)
			turno = 1;
		else
			turno = 0;

		// reiniciamos la posicion de la pieza seleccionada para no pintar la casilla en verde
		posicion_inicial.posX = posicion_inicial.posY = 0;
	}
	else {
		cout << "JAQUE MATE" << endl;
	}
}

void Tablero::mueve()
{

}

void Tablero::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		16, 16, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	glDisable(GL_LIGHTING);

	// DIBUJO DEL TABLERO
	// creamos los cuadrados de colores del tablero
	glBegin(GL_POLYGON);
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++) {
			if (j % 2 == 1) {//Bucle para las coordenadas y
				if (i % 2 == 1)//Bucle para las coordenadas x
					glColor3ub(0, 0, 0);
				else glColor3ub(255, 255, 255);
			}
			else {
				if (i % 2 == 0)
					glColor3ub(0, 0, 0);
				else glColor3ub(255, 255, 255);
			}
			glVertex3f(i * 4, j * 4, 0);//Definición de los vértices de cada casilla
			glVertex3f(i * 4, (j + 1) * 4, 0);
			glVertex3f((i + 1) * 4, (j + 1) * 4, 0);
			glVertex3f((i + 1) * 4, j * 4, 0);
		}
	}
	glEnd();
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
	bool comeralpaso; // sirve para dibujar que podemos comer cuando comemos al paso

	bool otro_turno;
	if (turno == 0)
		otro_turno = 1;
	else
		otro_turno = 0;

	if ((posicion_inicial.posX != 0) && (posicion_inicial.posY != 0)){
		// iluminamos la casilla de la pieza seleccionada
		glBegin(GL_POLYGON);
		glColor3ub(0, 255, 0);
		glVertex3f(posicion_inicial.posX * 4 - 4, posicion_inicial.posY * 4, 0.1);
		glVertex3f(posicion_inicial.posX * 4, posicion_inicial.posY * 4, 0.1);
		glVertex3f(posicion_inicial.posX * 4, posicion_inicial.posY * 4 - 4, 0.1);
		glVertex3f(posicion_inicial.posX * 4 - 4, posicion_inicial.posY * 4 - 4, 0.1);
		glEnd();

		// marcamos todos los posibles destinos de la pieza seleccionada
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				posible_destino = piezas.comprobar_movimiento(posicion_inicial.posX, posicion_inicial.posY, i, j, turno);
				pieza_en_destino = piezas.comprobar_posicion(i, j, otro_turno);
				for (int h = 0; h < piezas.getNumeroPeones(); h++) {
					comeralpaso = piezas.comprobar_comeralpaso(posicion_inicial.posX, posicion_inicial.posY, i, j, turno, piezas.getPeon(h));
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

// copiamos la funcion OnDraw para poder llamarla cuando queramos desde cualquier parte del codigo
void Tablero::actualizarpantalla() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	dibuja();
	glutSwapBuffers();
}
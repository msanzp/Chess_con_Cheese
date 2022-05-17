#include "Tablero.h"
#include <iostream>

using namespace std;

Tablero::~Tablero() {
	piezas.destruirContenido();
}

void Tablero::comienzo_partida()
{
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
	y_ojo = 18;
	z_ojo = 85;
}

void Tablero::juego_local(int opcion_juego, int opcion_color, int *turno, int opcion_graficos)
{
	bool jaque = false;
	bool jaque_mate = false;
	char color = 'w'; // esta variable sirve para saber que color de pieza mueve el jugador del turno
	if (*turno == 1)
		color = 'b';
		
	if (piezas.comprobar_jaquemate(*turno, piezas) == false && piezas.comprobar_ahogado(*turno, piezas) == false){
		if (opcion_graficos == 2) { // solamente vamos a jugar con teclado para el modo de juego 3D debido a los altos tiempos de carga
			cout << "Casilla origen" << endl;
			cin >> origen.posX >> origen.posY;
		}
		if (origen.posX != 0 && origen.posY != 0) {
			if (piezas.comprobar_posicion(origen.posX, origen.posY, *turno) == true) {
				casilla_origen = false;
				casilla_destino = true;
				pieza_selecionada.posX = origen.posX;
				pieza_selecionada.posY = origen.posY;
				actualizarpantalla(opcion_juego, opcion_color, *turno, opcion_graficos);
				if (opcion_graficos == 2) { // solamente vamos a jugar con teclado para el modo de juego 3D debido a los altos tiempos de carga
					cout << "Casilla destino" << endl,
					cin >> destino.posX >> destino.posY;
				}
				if (destino.posX != 0 && destino.posY != 0) {
					if (piezas.comprobar_posicion(destino.posX, destino.posY, *turno) == true) {
						origen.posX = destino.posX;
						origen.posY = destino.posY;
						destino.posX = destino.posY = 0;
						pieza_selecionada.posX = origen.posX;
						pieza_selecionada.posY = origen.posY;
						actualizarpantalla(opcion_juego , opcion_color, *turno, opcion_graficos);
					}
					else if (piezas.comprobar_movimiento(origen.posX, origen.posY, destino.posX, destino.posY, *turno, piezas) == true) {
						piezas.ejecuta_movimiento(origen.posX, origen.posY, destino.posX, destino.posY, *turno);
						pieza_selecionada.posX = pieza_selecionada.posY = 0;
						origen.posX = origen.posY = 0;
						destino.posX = destino.posY = 0;
						if (*turno == 0)
							*turno = 1;
						else
							*turno = 0;
						casilla_origen = true;
						casilla_destino = false;
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
		if(piezas.comprobar_jaquemate(*turno, piezas) == true)
			cout << "JAQUE MATE" << endl;
		if (piezas.comprobar_ahogado(*turno, piezas) == true)
			cout << "TABLAS" << endl;
	}
}

void Tablero::juego_maquina(int* turno) {
	int turnocontrario = 0;
	if (turno == 0)
		turnocontrario = 1;
	Jugada jugada = IA::analisis_jugada(*turno, piezas);
	piezas.ejecuta_movimiento(jugada.origen_x, jugada.origen_y, jugada.destino_x, jugada.destino_y, *turno);
	if (*turno == 0)
		*turno = 1;
	else
		*turno = 0;
}

void Tablero::dibuja2D(int opcion_juego, int opcion_color, int turno)
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		x_ojo, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);
	// pintamos el título de la pantalla
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/titulo.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(-15, 38, 0);
	glTexCoord2d(1, 1);		glVertex3f(47, 38, 0);
	glTexCoord2d(1, 0);		glVertex3f(47, 46, 0);
	glTexCoord2d(0, 0);		glVertex3f(-15, 46, 0);
	glEnd();

	// pintamos de quien es el turno
	if (turno == 0)
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/turnoblancas.png").id);
	if (turno == 1)
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/turnonegras.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(0, -10, 0);
	glTexCoord2d(1, 1);		glVertex3f(32, -10, 0);
	glTexCoord2d(1, 0);		glVertex3f(32, -4, 0);
	glTexCoord2d(0, 0);		glVertex3f(0, -4, 0);
	glEnd();

	// pintamos los avatares de los usuarios
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/jugadorblancas.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(-19, 30, 0);
	glTexCoord2d(1, 1);		glVertex3f(-7, 30, 0);
	glTexCoord2d(1, 0);		glVertex3f(-7, 35, 0);
	glTexCoord2d(0, 0);		glVertex3f(-19, 35, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/jugadornegras.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(39, 30, 0);
	glTexCoord2d(1, 1);		glVertex3f(51, 30, 0);
	glTexCoord2d(1, 0);		glVertex3f(51, 35, 0);
	glTexCoord2d(0, 0);		glVertex3f(39, 35, 0);
	glEnd();

	if (opcion_juego == 1) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/iconojugadorlocal2.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1);		glVertex3f(-19, 16, 0);
		glTexCoord2d(1, 1);		glVertex3f(-7, 16, 0);
		glTexCoord2d(1, 0);		glVertex3f(-7, 30, 0);
		glTexCoord2d(0, 0);		glVertex3f(-19, 30, 0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/iconojugadorlocal1.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1);		glVertex3f(39, 16, 0);
		glTexCoord2d(1, 1);		glVertex3f(51, 16, 0);
		glTexCoord2d(1, 0);		glVertex3f(51, 30, 0);
		glTexCoord2d(0, 0);		glVertex3f(39, 30, 0);
		glEnd();
	}
	if (opcion_juego == 2) {
		if (opcion_color == 1) {
			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/iconojugadorlocal2.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(-19, 16, 0);
			glTexCoord2d(1, 1);		glVertex3f(-7, 16, 0);
			glTexCoord2d(1, 0);		glVertex3f(-7, 30, 0);
			glTexCoord2d(0, 0);		glVertex3f(-19, 30, 0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/iconojugadormaquina.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(39, 16, 0);
			glTexCoord2d(1, 1);		glVertex3f(51, 16, 0);
			glTexCoord2d(1, 0);		glVertex3f(51, 30, 0);
			glTexCoord2d(0, 0);		glVertex3f(39, 30, 0);
			glEnd();
		}
		if (opcion_color == 2) {
			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/iconojugadormaquina.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(-19, 16, 0);
			glTexCoord2d(1, 1);		glVertex3f(-7, 16, 0);
			glTexCoord2d(1, 0);		glVertex3f(-7, 30, 0);
			glTexCoord2d(0, 0);		glVertex3f(-19, 30, 0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/iconojugadorlocal1.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(39, 16, 0);
			glTexCoord2d(1, 1);		glVertex3f(51, 16, 0);
			glTexCoord2d(1, 0);		glVertex3f(51, 30, 0);
			glTexCoord2d(0, 0);		glVertex3f(39, 30, 0);
			glEnd();
		}
	}

	// DIBUJO DEL TABLERO
	// creamos los cuadrados de colores del tablero de las casillas que no están ocupadas
	for (int j = 1; j < 9; j++) {
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

	if ((pieza_selecionada.posX != 0) && (pieza_selecionada.posY != 0)) {
		// marcamos todos los posibles destinos de la pieza seleccionada
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				posible_destino = piezas.comprobar_movimiento(pieza_selecionada.posX, pieza_selecionada.posY, i, j, turno, piezas);
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
	piezas.dibuja2D(pieza_selecionada.posX, pieza_selecionada.posY);
}

void Tablero::dibuja3D()
{
	gluLookAt(-70, 65, 55,  // posicion del ojo
		24, 0, 24,      // hacia que punto mira  (0,0,0) 
		0, 1, 0);      // definimos hacia arriba (eje Y)  

	// DIBUJO DEL TABLERO
	// creamos los cuadrados de colores del tablero
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			if (j == 0 || j == 9 || i == 0 || i == 9)
				glColor3ub(153, 102, 51);
			else if (j % 2 == 1) {//Bucle para las coordenadas y
				if (i % 2 == 1)//Bucle para las coordenadas x
					glColor3ub(0, 0, 204);
				else
					glColor3ub(102, 204, 255);
			}
			else {
				if (i % 2 == 0)
					glColor3ub(0, 0, 204);
				else
					glColor3ub(102, 204, 255);
			}
			if(pieza_selecionada.posX != 0 && pieza_selecionada.posY != 0 && pieza_selecionada.posX == j && pieza_selecionada.posY == i)
				glColor3ub(0, 255, 0);
			glTranslatef(i * 6 - 3, -3, j * 6 - 3);
			glutSolidCube(6);
			glTranslatef(- i * 6 + 3, 3, - j * 6 + 3);
		}
	}

	// DIBUJAMOS LAS PIEZAS
	piezas.dibuja3D();
}


void Tablero::actualizarpantalla(int opcion_juego, int opcion_color, int turno, int opcion_graficos) {
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (opcion_graficos == 1)
		dibuja2D(opcion_juego, opcion_color, turno);
	if (opcion_graficos == 2)
		dibuja3D();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

int Tablero::coordenadaX(int x) {
	if (x >= 306 && x <= 355)
		return 1;
	else if (x >= 356 && x <= 404)
		return 2;
	else if (x >= 405 && x <= 452)
		return 3;
	else if (x >= 453 && x <= 501)
		return 4;
	else if (x >= 502 && x <= 549)
		return 5;
	else if (x >= 550 && x <= 597)
		return 6;
	else if (x >= 598 && x <= 645)
		return 7;
	else if (x >= 646 && x <= 694)
		return 8;
	else
		return 0;
}

int Tablero::coordenadaY(int y) {
	if (y >= 191 && y <= 238)
		return 8;
	else if (y >= 239 && y <= 282)
		return 7;
	else if (y >= 283 && y <= 327)
		return 6;
	else if (y >= 328 && y <= 373)
		return 5;
	else if (y >= 374 && y <= 417)
		return 4;
	else if (y >= 418 && y <= 463)
		return 3;
	else if (y >= 464 && y <= 508)
		return 2;
	else if (y >= 509 && y <= 553)
		return 1;
	else
		return 0;
}
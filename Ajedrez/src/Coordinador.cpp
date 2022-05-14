#include "Coordinador.h"

Coordinador::Coordinador() 
{
	turno = 0; // siempre empiezan jugando las blancas
	opcion_juego = 0;
	opcion_color = 0;
	opcion_graficos = 0;
	estado = INSTRUCCIONES;
}

Coordinador::~Coordinador() {}

void Coordinador::partida() 
{
	if (estado == INSTRUCCIONES) 
	{
		opcion_juego = 0;
		opcion_color = 0;
		opcion_graficos = 0;
		tablero.comienzo_partida();
	}
	if (estado == JUEGO) 
	{
		if (opcion_juego == 1)
			tablero.juego_local(&turno, opcion_graficos);
		if (opcion_juego == 2) 
		{
			if (opcion_color == 1) 
			{
				if (turno == 0)
					tablero.juego_local(&turno, opcion_graficos);
				if (turno == 1)
					tablero.juego_local(&turno, opcion_graficos); // aqui hay que poner el juego de la maquina
			}
			if (opcion_color == 2) {
				if (turno == 0)
					tablero.juego_local(&turno, opcion_graficos); // aqui hay que poner el juego de la maquina
				if (turno == 1)
					tablero.juego_local(&turno, opcion_graficos);
			}
		}
	}
}

void Coordinador::dibuja() {
	if (estado == INSTRUCCIONES)
		dibujainstrucciones();
	if (estado == MENU)
		dibujaelecciones();
	if (estado == JUEGO) {
		if (opcion_graficos == 1)
			tablero.dibuja2D(turno);
		if (opcion_graficos == 2)
			tablero.dibuja3D();
	}
}

void Coordinador::dibujainstrucciones() {
	gluLookAt(1.3, 0.5, 13,  // posicion del ojo
		1.3, 0.5, 0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0);      // definimos hacia arriba (eje Y) 

	ETSIDI::setTextColor(255, 255, 255);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 27);
	ETSIDI::printxy("BIENVENIDOS A CHESS_CON_CHEES", -4, 3);

	ETSIDI::setFont("fuentes/Bitwise.ttf", 21);
	ETSIDI::printxy("Bienvenidos a nuestro juego de ajedrez. Antes de", -4, 2);
	ETSIDI::printxy("comenzar a jugar hay que seleccionar los modos de", -4, 1);
	ETSIDI::printxy("juego. Haga click en la flecha para continuar.", -4, 0);

	glColor3ub(255, 255, 255);
	glBegin(GL_POLYGON);
	glVertex3f(4.2, -0.7, -0.1);
	glVertex3f(4.2, -2, -0.1);
	glVertex3f(6.6, -2, -0.1);
	glVertex3f(6.6, -0.7, -0.1);
	glEnd();
	glColor3ub(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(4.4, -1.1, 0.0f);
	glVertex3f(4.4, -1.6, 0.0f);
	glVertex3f(5.4, -1.6, 0.0f);
	glVertex3f(5.4, -1.1, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(5.4, -0.85, 0.0f);
	glVertex3f(5.4, -1.85, 0.0f);
	glVertex3f(6.4, -1.35, 0.0f);
	glEnd();

	ETSIDI::setTextColor(255, 0, 0);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 23);
	ETSIDI::printxy("ADVERTENCIA MODO 3D", -4, -1);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 17);
	ETSIDI::printxy("TIEMPOS DE CARGA MUY ALTOS", -4, -2);
}

void Coordinador::dibujaelecciones() {
	gluLookAt(1.3, 0.5, 13,  // posicion del ojo
		1.3, 0.5, 0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0);      // definimos hacia arriba (eje Y) 

	// SELECCIÓN DEL MODO DE JUEGO
	ETSIDI::setTextColor(255, 255, 255);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 29);
	ETSIDI::printxy("SELECCIONE EL MODO DE JUEGO", -4, 3);

	glColor3ub(255, 255, 255);
	if(opcion_juego == 1)
		glColor3ub(0, 200, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-4.2, 2.5, -0.1);
	glVertex3f(-4.2, 1.8, -0.1);
	glVertex3f(0.4, 1.8, -0.1);
	glVertex3f(0.4, 2.5, -0.1);
	glEnd();
	glColor3ub(255, 255, 255);
	if (opcion_juego == 2)
		glColor3ub(0, 200, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1.8, 2.5, 0);
	glVertex3f(1.8, 1.8, 0);
	glVertex3f(6.4, 1.8, 0);
	glVertex3f(6.4, 2.5, 0);
	glEnd();

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 17);
	ETSIDI::printxy("JUGADOR VS JUGADOR", -4, 2);
	ETSIDI::printxy("JUGADOR VS MAQUINA", 2, 2);

	// SELECCIÓN DEL COLOR DE JUEGO
	if (opcion_juego == 2) {
		ETSIDI::setTextColor(255, 255, 255);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 28);
		ETSIDI::printxy("SELECCIONE EL COLOR DE JUEGO", -4, 1);

		glColor3ub(255, 255, 255);
		if (opcion_color == 1)
			glColor3ub(0, 200, 0);
		glBegin(GL_POLYGON);
		glVertex3f(-4.2, 0.5, -0.1);
		glVertex3f(-4.2, -0.2, -0.1);
		glVertex3f(0.2, -0.2, -0.1);
		glVertex3f(0.2, 0.5, -0.1);
		glEnd();
		glColor3ub(255, 255, 255);
		if (opcion_color == 2)
			glColor3ub(0, 200, 0);
		glBegin(GL_POLYGON);
		glVertex3f(1.8, 0.5, 0);
		glVertex3f(1.8, -0.2, 0);
		glVertex3f(6, -0.2, 0);
		glVertex3f(6, 0.5, 0);
		glEnd();

		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 17);
		ETSIDI::printxy("JUEGO CON BLANCAS", -4, 0);
		ETSIDI::printxy("JUEGO CON NEGRAS", 2, 0);
	}

	// SELECCIÓN DE LOS GRÁFICOS
	if (opcion_juego == 1 || (opcion_juego == 2 && opcion_color != 0)) {
		ETSIDI::setTextColor(255, 255, 255);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 29);
		ETSIDI::printxy("SELECCIONE EL MODO GRAFICO", -4, -1);

		glColor3ub(255, 255, 255);
		if (opcion_graficos == 1)
			glColor3ub(0, 200, 0);
		glBegin(GL_POLYGON);
		glVertex3f(-4.2, -1.5, -0.1);
		glVertex3f(-4.2, -2.2, -0.1);
		glVertex3f(0.2, -2.2, -0.1);
		glVertex3f(0.2, -1.5, -0.1);
		glEnd();
		glColor3ub(255, 255, 255);
		if (opcion_graficos == 2)
			glColor3ub(0, 200, 0);
		glBegin(GL_POLYGON);
		glVertex3f(1.8, -1.5, 0);
		glVertex3f(1.8, -2.2, 0);
		glVertex3f(6, -2.2, 0);
		glVertex3f(6, -1.5, 0);
		glEnd();

		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 19);
		ETSIDI::printxy("MODO GRAFICO 2D", -4, -2);
		ETSIDI::printxy("MODO GRAFICO 3D", 2, -2);
		ETSIDI::setTextColor(255, 255, 255);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 21);
		ETSIDI::printxy("Juego por raton", -4, -3);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 20);
		ETSIDI::printxy("Juego por teclado", 2, -3);
	}
}

int Coordinador::getEstado() {
	if (estado == INSTRUCCIONES)
		return 1;
	if (estado == MENU)
		return 2;
	if (estado == JUEGO)
		return 3;
}

void Coordinador::opcionSeleccionada(int x, int y) {
	if (estado == INSTRUCCIONES)
		if (x >= 581 && x <= 733 && y >= 439 && y <= 533)
			estado = MENU;
	if (estado == MENU) {
		if (x >= 54 && x <= 344 && y >= 201 && y <= 255) {
			opcion_juego = 1;
		}
		if (x >= 432 && x <= 724 && y >= 201 && y <= 225) {
			opcion_juego = 2;
		}
		if (opcion_juego == 2) { // el color solamente lo elegimos en el modo JUGADOR VS MAQUINA
			if (x >= 54 && x <= 330 && y >= 350 && y <= 400) {
				opcion_color = 1;
			}
			if (x >= 432 && x <= 699 && y >= 350 && y <= 400) {
				opcion_color = 2;
			}
		}
		if (opcion_juego == 1 || (opcion_juego == 2 && opcion_color!=0)) {
			if (x >= 54 && x <= 330 && y >= 497 && y <= 548) {
				opcion_graficos = 1;
				estado = JUEGO;
			}
			if (x >= 432 && x <= 697 && y >= 497 && y <= 548) {
				opcion_graficos = 2;
				estado = JUEGO;
			}
		}
	}
}
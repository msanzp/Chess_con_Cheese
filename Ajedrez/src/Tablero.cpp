#include "Tablero.h"
#include "freeglut.h"
#include <math.h>
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
	x_ojo=16;
	y_ojo=16;
	z_ojo=50;

	//creamos los reyes
	Rey* reyblanco = new Rey(5, 1, 'w');
	Rey* reynegro = new Rey(5, 8, 'b');
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
	Torre* torreblanca1 = new Torre(1, 1, 'w');
	Torre* torreblanca2 = new Torre(8, 1, 'w');
	Torre* torrenegra1 = new Torre(8, 8, 'b');
	Torre* torrenegra2 = new Torre(1, 8, 'b');
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
}

void Tablero::ejecutar_movimiento()
{
	int origen_x, origen_y; // para determinar las coordenadas de la pieza a ser movida
	int destino_x, destino_y; // para determinar las coordenadas de la posición de destino
	bool posicion_ocupada; // para determinar si en la casilla de origen hay pieza
	bool movimiento_valido; // sirve para saber si la pieza escogida se puede mover a la posición indicada
	// introducimos la casilla donde se encuentra la pieza que queremos mover
	do {
		// introducimos la casilla a donde queremos mover nuestra pieza
		do {
			cout << "Posición de la pieza que desea mover:" << endl;
			cin >> origen_x >> origen_y;
			posicion_ocupada = piezas.comprobar_posicion(origen_x, origen_y);
		} while (posicion_ocupada == false); // el bucle se repite si en la casilla introducida no hay pieza
		// introducimos la casilla a donde queremos mover nuestra pieza
		cout << "Posición de destino de la pieza:" << endl;
		cin >> destino_x >> destino_y;
		movimiento_valido = piezas.comprobar_movimiento(origen_x, origen_y, destino_x, destino_y);
	} while (movimiento_valido == false); // el bucle se repite si el movimiento no es válido
	piezas.ejecuta_movimiento(origen_x, origen_y, destino_x, destino_y);
	cout << "Movimiento realizado" << endl;
}

void Tablero::mueve()
{

}

void Tablero::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		16, 16, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	//aqui es donde hay que poner el codigo de dibujo
	//dibujo del tablero
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);
	for (int i = 0; i < 9; i++)
	{
		glVertex3f(i * 4, 0, 0);
		glVertex3f(i * 4, 32, 0);
		glVertex3f(0, i * 4, 0);
		glVertex3f(32, i * 4, 0);
	}
	glEnd();
	glEnable(GL_LIGHTING);
	piezas.dibuja();
}
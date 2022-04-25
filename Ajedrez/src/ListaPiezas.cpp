#include "ListaPiezas.h"

using namespace std;

ListaPiezas::ListaPiezas(){
	numeroreyes = 0;
	numeroreinas = 0;
	numerotorres = 0;
	numerocaballos = 0;
	numeroalfiles = 0;
	numeropeones = 0;
	for (int i = 0; i < MAX_PIEZAS; i++) {
		reyes[i] = 0;
		reinas[i] = 0;
		torres[i] = 0;
		caballos[i] = 0;
		alfiles[i] = 0;
		peones[i] = 0;
	}
	//Inicializacion de posiciones. 0 es que esa posicion no tiene pieza.
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			posiciones[i][j].presencia = false;
	}
}

ListaPiezas::~ListaPiezas() {}

// dibuja todas las piezas presentes en el tablero
void ListaPiezas::dibuja(){
	for (int i = 0; i < numeroreyes; i++)
		reyes[i]->dibuja();
	for (int i = 0; i < numeroreinas; i++)
		reinas[i]->dibuja();
	for (int i = 0; i < numerotorres; i++)
		torres[i]->dibuja();
	for (int i = 0; i < numerocaballos; i++)
		caballos[i]->dibuja();
	for (int i = 0; i < numeroalfiles; i++)
		alfiles[i]->dibuja();
	for (int i = 0; i < numeropeones; i++)
		peones[i]->dibuja();
}
//Indica que posiciones estan con piezas y el color de estas
void ListaPiezas::introducir_posiciones() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < numeroreyes; k++) {
				if ((reyes[k]->getX() == i) && (reyes[k]->getY() == j))
					posiciones[i][j] = { true,reyes[k]->getColor() };	
			}
			for (int k = 0; k < numeroreinas; k++) {
				if (reinas[k]->getX() == i && reinas[k]->getY() == j)
					posiciones[i][j] = { true,reinas[k]->getColor() };
			}
			for (int k = 0; k < numerotorres; k++) {
				if (torres[k]->getX() == i && torres[k]->getY() == j)
					posiciones[i][j] = { true,torres[k]->getColor() };
			}
			for (int k = 0; k < numerocaballos; k++) {
				if (caballos[k]->getX() == i && caballos[k]->getY() == j)
					posiciones[i][j] = { true,caballos[k]->getColor() };
			}
			for (int k = 0; k < numeroalfiles; k++) {
				if (alfiles[k]->getX() == i && alfiles[k]->getY() == j)
					posiciones[i][j] = { true,alfiles[k]->getColor() };
			}
			for (int k = 0; k < numeropeones; k++) {
				if (peones[k]->getX() == i && peones[k]->getY() == j)
					posiciones[i][j] = { true,peones[k]->getColor() };
			}
		}
	}
}
// esta funcion sirve para determinar si una determinada casilla está ocupada por alguna pieza
bool ListaPiezas::comprobar_posicion(int x, int y){
	introducir_posiciones();
	bool casilla_ocupada = false;
	//Se comprueba la posicion utilizando la estructura posicion
	if (posiciones[x][y].presencia==true)
		casilla_ocupada=true;
	/*for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == x && reyes[i]->getY() == y)
			casilla_ocupada = true;
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getX() == x && reinas[i]->getY() == y)
			casilla_ocupada = true;
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getX() == x && torres[i]->getY() == y)
			casilla_ocupada = true;
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getX() == x && caballos[i]->getY() == y)
			casilla_ocupada = true;
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getX() == x && alfiles[i]->getY() == y)
			casilla_ocupada = true;
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getX() == x && peones[i]->getY() == y)
			casilla_ocupada = true;
	}*/
	return casilla_ocupada;
}

// esta función sirve para determinar si podemos mover una pieza de una casilla a otra
bool ListaPiezas::comprobar_movimiento(int origen_x, int origen_y, int destino_x, int destino_y) {
	bool movimiento_valido = false;
	bool trayectoria_valida = false;
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == origen_x && reyes[i]->getY() == origen_y) {
			movimiento_valido = reyes[i]->comprobar_movimiento(destino_x, destino_y); // la forma de moverse de la pieza es la adecuada
			// si la forma de moverse es la adecuada, comprobamos que el rey no se encuentre en jaque en la posición de destino
			if (movimiento_valido == true) {

			}
		}
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getX() == origen_x && reinas[i]->getY() == origen_y) {
			movimiento_valido = reinas[i]->comprobar_movimiento(destino_x, destino_y);  // la forma de moverse de la pieza es la adecuada
			// si la forma de moverse es la adecuada, comprobamos que no hay piezas en medio durante el recorrido
			if (movimiento_valido == true)
				trayectoria_valida = comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y);
			if (trayectoria_valida == true)
				movimiento_valido = false;
		}
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getX() == origen_x && torres[i]->getY() == origen_y) {
			movimiento_valido = torres[i]->comprobar_movimiento(destino_x, destino_y);  // la forma de moverse de la pieza es la adecuada
			// si la forma de moverse es la adecuada, comprobamos que no hay piezas en medio durante el recorrido
			if (movimiento_valido == true)
				trayectoria_valida = comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y);
			if (trayectoria_valida == true)//Esto no se deberia de cumplir con piezas de distinto color, si coincide alguna pieza en la trayectoria se puede atrapar
				movimiento_valido = false;
		}
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getX() == origen_x && caballos[i]->getY() == origen_y) {
			movimiento_valido = caballos[i]->comprobar_movimiento(destino_x, destino_y); // la forma de moverse de la pieza es la adecuada
			if (movimiento_valido == true)
				trayectoria_valida = comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y);
			if (trayectoria_valida == true)//Esto no se deberia de cumplir con piezas de distinto color, si coincide alguna pieza en la trayectoria se puede atrapar
				movimiento_valido = false;
		}

		for (int i = 0; i < numeroalfiles; i++) {
			if (alfiles[i]->getX() == origen_x && alfiles[i]->getY() == origen_y) {
				movimiento_valido = alfiles[i]->comprobar_movimiento(destino_x, destino_y); // la forma de moverse de la pieza es la adecuada
				// si la forma de moverse es la adecuada, comprobamos que no hay piezas en medio durante el recorrido
				if (movimiento_valido == true)
					trayectoria_valida = comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y);
				if (trayectoria_valida == true)
					movimiento_valido = false;
			}
		}
		for (int i = 0; i < numeropeones; i++) {
			if (peones[i]->getX() == origen_x && peones[i]->getY() == origen_y) {
				movimiento_valido = peones[i]->comprobar_movimiento(destino_x, destino_y); // la forma de moverse de la pieza es la adecuada
				// si la forma de moverse es la adecuada, comprobamos que no hay piezas en medio durante el recorrido
				if (movimiento_valido == true) {

				}
			}
		}
		return movimiento_valido;
	}
}

// esta función sirve para determinar si hay piezas o no en medio de la trayectoria, devuelve false si la trayectoria esta libre
bool ListaPiezas::comprobar_trayectoria(int origen_x, int origen_y, int destino_x, int destino_y) {
	bool trayectoria_ocupada = false;
	if (origen_x == destino_x) // se trata de un movimiento horizontal
	{
		if (destino_y > origen_y) {
			for (int i = origen_y + 1; i < destino_y; i++)
				if (trayectoria_ocupada==false)
					trayectoria_ocupada = comprobar_posicion(origen_x,i);

		}
		if (origen_y > destino_y) {
			for (int i = destino_y + 1; i < origen_y; i++)
				if (trayectoria_ocupada == false)
					trayectoria_ocupada = comprobar_posicion(origen_x, i);
		}
	}
	if (origen_y == destino_y) // se trata de un movimiento vertical
	{
		if (destino_x > origen_x) {
			for (int i = origen_x + 1; i < destino_x; i++)
				if (trayectoria_ocupada == false)
					trayectoria_ocupada = comprobar_posicion(i, origen_y);
		}
		if (origen_x > destino_x) {
			for (int i = destino_x + 1; i < origen_x; i++)
				if (trayectoria_ocupada == false)
					trayectoria_ocupada = comprobar_posicion(i, origen_y);
		}
	}
	if ((origen_x != destino_x) && (origen_y != destino_y)) // se trata de un movimiento diagonal
	{
		int diferencia = fabs(origen_x - destino_x);;
		if ((origen_x < destino_x)&& (origen_y < destino_y)) {
			for (int i = 1; i < diferencia; i++)
				if (trayectoria_ocupada == false)
					trayectoria_ocupada = comprobar_posicion(origen_x + i, origen_y + i);
		}
		if ((origen_x < destino_x) && (origen_y > destino_y)) {
			for (int i = 1; i < diferencia; i++)
				if (trayectoria_ocupada == false)
					trayectoria_ocupada = comprobar_posicion(origen_x + i, origen_y - i);
		}
		if ((origen_x > destino_x) && (origen_y > destino_y)) {
			for (int i = 1; i < diferencia; i++)
				if (trayectoria_ocupada == false)
					trayectoria_ocupada = comprobar_posicion(origen_x - i, origen_y - i);
		}
		if ((origen_x > destino_x) && (origen_y < destino_y)) {
			for (int i = 1; i < diferencia; i++)
				if (trayectoria_ocupada == false)
					trayectoria_ocupada = comprobar_posicion(origen_x - i, origen_y + i);
		}
	}
	//Se tiene que comprobar si la posicion de destino, si esta ocupada por una misma pieza del mismo color el movimiento no es posible
	if (posiciones[destino_x][destino_y].color == posiciones[origen_x][origen_y].color)
		trayectoria_ocupada = true;
	return trayectoria_ocupada;
}

// esta función sirve para ejecutar el movimiento, eliminando la pieza comica (si hay) y moviendo la pieza seleccionada
void ListaPiezas::ejecuta_movimiento(int origen_x, int origen_y, int destino_x, int destino_y) {
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == destino_x && reyes[i]->getY() == destino_y)
			eliminar(reyes[i]);
		if (reyes[i]->getX() == origen_x && reyes[i]->getY() == origen_y) {
			reyes[i]->setX(destino_x);
			reyes[i]->setY(destino_y);
		}
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getX() == destino_x && reinas[i]->getY() == destino_y)
			eliminar(reinas[i]);
		if (reinas[i]->getX() == origen_x && reinas[i]->getY() == origen_y) {
			reinas[i]->setX(destino_x);
			reinas[i]->setY(destino_y);
		}
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getX() == destino_x && torres[i]->getY() == destino_y)
			eliminar(torres[i]);
		if (torres[i]->getX() == origen_x && torres[i]->getY() == origen_y) {
			torres[i]->setX(destino_x);
			torres[i]->setY(destino_y);
		}
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getX() == destino_x && caballos[i]->getY() == destino_y)
			eliminar(caballos[i]);
		if (caballos[i]->getX() == origen_x && caballos[i]->getY() == origen_y) {
			caballos[i]->setX(destino_x);
			caballos[i]->setY(destino_y);
		}
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getX() == destino_x && alfiles[i]->getY() == destino_y)
			eliminar(alfiles[i]);
		if (alfiles[i]->getX() == origen_x && alfiles[i]->getY() == origen_y) {
			alfiles[i]->setX(destino_x);
			alfiles[i]->setY(destino_y);
		}
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getX() == destino_x && peones[i]->getY() == destino_y)
			eliminar(peones[i]);
		if (peones[i]->getX() == origen_x && peones[i]->getY() == origen_y) {
			peones[i]->setX(destino_x);
			peones[i]->setY(destino_y);
		}
	}
}

// esta funcion sirve para determinar si el rey se encuentra en jaque
// devuelve 0 si no está en jaque, 1 si es jaque y 2 si es jaque mate
int ListaPiezas::comprobar_jaque(Rey* k) {
	return 0;
}

bool ListaPiezas::agregar(Rey* k){
	if (numeroreyes < MAX_PIEZAS)
		reyes[numeroreyes++] = k; // último puesto sin rellenar 
	else
		return false; // capacidad máxima alcanzada 
	return true;
}

bool ListaPiezas::agregar(Reina* q){
	if (numeroreinas < MAX_PIEZAS)
		reinas[numeroreinas++] = q; // último puesto sin rellenar 
	else
		return false; // capacidad máxima alcanzada 
	return true;
}

bool ListaPiezas::agregar(Torre* t){
	if (numerotorres < MAX_PIEZAS)
		torres[numerotorres++] = t; // último puesto sin rellenar 
	else
		return false; // capacidad máxima alcanzada 
	return true;
}

bool ListaPiezas::agregar(Caballo* c){
	if (numerocaballos < MAX_PIEZAS)
		caballos[numerocaballos++] = c; // último puesto sin rellenar 
	else
		return false; // capacidad máxima alcanzada 
	return true;
}

bool ListaPiezas::agregar(Alfil* a){
	if (numeroalfiles < MAX_PIEZAS)
		alfiles[numeroalfiles++] = a; // último puesto sin rellenar 
	else
		return false; // capacidad máxima alcanzada 
	return true;
}

bool ListaPiezas::agregar(Peon* p){
	if (numeropeones < MAX_PIEZAS)
		peones[numeropeones++] = p; // último puesto sin rellenar 
	else
		return false; // capacidad máxima alcanzada 
	return true;
}

void ListaPiezas::eliminar(Rey* k) {
	for (int j = 0; j < numeroreyes; j++)
		if (reyes[j] == k)
		{
			delete reyes[j];
			numeroreyes--;
			for (int i = j; i < numeroreyes; i++)
				reyes[i] = reyes[i + 1];
		}
}

void ListaPiezas::eliminar(Reina* q) {
	for (int j = 0; j < numeroreinas; j++)
		if (reinas[j] == q)
		{
			delete reinas[j];
			numeroreinas--;
			for (int i = j; i < numeroreinas; i++)
				reinas[i] = reinas[i + 1];
		}
}

void ListaPiezas::eliminar(Torre* t) {
	for (int j = 0; j < numerotorres; j++)
		if (torres[j] == t)
		{
			delete torres[j];
			numerotorres--;
			for (int i = j; i < numerotorres; i++)
				torres[i] = torres[i + 1];
		}
}

void ListaPiezas::eliminar(Caballo* c) {
	for (int j = 0; j < numerocaballos; j++)
		if (caballos[j] == c)
		{
			delete caballos[j];
			numerocaballos--;
			for (int i = j; i < numerocaballos; i++)
				caballos[i] = caballos[i + 1];
		}
}

void ListaPiezas::eliminar(Alfil* a) {
	for (int j = 0; j < numeroalfiles; j++)
		if (alfiles[j] == a)
		{
			delete alfiles[j];
			numeroalfiles--;
			for (int i = j; i < numeroalfiles; i++)
				alfiles[i] = alfiles[i + 1];
		}
}

void ListaPiezas::eliminar(Peon* p) {
	for (int j = 0; j < numeropeones; j++)
		if (peones[j] == p)
		{
			delete peones[j];
			numeropeones--;
			for (int i = j; i < numeropeones; i++)
				peones[i] = peones[i + 1];
		}
}

void ListaPiezas::destruirContenido() {
	for (int i = 0; i < numeroreyes; i++) // destrucción de reyess 
		delete reyes[i];
	for (int i = 0; i < numeroreyes; i++) // destrucción de reinas
		delete reinas[i];
	for (int i = 0; i < numeroreyes; i++) // destrucción de torres
		delete torres[i];
	for (int i = 0; i < numeroreyes; i++) // destrucción de caballos
		delete caballos[i];
	for (int i = 0; i < numeroreyes; i++) // destrucción de alfiles
		delete alfiles[i];
	for (int i = 0; i < numeroreyes; i++) // destrucción de peones
		delete peones[i];
	numeroreyes = 0; // inicializa lista 
	numeroreinas = 0; // inicializa lista
	numerotorres = 0; // inicializa lista
	numerocaballos = 0; // inicializa lista
	numeroalfiles = 0; // inicializa lista
	numeropeones = 0; // inicializa lista
}

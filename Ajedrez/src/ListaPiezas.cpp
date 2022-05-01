#include "ListaPiezas.h"
#include <iostream>
#include <math.h>

using namespace std;

ListaPiezas::ListaPiezas(){
	numero_jugadas = 1;
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
}

ListaPiezas::ListaPiezas(const ListaPiezas& copia) {
	numero_jugadas = copia.numero_jugadas;
	numeroreyes = 0;
	numeroreinas = 0;
	numerotorres = 0;
	numerocaballos = 0;
	numeroalfiles = 0;
	numeropeones = 0;
	for (int i = 0; i < copia.numeroreyes; i++) {
		Rey* rey = new Rey(copia.reyes[i]->getX(), copia.reyes[i]->getY(), copia.reyes[i]->getColor(), copia.reyes[i]->getPrimerMovimiento());
		agregar(rey);
	}
	for (int i = 0; i < copia.numeroreinas; i++) {
		Reina* reina = new Reina(copia.reinas[i]->getX(), copia.reinas[i]->getY(), copia.reinas[i]->getColor());
		agregar(reina);
	}
	for (int i = 0; i < copia.numerotorres; i++) {
		Torre* torre = new Torre(copia.torres[i]->getX(), copia.torres[i]->getY(), copia.torres[i]->getColor(), copia.torres[i]->getPrimerMovimiento());
		agregar(torre);
	}
	for (int i = 0; i < copia.numerocaballos; i++) {
		Caballo* caballo = new Caballo(copia.caballos[i]->getX(), copia.caballos[i]->getY(), copia.caballos[i]->getColor());
		agregar(caballo);
	}
	for (int i = 0; i < copia.numeroalfiles; i++) {
		Alfil* alfil = new Alfil(copia.alfiles[i]->getX(), copia.alfiles[i]->getY(), copia.alfiles[i]->getColor());
		agregar(alfil);
	}
	for (int i = 0; i < copia.numeropeones; i++) {
		Peon* peon = new Peon(copia.peones[i]->getX(), copia.peones[i]->getY(), copia.peones[i]->getColor());
		agregar(peon);
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

// esta funcion sirve para determinar si una determinada casilla est� ocupada por por una pieza de un color especifico
bool ListaPiezas::comprobar_posicion(int x, int y, int turno){
	char color = 'w';
	if (turno == 1)
		color = 'b';

	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == x && reyes[i]->getY() == y && reyes[i]->getColor() == color)
			return true;
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getX() == x && reinas[i]->getY() == y && reinas[i]->getColor() == color)
			return true;
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getX() == x && torres[i]->getY() == y && torres[i]->getColor() == color)
			return true;
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getX() == x && caballos[i]->getY() == y && caballos[i]->getColor() == color)
			return true;
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getX() == x && alfiles[i]->getY() == y && alfiles[i]->getColor() == color)
			return true;
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getX() == x && peones[i]->getY() == y && peones[i]->getColor() == color)
			return true;
	}
	return false;
}

// esta funcion sirve para determinar si una determinada casilla est� ocupada por alguna pieza
bool ListaPiezas::comprobar_posicion(int x, int y){
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == x && reyes[i]->getY() == y)
			return true;
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getX() == x && reinas[i]->getY() == y)
			return true;
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getX() == x && torres[i]->getY() == y)
			return true;
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getX() == x && caballos[i]->getY() == y)
			return true;
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getX() == x && alfiles[i]->getY() == y)
			return true;
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getX() == x && peones[i]->getY() == y)
			return true;
	}
	return false;
}

// esta funci�n sirve para determinar si podemos mover una pieza de una casilla a otra
bool ListaPiezas::comprobar_movimiento(int origen_x, int origen_y, int destino_x, int destino_y, int turno){
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == origen_x && reyes[i]->getY() == origen_y){
			// primero comprobamos que la forma de moverse corresponde con la del rey
			if (reyes[i]->comprobar_movimiento(destino_x, destino_y) == true) {
				// si la forma de moverse es la adecuada, comprobamos que no hay piezas de su mismo color en la casilla de destino
				if (comprobar_posicion(destino_x, destino_y, turno) == true)
					return false;
				// compruebo que en la posicion de destino no se encuentra en jaque
				if (comprobar_jaque(destino_x, destino_y, turno) == true)
					return false;
			}
			else
				return false;
			return true;
		}
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getX() == origen_x && reinas[i]->getY() == origen_y) {
			// primero comprobamos que la forma de moverse corresponde con la de la reina
			if (reinas[i]->comprobar_movimiento(destino_x, destino_y) == true) {
				// si la forma de moverse es la adecuada, comprobamos que no hay piezas en medio de la trayectoria y hay piezas de su mismo color en la casilla de destino
				if (comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y, turno) == true)
					return false;
			}
			else
				return false;
			return true;
		}
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getX() == origen_x && torres[i]->getY() == origen_y) {
			// primero comprobamos que la forma de moverse corresponde con la de la torre
			if (torres[i]->comprobar_movimiento(destino_x, destino_y) == true) {
				// si la forma de moverse es la adecuada, comprobamos que no hay piezas en medio de la trayectoria y hay piezas de su mismo color en la casilla de destino
				if (comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y, turno) == true)
					return false;
			}
			else
				return false;
			return true;
		}	
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getX() == origen_x && caballos[i]->getY() == origen_y) {
			// primero comprobamos que la forma de moverse corresponde con la de la torre
			if (caballos[i]->comprobar_movimiento(destino_x, destino_y) == true) {
				// si la forma de moverse es la adecuada, comprobamos que no hay piezas de su mismo color en la casilla de destino
				if (comprobar_posicion(destino_x, destino_y, turno) == true)
					return false;
			}
			else
				return false;
			return true;
		}
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getX() == origen_x && alfiles[i]->getY() == origen_y) {
			// primero comprobamos que la forma de moverse corresponde con la de la torre
			if (alfiles[i]->comprobar_movimiento(destino_x, destino_y) == true) {
				// si la forma de moverse es la adecuada, comprobamos que no hay piezas en medio de la trayectoria y hay piezas de su mismo color en la casilla de destino
				if (comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y, turno) == true)
					return false;
			}
			else
				return false;
			return true;
		}
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getX() == origen_x && peones[i]->getY() == origen_y) {
			int variaciony = 0;
			if (peones[i]->getColor() == 'w')
				variaciony = destino_y - origen_y;
			else
				variaciony = origen_y - destino_y;

			int turno1; // esta variable sirve para comer en diagonal una pieza del otro jugador
			if (turno == 0)
				turno1 = 1;
			else
				turno1 = 0;

			// si se mueve hacia adelante
			if (origen_x == destino_x) {
				if (peones[i]->comprobar_movimiento(destino_x, destino_y) == true) {
					if (comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y, turno1) == true)
						return false;
				}
				else
					return false;
				return true;
			}
			// si se mueve de lado para comer
			else if (fabs(origen_x - destino_x) == 1) {
				// en primer lugar ejecutamos el movimiento normal de comer en diagonal
				if (variaciony == 1 && comprobar_posicion(destino_x, destino_y, turno1) == true)
					return true;
				// tras ello, ejecutamos la jugada de "comer al paso"
				else if (comprobar_comeralpaso(origen_x, origen_y, destino_x, destino_y, turno, *peones[i]) == true)
					return true;
				else
					return false;
			}
			else
				return false;
		}
	}
}

// esta funci�n sirve para determinar si hay piezas o no en medio de la trayectoria, devuelve false si la trayectoria esta libre
bool ListaPiezas::comprobar_trayectoria(int origen_x, int origen_y, int destino_x, int destino_y, int turno) {
	// lo primero que hacemos es comprobar que en la posici�n de destino no hay ficha de mi mismo color
	if(comprobar_posicion(destino_x, destino_y, turno) == true)
		return true;
	// tras ello comprobamos que no hay fichas en medio de la trayectoria
	if (origen_x == destino_x){ // se trata de un movimiento horizontal
		if (destino_y > origen_y) {
			for (int i = origen_y + 1; i < destino_y; i++) {
				if (comprobar_posicion(origen_x, i) == true)
					return true;
			}
		}
		if (origen_y > destino_y) {
			for (int i = destino_y + 1; i < origen_y; i++)
				if (comprobar_posicion(origen_x, i) == true)
					return true;
		}
	}
	if (origen_y == destino_y){ // se trata de un movimiento vertical
		if (destino_x > origen_x) {
			for (int i = origen_x + 1; i < destino_x; i++)
				if (comprobar_posicion(i, origen_y) == true)
					return true;
		}
		if (origen_x > destino_x) {
			for (int i = destino_x + 1; i < origen_x; i++)
				if (comprobar_posicion(i, origen_y) == true)
					return true;
		}
	}
	if ((origen_x != destino_x) && (origen_y != destino_y)){ // se trata de un movimiento diagonal
		int diferencia = fabs(origen_x - destino_x);
		if ((origen_x < destino_x) && (origen_y < destino_y)) {
			for (int i = 1; i < diferencia; i++)
				if (comprobar_posicion(origen_x + i, origen_y + i) == true)
					return true;
		}
		if ((origen_x < destino_x) && (origen_y > destino_y)) {
			for (int i = 1; i < diferencia; i++)
				if (comprobar_posicion(origen_x + i, origen_y - i) == true)
					return true;
		}
		if ((origen_x > destino_x) && (origen_y > destino_y)) {
			for (int i = 1; i < diferencia; i++)
				if (comprobar_posicion(origen_x - i, origen_y - i) == true)
					return true;
		}
		if ((origen_x > destino_x) && (origen_y < destino_y)) {
			for (int i = 1; i < diferencia; i++)
				if (comprobar_posicion(origen_x - i, origen_y + i) == true)
					return true;
		}
	}
	return false;
}

// esta funci�n sirve para ejecutar el movimiento, eliminando la pieza comica (si hay) y moviendo la pieza seleccionada
void ListaPiezas::ejecuta_movimiento(int origen_x, int origen_y, int destino_x, int destino_y, int turno) {
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == destino_x && reyes[i]->getY() == destino_y)
			eliminar(reyes[i]);
		if (reyes[i]->getX() == origen_x && reyes[i]->getY() == origen_y) {
			reyes[i]->setX(destino_x);
			reyes[i]->setY(destino_y);
			reyes[i]->setPrimerMovimiento();
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
			torres[i]->setPrimerMovimiento();
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
		char color;
		if (turno == 0)
			color = 'b';
		if (turno == 1)
			color = 'w';

		if (peones[i]->getX() == destino_x && peones[i]->getY() == destino_y)
			eliminar(peones[i]);
		if (peones[i]->getX() == destino_x && peones[i]->getY() == origen_y && peones[i]->getColor() == color && peones[i]->getJugadaPrimerMovimiento() == numero_jugadas - 1)
			eliminar(peones[i]);
		if (peones[i]->getX() == origen_x && peones[i]->getY() == origen_y) {
			peones[i]->setX(destino_x);
			peones[i]->setY(destino_y);
			if(peones[i]->getPrimerMovimiento() == true && fabs(destino_y - origen_y) == 2)
				peones[i]->setJugadaPrimerMovimiento(numero_jugadas);
			peones[i]->setPrimerMovimiento();
		}

		// usa vez he cambiado la posicion del pe�n, compruebo si puede coronar
		if ((peones[i]->getY() == 8 && peones[i]->getColor() == 'w') || (peones[i]->getY() == 1 && peones[i]->getColor() == 'b'))
		{
			int opcion, posX = peones[i]->getX(), posY = peones[i]->getY();
			char color = peones[i]->getColor();
			cout << "El peon puede coronar. Seleccione una opcion:" << endl; 
			cout << "1: Coronar en torre" << endl;
			cout << "2: Coronar en caballo" << endl;
			cout << "3: Coronar en alfil" << endl;
			cout << "4: Coronar en reina" << endl;
			cin >> opcion;
			if (opcion == 1) {
				eliminar(peones[i]);
				Torre* torre = new Torre(posX, posY, color, false);
				agregar(torre);
			}
			if (opcion == 2) {
				eliminar(peones[i]);
				Caballo* caballo = new Caballo(posX, posY, color);
				agregar(caballo);
			}
			if (opcion == 3) {
				eliminar(peones[i]);
				Alfil* alfil = new Alfil(posX, posY, color);
				agregar(alfil);
			}
			if (opcion == 4) {
				eliminar(peones[i]);
				Reina* reina = new Reina(posX, posY, color);
				agregar(reina);
			}
		}
	}
	numero_jugadas += 1;
}

void ListaPiezas::ejecuta_movimientocopia(int origen_x, int origen_y, int destino_x, int destino_y, int turno) {
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == destino_x && reyes[i]->getY() == destino_y)
			eliminar(reyes[i]);
		if (reyes[i]->getX() == origen_x && reyes[i]->getY() == origen_y) {
			reyes[i]->setX(destino_x);
			reyes[i]->setY(destino_y);
			reyes[i]->setPrimerMovimiento();
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
			torres[i]->setPrimerMovimiento();
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
		char color;
		if (turno == 0)
			color = 'b';
		if (turno == 1)
			color = 'w';

		if (peones[i]->getX() == destino_x && peones[i]->getY() == destino_y)
			eliminar(peones[i]);
		if (peones[i]->getX() == destino_x && peones[i]->getY() == origen_y && peones[i]->getColor() == color && peones[i]->getJugadaPrimerMovimiento() == numero_jugadas - 1)
			eliminar(peones[i]);
		if (peones[i]->getX() == origen_x && peones[i]->getY() == origen_y) {
			peones[i]->setX(destino_x);
			peones[i]->setY(destino_y);
			if (peones[i]->getPrimerMovimiento() == true && fabs(destino_y - origen_y) == 2)
				peones[i]->setJugadaPrimerMovimiento(numero_jugadas);
			peones[i]->setPrimerMovimiento();
		}

		// usa vez he cambiado la posicion del pe�n, compruebo si puede coronar
		if ((peones[i]->getY() == 8 && peones[i]->getColor() == 'w') || (peones[i]->getY() == 1 && peones[i]->getColor() == 'b'))
		{
			int opcion, posX = peones[i]->getX(), posY = peones[i]->getY();
			char color = peones[i]->getColor();
			eliminar(peones[i]);
			Reina* reina = new Reina(posX, posY, color);
			agregar(reina);
		}
	}
	numero_jugadas += 1;
}

// esta funcion sirve para determinar si una determinada posici�n est� amenazada
bool ListaPiezas::comprobar_jaque(int x, int y, int turno) {
	char color = 'w'; // esta variable porque solamente pueden hacer jaque al rey las piezas del otro color
	if (turno == 0)
		color = 'b';

	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getColor() == color && reyes[i]->comprobar_movimiento(x, y) == true)
			return true; // si el rey contrario se puede mover hacia donde esta el nuestro vamos a estar en jaque
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getColor() == color && reinas[i]->comprobar_movimiento(x, y) == true && comprobar_trayectoria(reinas[i]->getX(), reinas[i]->getY(), x, y, turno) == false)
			return true; // si una reina contraria se puede mover hacia donde esta nuestro rey vamos a estar en jaque
	}
	for (int i = 0; i < numerotorres; i++){
		if (torres[i]->getColor() == color && torres[i]->comprobar_movimiento(x, y) == true && comprobar_trayectoria(torres[i]->getX(), torres[i]->getY(), x, y, turno) == false)
			return true; // si una torre contraria se puede mover hacia donde esta nuestro rey vamos a estar en jaque
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getColor() == color && caballos[i]->comprobar_movimiento(x, y))
			return true; // si un caballo contrario se puede mover hacia donde esta nuestro rey vamos a estar en jaque
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getColor() == color && alfiles[i]->comprobar_movimiento(x, y) == true && comprobar_trayectoria(alfiles[i]->getX(), alfiles[i]->getY(), x, y, turno) == false)
			return true; // si un alfil contraria se puede mover hacia donde esta nuestro rey vamos a estar en jaque
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getColor() == color) {
			int variaciony = 0;
			if (peones[i]->getColor() == 'w')
				variaciony = y - peones[i]->getY();
			else
				variaciony = peones[i]->getY() - y;
			// el rey estar� en jaque si el peon puede comerle
			if (fabs(peones[i]->getX() - x) == 1 && variaciony == 1)
				return true;
		}
	}
	return false;
}

bool ListaPiezas::comprobar_jaque2(int x, int y, int turno) {
	char color = 'w'; // esta variable porque solamente pueden hacer jaque al rey las piezas del otro color
	int turnocontrario = 1; // esta variable nos va a servir para determinar si estamos o no en jaque
	bool jaque = false;
	if (turno == 1) {
		color = 'b';
		turnocontrario = 0;
	}

	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_posicion(j, h, turnocontrario) == true && comprobar_movimiento(j, h, x, y, turnocontrario) == true)
						jaque = true;
				}
			}
		}
	}
	return jaque;
}

bool ListaPiezas::comprobar_jaquemate(int turno, ListaPiezas L) {
	char color = 'w'; // esta variable porque solamente pueden hacer jaque al rey las piezas del otro color
	int posreyX, posreyY; // estas variables me sirven para guardar cual es la posicion del rey;
	if (turno == 1)
		color = 'b';

	// En primer lugar, comprobamos si en la posici�n actual existe jaque o no
	for (int i = 0; i < numeroreyes; i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
		if (reyes[i]->getColor() == color) {
			posreyX = reyes[i]->getX();
			posreyY = reyes[i]->getY();
			if (comprobar_jaque2(posreyX, posreyY, turno) == false)// Si en la situacion actual no existe jaque, no puede ser jaque mate
				return false;
		}
	}

	// ahora tenemos que comprobar que en todos los futuros posibles sigue habiendo jaque
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(reyes[i]->getX(), reyes[i]->getY(), j, h, turno) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimiento(reyes[i]->getX(), reyes[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroReyes(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getRey(i).getColor() == color) {
								if (piezas2.comprobar_jaque2(j, h, turno) == false) {
									return false;
								}
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(reinas[i]->getX(), reinas[i]->getY(), j, h, turno) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimiento(reinas[i]->getX(), reinas[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroReinas(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getReina(i).getColor() == color) {
								if (piezas2.comprobar_jaque2(posreyX, posreyY, turno) == false)
									return false;
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(torres[i]->getX(), torres[i]->getY(), j, h, turno) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimiento(torres[i]->getX(), torres[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroTorres(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getTorre(i).getColor() == color) {
								if (piezas2.comprobar_jaque2(posreyX, posreyY, turno) == false)
									return false;
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(caballos[i]->getX(), caballos[i]->getY(), j, h, turno) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimiento(caballos[i]->getX(), caballos[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroCaballos(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getCaballo(i).getColor() == color) {
								if (piezas2.comprobar_jaque2(posreyX, posreyY, turno) == false)
									return false;
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(alfiles[i]->getX(), alfiles[i]->getY(), j, h, turno) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimiento(alfiles[i]->getX(), alfiles[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroAlfiles(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getAlfil(i).getColor() == color) {
								if (piezas2.comprobar_jaque2(posreyX, posreyY, turno) == false)
									return false;
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(peones[i]->getX(), peones[i]->getY(), j, h, turno) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimiento(peones[i]->getX(), peones[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroPeones(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getPeon(i).getColor() == color)
								if (piezas2.comprobar_jaque2(posreyX, posreyY, turno) == false)
									return false;
						}
					}
				}
			}
		}
	}
	return true;
}

bool ListaPiezas::comprobar_ahogado(int turno) {
	char color = 'w'; // esta variable porque solamente pueden hacer jaque al rey las piezas del otro color
	int posreyX, posreyY; // estas variables me sirven para guardar cual es la posicion del rey;
	if (turno == 1)
		color = 'b';

	// En primer lugar, comprobamos si en la posici�n actual existe jaque o no
	for (int i = 0; i < numeroreyes; i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
		if (reyes[i]->getColor() == color) {
			posreyX = reyes[i]->getX();
			posreyY = reyes[i]->getY();
			if (comprobar_jaque2(posreyX, posreyY, turno) == true)// Si en la situacion actual no existe jaque, no puede ser jaque mate
				return false;
		}
	}

	// ahora tenemos que comprobar no podemos mover ninguna pieza
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(reyes[i]->getX(), reyes[i]->getY(), j, h, turno) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(reinas[i]->getX(), reinas[i]->getY(), j, h, turno) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(torres[i]->getX(), torres[i]->getY(), j, h, turno) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(caballos[i]->getX(), caballos[i]->getY(), j, h, turno) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(alfiles[i]->getX(), alfiles[i]->getY(), j, h, turno) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(peones[i]->getX(), peones[i]->getY(), j, h, turno) == true)
						return false;
				}
			}
		}
	}
	return true;
}

bool ListaPiezas::comprobar_comeralpaso(int origen_x, int origen_y, int destino_x, int destino_y, int turno, Peon p) {
	int variaciony = 0;
	if (p.getColor() == 'w')
		variaciony = destino_y - origen_y;
	else
		variaciony = origen_y - destino_y;
	
	char color;
	if (turno == 0)
		color = 'b';
	if (turno == 1)
		color = 'w';
	for (int j = 0; j < numeropeones; j++) {
		if (variaciony == 1 && peones[j]->getX() == destino_x && peones[j]->getY() == origen_y && peones[j]->getColor() == color && peones[j]->getJugadaPrimerMovimiento() == numero_jugadas - 1) {
			return true;
		}
	}
}

bool ListaPiezas::comprobar_enroque() {
	return false;
}

bool ListaPiezas::agregar(Rey* k){
	bool iguales = false;
	// comprobamos que la pieza a introducir no ha sido ya introducida
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i] == k)
			iguales = true;
	}
	// si no ha sido ya introducida y el vector no est� lleno
	if ((numeroreyes < MAX_PIEZAS) && (iguales == false))
		reyes[numeroreyes++] = k; // �ltimo puesto sin rellenar 
	else
		return false;
	return true;
}

bool ListaPiezas::agregar(Reina* q){
	bool iguales = false;
	// comprobamos que la pieza a introducir no ha sido ya introducida
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i] == q)
			iguales = true;
	}
	// si no ha sido ya introducida y el vector no est� lleno
	if ((numeroreinas < MAX_PIEZAS) && (iguales == false))
		reinas[numeroreinas++] = q; // �ltimo puesto sin rellenar 
	else
		return false;
	return true;
}

bool ListaPiezas::agregar(Torre* t){
	bool iguales = false;
	// comprobamos que la pieza a introducir no ha sido ya introducida
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i] == t)
			iguales = true;
	}
	// si no ha sido ya introducida y el vector no est� lleno
	if ((numerotorres < MAX_PIEZAS) && (iguales == false))
		torres[numerotorres++] = t; // �ltimo puesto sin rellenar 
	else
		return false;
	return true;
}

bool ListaPiezas::agregar(Caballo* c){
	bool iguales = false;
	// comprobamos que la pieza a introducir no ha sido ya introducida
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i] == c)
			iguales = true;
	}
	// si no ha sido ya introducida y el vector no est� lleno
	if ((numerocaballos < MAX_PIEZAS) && (iguales == false))
		caballos[numerocaballos++] = c; // �ltimo puesto sin rellenar 
	else
		return false;
	return true;
}

bool ListaPiezas::agregar(Alfil* a){
	bool iguales = false;
	// comprobamos que la pieza a introducir no ha sido ya introducida
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i] == a)
			iguales = true;
	}
	// si no ha sido ya introducida y el vector no est� lleno
	if ((numeroalfiles < MAX_PIEZAS) && (iguales == false))
		alfiles[numeroalfiles++] = a; // �ltimo puesto sin rellenar 
	else
		return false;
	return true;
}

bool ListaPiezas::agregar(Peon* p){
	bool iguales = false;
	// comprobamos que la pieza a introducir no ha sido ya introducida
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i] == p)
			iguales = true;
	}
	// si no ha sido ya introducida y el vector no est� lleno
	if ((numeropeones < MAX_PIEZAS) && (iguales == false))
		peones[numeropeones++] = p; // �ltimo puesto sin rellenar 
	else
		return false;
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
	for (int i = 0; i < numeroreyes; i++) // destrucci�n de reyess 
		delete reyes[i];
	for (int i = 0; i < numeroreyes; i++) // destrucci�n de reinas
		delete reinas[i];
	for (int i = 0; i < numeroreyes; i++) // destrucci�n de torres
		delete torres[i];
	for (int i = 0; i < numeroreyes; i++) // destrucci�n de caballos
		delete caballos[i];
	for (int i = 0; i < numeroreyes; i++) // destrucci�n de alfiles
		delete alfiles[i];
	for (int i = 0; i < numeroreyes; i++) // destrucci�n de peones
		delete peones[i];
	numeroreyes = 0; // inicializa lista 
	numeroreinas = 0; // inicializa lista
	numerotorres = 0; // inicializa lista
	numerocaballos = 0; // inicializa lista
	numeroalfiles = 0; // inicializa lista
	numeropeones = 0; // inicializa lista
}

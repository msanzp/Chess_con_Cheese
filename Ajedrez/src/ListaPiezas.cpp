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

	numeroreinasblancascomidas = 0;
	numeroreinasnegrascomidas = 0;
	numerotorresblancascomidas = 0;
	numerotorresnegrascomidas = 0;
	numerocaballosblancoscomidos = 0;
	numerocaballosnegroscomidos = 0;
	numeroalfilesblancoscomidos = 0;
	numeroalfilesnegroscomidos = 0;
	numeropeonesblancoscomidos = 0;
	numeropeonesnegroscomidos = 0;
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
		Peon* peon = new Peon(copia.peones[i]->getX(), copia.peones[i]->getY(), copia.peones[i]->getColor(), copia.peones[i]->getPrimerMovimiento());
		agregar(peon);
	}
}

ListaPiezas::~ListaPiezas() {}

// dibuja todas las piezas presentes en el tablero
void ListaPiezas::dibuja2D(int pieza_seleccionadaX, int pieza_seleccionadaY){
	for (int i = 0; i < numeroreyes; i++)
		reyes[i]->dibuja2D("imagenes/2D/reyblanco_fondoblanco.png", "imagenes/2D/reyblanco_fondonegro.png", "imagenes/2D/reynegro_fondoblanco.png", "imagenes/2D/reynegro_fondonegro.png", "imagenes/2D/reyblanco_fondoverde.png", "imagenes/2D/reynegro_fondoverde.png", pieza_seleccionadaX, pieza_seleccionadaY);
	for (int i = 0; i < numeroreinas; i++)
		reinas[i]->dibuja2D("imagenes/2D/reinablanca_fondoblanco.png", "imagenes/2D/reinablanca_fondonegro.png", "imagenes/2D/reinanegra_fondoblanco.png", "imagenes/2D/reinanegra_fondonegro.png", "imagenes/2D/reinablanca_fondoverde.png", "imagenes/2D/reinanegra_fondoverde.png", pieza_seleccionadaX, pieza_seleccionadaY);
	for (int i = 0; i < numerotorres; i++)
		torres[i]->dibuja2D("imagenes/2D/torreblanca_fondoblanco.png", "imagenes/2D/torreblanca_fondonegro.png", "imagenes/2D/torrenegra_fondoblanco.png", "imagenes/2D/torrenegra_fondonegro.png", "imagenes/2D/torreblanca_fondoverde.png", "imagenes/2D/torrenegra_fondoverde.png", pieza_seleccionadaX, pieza_seleccionadaY);
	for (int i = 0; i < numerocaballos; i++)
		caballos[i]->dibuja2D("imagenes/2D/caballoblanco_fondoblanco.png", "imagenes/2D/caballoblanco_fondonegro.png", "imagenes/2D/caballonegro_fondoblanco.png", "imagenes/2D/caballonegro_fondonegro.png", "imagenes/2D/caballoblanco_fondoverde.png", "imagenes/2D/caballonegro_fondoverde.png", pieza_seleccionadaX, pieza_seleccionadaY);
	for (int i = 0; i < numeroalfiles; i++)
		alfiles[i]->dibuja2D("imagenes/2D/alfilblanco_fondoblanco.png", "imagenes/2D/alfilblanco_fondonegro.png", "imagenes/2D/alfilnegro_fondoblanco.png", "imagenes/2D/alfilnegro_fondonegro.png", "imagenes/2D/alfilblanco_fondoverde.png", "imagenes/2D/alfilnegro_fondoverde.png", pieza_seleccionadaX, pieza_seleccionadaY);
	for (int i = 0; i < numeropeones; i++)
		peones[i]->dibuja2D("imagenes/2D/peonblanco_fondoblanco.png", "imagenes/2D/peonblanco_fondonegro.png", "imagenes/2D/peonnegro_fondoblanco.png", "imagenes/2D/peonnegro_fondonegro.png", "imagenes/2D/peonblanco_fondoverde.png", "imagenes/2D/peonnegro_fondoverde.png", pieza_seleccionadaX, pieza_seleccionadaY);
	
	// piezas comidas por el jugador negro
	dibujaComidas2D("imagenes/2D/reinablanca_fondonegro.png", 10, 3.56, numeroreinasblancascomidas);
	dibujaComidas2D("imagenes/2D/torreblanca_fondonegro.png", 10, 2.28, numerotorresblancascomidas);
	dibujaComidas2D("imagenes/2D/caballoblanco_fondonegro.png", 10, 1, numerocaballosblancoscomidos);
	dibujaComidas2D("imagenes/2D/alfilblanco_fondonegro.png", 12.5, 2.9, numeroalfilesblancoscomidos);
	dibujaComidas2D("imagenes/2D/peonblanco_fondonegro.png", 12.5, 1.7, numeropeonesblancoscomidos);

	// piezas comidas por el jugador blanco
	dibujaComidas2D("imagenes/2D/reinanegra_fondonegro.png", -4.5, 3.56, numeroreinasnegrascomidas);
	dibujaComidas2D("imagenes/2D/torrenegra_fondonegro.png", -4.5, 2.28, numerotorresnegrascomidas);
	dibujaComidas2D("imagenes/2D/caballonegro_fondonegro.png", -4.5, 1, numerocaballosnegroscomidos);
	dibujaComidas2D("imagenes/2D/alfilnegro_fondonegro.png", -2, 2.9, numeroalfilesnegroscomidos);
	dibujaComidas2D("imagenes/2D/peonnegro_fondonegro.png", -2, 1.7, numeropeonesnegroscomidos);
}

void ListaPiezas::dibujaComidas2D(const char foto[], float coordenadaX, float coordenadaY, int numerocomido)
{
	// esta función sirve para pintar las piezas que han sido eliminadas
	// primero pintamos las piezas blancas comidas
	glEnable(GL_TEXTURE_2D);

	// reinas blancas comidas
	glBindTexture(GL_TEXTURE_2D, getTexture(foto).id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(coordenadaX * 4 - 4, coordenadaY * 4 - 4, 0);
	glTexCoord2d(1, 1);		glVertex3f(coordenadaX * 4, coordenadaY * 4 - 4, 0);
	glTexCoord2d(1, 0);		glVertex3f(coordenadaX * 4, coordenadaY * 4, 0);
	glTexCoord2d(0, 0);		glVertex3f(coordenadaX * 4 - 4, coordenadaY * 4, 0);
	glEnd();

	if(numerocomido == 0)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x0.png").id);
	if (numerocomido == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x1.png").id);
	if (numerocomido == 2)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x2.png").id);
	if (numerocomido == 3)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x3.png").id);
	if (numerocomido == 4)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x4.png").id);
	if (numerocomido == 5)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x5.png").id);
	if (numerocomido == 6)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x6.png").id);
	if (numerocomido == 7)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x7.png").id);
	if (numerocomido == 8)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x8.png").id);
	if (numerocomido == 9)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/2D/x9.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f((coordenadaX + 1) * 4 - 4, coordenadaY * 4 - 4, 0);
	glTexCoord2d(1, 1);		glVertex3f((coordenadaX + 1) * 4, coordenadaY * 4 - 4, 0);
	glTexCoord2d(1, 0);		glVertex3f((coordenadaX + 1) * 4, coordenadaY * 4, 0);
	glTexCoord2d(0, 0);		glVertex3f((coordenadaX + 1) * 4 - 4, coordenadaY * 4, 0);
	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void ListaPiezas::dibuja3D() {
	for (int i = 0; i < numeroreyes; i++)
		reyes[i]->dibuja3D("imagenes/rey.txt");
	for (int i = 0; i < numeroreinas; i++)
		reinas[i]->dibuja3D("imagenes/reina.txt");
	for (int i = 0; i < numerotorres; i++)
		torres[i]->dibuja3D("imagenes/torre.txt");
	for (int i = 0; i < numerocaballos; i++)
		caballos[i]->dibuja3D("imagenes/caballo.txt");
	for (int i = 0; i < numeroalfiles; i++)
		alfiles[i]->dibuja3D("imagenes/alfil.txt");
	for (int i = 0; i < numeropeones; i++)
		peones[i]->dibuja3D("imagenes/peon.txt");
}

// esta funcion sirve para determinar si una determinada casilla está ocupada por por una pieza de un color especifico
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

// esta funcion sirve para determinar si una determinada casilla está ocupada por alguna pieza
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

// esta función sirve para determinar si podemos mover una pieza de una casilla a otra
bool ListaPiezas::comprobar_movimiento(int origen_x, int origen_y, int destino_x, int destino_y, int turno, ListaPiezas L){
	// lo primero que hacemos es comprobar que las posiciones de origen y destino son diferentes
	if (origen_x == destino_x && origen_y == destino_y)
		return false;

	// una vez son diferentes, lo primero que invalida cualquier movimiento es el jaque
	char color = 'w'; // esta variable sirve para saber que color de pieza mueve el jugador del turno
	if (turno == 1)
		color = 'b';

	// debido a ser una de las jugadas más raras, vamos a analizar primero el enroque
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == origen_x && reyes[i]->getY() == origen_y) {
			for (int j = 0; j < numerotorres; j++) {
				if (comprobar_enroque(origen_x, origen_y, destino_x, destino_y, turno, reyes[i], torres[j]) == true)
					return true;
			}
		}
	}

	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == origen_x && reyes[i]->getY() == origen_y){
			// primero comprobamos que la forma de moverse corresponde con la del rey
			if (reyes[i]->comprobar_movimiento(destino_x, destino_y) == true) {
				// si la forma de moverse es la adecuada, comprobamos que no hay piezas de su mismo color en la casilla de destino
				if (comprobar_posicion(destino_x, destino_y, turno) == true)
					return false;
				else {
					ListaPiezas piezas2 = (L);
					piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
					for (int j = 0; j < piezas2.getNumeroReyes(); j++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
						if (piezas2.getRey(j).getColor() == color) {
							if (piezas2.comprobar_jaque(piezas2.getRey(j).getX(), piezas2.getRey(j).getY(), turno) == true) {
								return false;
							}
						}
					}
				}
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
				if (comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y, turno) == false) {
					ListaPiezas piezas2 = (L);
					piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
					for (int j = 0; j < piezas2.getNumeroReyes(); j++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
						if (piezas2.getRey(j).getColor() == color) {
							if (piezas2.comprobar_jaque(piezas2.getRey(j).getX(), piezas2.getRey(j).getY(), turno) == true) {
								return false;
							}
						}
					}
				}
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
				if (comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y, turno) == false) {
					ListaPiezas piezas2 = (L);
					piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
					for (int j = 0; j < piezas2.getNumeroReyes(); j++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
						if (piezas2.getRey(j).getColor() == color) {
							if (piezas2.comprobar_jaque(piezas2.getRey(j).getX(), piezas2.getRey(j).getY(), turno) == true) {
								return false;
							}
						}
					}
				}
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
				else {
					ListaPiezas piezas2 = (L);
					piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
					for (int j = 0; j < piezas2.getNumeroReyes(); j++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
						if (piezas2.getRey(j).getColor() == color) {
							if (piezas2.comprobar_jaque(piezas2.getRey(j).getX(), piezas2.getRey(j).getY(), turno) == true) {
								return false;
							}
						}
					}
				}
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
				if (comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y, turno) == false) {
					ListaPiezas piezas2 = (L);
					piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
					for (int j = 0; j < piezas2.getNumeroReyes(); j++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
						if (piezas2.getRey(j).getColor() == color) {
							if (piezas2.comprobar_jaque(piezas2.getRey(j).getX(), piezas2.getRey(j).getY(), turno) == true) {
								return false;
							}
						}
					}
				}
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

			int turno1 = 0; // esta variable sirve para comer en diagonal una pieza del otro jugador
			if (turno == 0)
				turno1 = 1;

			// si se mueve hacia adelante
			if (origen_x == destino_x) {
				if (peones[i]->comprobar_movimiento(destino_x, destino_y) == true) {
					if (comprobar_posicion(destino_x, destino_y) == true)
						return false;
					if (comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y, turno) == true)
						return false;
					ListaPiezas piezas2 = (L);
					piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
					for (int j = 0; j < piezas2.getNumeroReyes(); j++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
						if (piezas2.getRey(j).getColor() == color) {
							if (piezas2.comprobar_jaque(piezas2.getRey(j).getX(), piezas2.getRey(j).getY(), turno) == true) {
								return false;
							}
						}
					}
				}
				else
					return false;
				return true;
			}

			// si se mueve de lado para comer
			else if (fabs(origen_x - destino_x) == 1) {
				// en primer lugar ejecutamos el movimiento normal de comer en diagonal
				if (variaciony == 1 && comprobar_posicion(destino_x, destino_y, turno1) == true) {
					ListaPiezas piezas2 = (L);
					piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
					for (int j = 0; j < piezas2.getNumeroReyes(); j++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
						if (piezas2.getRey(j).getColor() == color) {
							if (piezas2.comprobar_jaque(piezas2.getRey(j).getX(), piezas2.getRey(j).getY(), turno) == true) {
								return false;
							}
						}
					}
					return true;
				}
				// tras ello, ejecutamos la jugada de "comer al paso"
				else if (comprobar_comeralpaso(origen_x, origen_y, destino_x, destino_y, turno, *peones[i]) == true) {
					if (comprobar_trayectoria(origen_x, origen_y, destino_x, destino_y, turno) == false) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
						for (int j = 0; j < piezas2.getNumeroReyes(); j++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getRey(j).getColor() == color) {
								if (piezas2.comprobar_jaque(piezas2.getRey(j).getX(), piezas2.getRey(j).getY(), turno) == true) {
									return false;
								}
							}
						}
					}
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
	}
}

// esta función sirve para determinar si hay piezas o no en medio de la trayectoria, devuelve false si la trayectoria esta libre
bool ListaPiezas::comprobar_trayectoria(int origen_x, int origen_y, int destino_x, int destino_y, int turno) {
	// lo primero que hacemos es comprobar que en la posición de destino no hay ficha de mi mismo color
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

// esta función sirve para ejecutar el movimiento, eliminando la pieza comica (si hay) y moviendo la pieza seleccionada
void ListaPiezas::ejecuta_movimiento(int origen_x, int origen_y, int destino_x, int destino_y, int turno) {
	// lo primero que ejecutamos son los posibles enroques
	if (origen_x == 5 && origen_y == 1 && destino_x == 7 && destino_y == 1) {
		for (int i = 0; i < numeroreyes; i++) {
			for (int j = 0; j < numerotorres; j++) {
				if (comprobar_enroque(origen_x, origen_y, destino_x, destino_y, turno, reyes[i], torres[j]) == true){
					ETSIDI::play("sonidos/mover.wav");
					reyes[i]->setX(7);
					reyes[i]->setY(1);
					torres[j]->setX(6);
					torres[j]->setY(1);
					return;
				}
			}
		}
	}
	if (origen_x == 5 && origen_y == 1 && destino_x == 3 && destino_y == 1) {
		for (int i = 0; i < numeroreyes; i++) {
			for (int j = 0; j < numerotorres; j++) {
				if (comprobar_enroque(origen_x, origen_y, destino_x, destino_y, turno, reyes[i], torres[j]) == true) {
					ETSIDI::play("sonidos/mover.wav");
					reyes[i]->setX(3);
					reyes[i]->setY(1);
					torres[j]->setX(4);
					torres[j]->setY(1);
					return;
				}
			}
		}
	}
	if (origen_x == 5 && origen_y == 8 && destino_x == 7 && destino_y == 8) {
		for (int i = 0; i < numeroreyes; i++) {
			for (int j = 0; j < numerotorres; j++) {
				if (comprobar_enroque(origen_x, origen_y, destino_x, destino_y, turno, reyes[i], torres[j]) == true) {
					ETSIDI::play("sonidos/mover.wav");
					reyes[i]->setX(7);
					reyes[i]->setY(8);
					torres[j]->setX(6);
					torres[j]->setY(8);
					return;
				}
			}
		}
	}
	if (origen_x == 5 && origen_y == 8 && destino_x == 3 && destino_y == 8) {
		for (int i = 0; i < numeroreyes; i++) {
			for (int j = 0; j < numerotorres; j++) {
				if (comprobar_enroque(origen_x, origen_y, destino_x, destino_y, turno, reyes[i], torres[j]) == true) {
					ETSIDI::play("sonidos/mover.wav");
					reyes[i]->setX(3);
					reyes[i]->setY(8);
					torres[j]->setX(4);
					torres[j]->setY(8);
					return;
				}
			}
		}
	}

	// para que no tocas las piezas puedan comer al paso, comprobamos que sea un peon la pieza que se encuentra en la casilla de origen
	bool comer_paso = false;
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getX() == origen_x && peones[i]->getY() == origen_y)
			comer_paso = true;
	}

	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getX() == origen_x && reyes[i]->getY() == origen_y) {
			ETSIDI::play("sonidos/mover.wav");
			reyes[i]->setX(destino_x);
			reyes[i]->setY(destino_y);
			reyes[i]->setPrimerMovimiento();
		}
	}

	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getX() == destino_x && reinas[i]->getY() == destino_y) {
			ETSIDI::play("sonidos/comer.wav");
			eliminar(reinas[i]);
		}
		if (reinas[i]->getX() == origen_x && reinas[i]->getY() == origen_y) {
			ETSIDI::play("sonidos/mover.wav");
			reinas[i]->setX(destino_x);
			reinas[i]->setY(destino_y);
		}
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getX() == destino_x && torres[i]->getY() == destino_y) {
			ETSIDI::play("sonidos/comer.wav");
			eliminar(torres[i]);
		}
		if (torres[i]->getX() == origen_x && torres[i]->getY() == origen_y) {
			ETSIDI::play("sonidos/mover.wav");
			torres[i]->setX(destino_x);
			torres[i]->setY(destino_y);
			torres[i]->setPrimerMovimiento();
		}
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getX() == destino_x && caballos[i]->getY() == destino_y) {
			ETSIDI::play("sonidos/comer.wav");
			eliminar(caballos[i]);
		}
		if (caballos[i]->getX() == origen_x && caballos[i]->getY() == origen_y) {
			ETSIDI::play("sonidos/mover.wav");
			caballos[i]->setX(destino_x);
			caballos[i]->setY(destino_y);
		}
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getX() == destino_x && alfiles[i]->getY() == destino_y) {
			ETSIDI::play("sonidos/comer.wav");
			eliminar(alfiles[i]);
		}
		if (alfiles[i]->getX() == origen_x && alfiles[i]->getY() == origen_y) {
			ETSIDI::play("sonidos/mover.wav");
			alfiles[i]->setX(destino_x);
			alfiles[i]->setY(destino_y);
		}
	}
	for (int i = 0; i < numeropeones; i++) {
		bool comido_por_peon;
		char color;
		if (turno == 0)
			color = 'b';
		if (turno == 1)
			color = 'w';

		if (peones[i]->getX() == destino_x && peones[i]->getY() == destino_y) {
			ETSIDI::play("sonidos/comer.wav");
			eliminar(peones[i]);
		}
		if (comer_paso == true && peones[i]->getX() == destino_x && peones[i]->getY() == origen_y && peones[i]->getColor() == color && peones[i]->getJugadaPrimerMovimiento() == numero_jugadas - 1) {
			ETSIDI::play("sonidos/comer.wav");
			eliminar(peones[i]);
		}
		if (peones[i]->getX() == origen_x && peones[i]->getY() == origen_y) {
			ETSIDI::play("sonidos/mover.wav");
			peones[i]->setX(destino_x);
			peones[i]->setY(destino_y);
			if (peones[i]->getPrimerMovimiento() == true && fabs(destino_y - origen_y) == 2) {
				peones[i]->setJugadaPrimerMovimiento(numero_jugadas);
			}	
			peones[i]->setPrimerMovimiento();
			// usa vez he cambiado la posicion del peón, compruebo si puede coronar
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
				ETSIDI::play("sonidos/coronar.wav");
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
				return;
			}
		}
	}
	numero_jugadas += 1;
}

void ListaPiezas::ejecuta_movimientocopia(int origen_x, int origen_y, int destino_x, int destino_y, int turno) {
	// lo primero que ejecutamos son los posibles enroques
	if (origen_x == 5 && origen_y == 1 && destino_x == 7 && destino_y == 1) {
		for (int i = 0; i < numeroreyes; i++) {
			for (int j = 0; j < numerotorres; j++) {
				if (comprobar_enroque(origen_x, origen_y, destino_x, destino_y, turno, reyes[i], torres[j]) == true) {
					reyes[i]->setX(7);
					reyes[i]->setY(1);
					torres[j]->setX(6);
					torres[j]->setY(1);
					return;
				}
			}
		}
	}
	if (origen_x == 5 && origen_y == 1 && destino_x == 3 && destino_y == 1) {
		for (int i = 0; i < numeroreyes; i++) {
			for (int j = 0; j < numerotorres; j++) {
				if (comprobar_enroque(origen_x, origen_y, destino_x, destino_y, turno, reyes[i], torres[j]) == true) {
					reyes[i]->setX(3);
					reyes[i]->setY(1);
					torres[j]->setX(4);
					torres[j]->setY(1);
					return;
				}
			}
		}
	}
	if (origen_x == 5 && origen_y == 8 && destino_x == 7 && destino_y == 8) {
		for (int i = 0; i < numeroreyes; i++) {
			for (int j = 0; j < numerotorres; j++) {
				if (comprobar_enroque(origen_x, origen_y, destino_x, destino_y, turno, reyes[i], torres[j]) == true) {
					reyes[i]->setX(7);
					reyes[i]->setY(8);
					torres[j]->setX(6);
					torres[j]->setY(8);
					return;
				}
			}
		}
	}
	if (origen_x == 5 && origen_y == 8 && destino_x == 3 && destino_y == 8) {
		for (int i = 0; i < numeroreyes; i++) {
			for (int j = 0; j < numerotorres; j++) {
				if (comprobar_enroque(origen_x, origen_y, destino_x, destino_y, turno, reyes[i], torres[j]) == true) {
					reyes[i]->setX(3);
					reyes[i]->setY(8);
					torres[j]->setX(4);
					torres[j]->setY(8);
					return;
				}
			}
		}
	}

	// para que no tocas las piezas puedan comer al paso, comprobamos que sea un peon la pieza que se encuentra en la casilla de origen
	bool comer_paso = false;
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getX() == origen_x && peones[i]->getY() == origen_y)
			comer_paso = true;
	}
	for (int i = 0; i < numeroreyes; i++) {
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
		if (comer_paso == true && peones[i]->getX() == destino_x && peones[i]->getY() == origen_y && peones[i]->getColor() == color && peones[i]->getJugadaPrimerMovimiento() == numero_jugadas - 1)
			eliminar(peones[i]);
		if (peones[i]->getX() == origen_x && peones[i]->getY() == origen_y) {
			peones[i]->setX(destino_x);
			peones[i]->setY(destino_y);
			if (peones[i]->getPrimerMovimiento() == true && fabs(destino_y - origen_y) == 2) {
				peones[i]->setJugadaPrimerMovimiento(numero_jugadas);
			}
			peones[i]->setPrimerMovimiento();
		}

		// usa vez he cambiado la posicion del peón, compruebo si puede coronar
		if ((peones[i]->getY() == 8 && peones[i]->getColor() == 'w') || (peones[i]->getY() == 1 && peones[i]->getColor() == 'b'))
		{
			int posX = peones[i]->getX(), posY = peones[i]->getY();
			char color = peones[i]->getColor();
			eliminar(peones[i]);
			Reina* reina = new Reina(posX, posY, color);
			agregar(reina);
		}
	}
	numero_jugadas += 1;
}

// esta funcion sirve para determinar si una determinada posición está amenazada
bool ListaPiezas::comprobar_jaque(int x, int y, int turno) {
	int turnocontrario = 0;
	char color = 'w'; // solamente pueden hacer jaque al rey las piezas del otro color
	if (turno == 0) {
		color = 'b';
		turnocontrario = 1;
	}
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getColor() == color && reyes[i]->comprobar_movimiento(x, y) == true && comprobar_trayectoria(reinas[i]->getX(), reinas[i]->getY(), x, y, turnocontrario) == false)
			return true; // si el rey contrario se puede mover hacia donde esta el nuestro vamos a estar en jaque
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getColor() == color && reinas[i]->comprobar_movimiento(x, y) == true && comprobar_trayectoria(reinas[i]->getX(), reinas[i]->getY(), x, y, turnocontrario) == false)
			return true;
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getColor() == color && torres[i]->comprobar_movimiento(x, y) == true && comprobar_trayectoria(torres[i]->getX(), torres[i]->getY(), x, y, turnocontrario) == false)
			return true; // si una torre contraria se puede mover hacia donde esta nuestro rey vamos a estar en jaque
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getColor() == color && caballos[i]->comprobar_movimiento(x, y) == true && comprobar_posicion(x, y, turnocontrario) == false)
			return true; // si un caballo contrario se puede mover hacia donde esta nuestro rey vamos a estar en jaque
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getColor() == color && alfiles[i]->comprobar_movimiento(x, y) == true && comprobar_trayectoria(alfiles[i]->getX(), alfiles[i]->getY(), x, y, turnocontrario) == false)
			return true; // si un alfil contraria se puede mover hacia donde esta nuestro rey vamos a estar en jaque
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getColor() == color) {
			int variaciony = 0;
			if (peones[i]->getColor() == 'w')
				variaciony = y - peones[i]->getY();
			else
				variaciony = peones[i]->getY() - y;
			// el rey estará en jaque si el peon puede comerle
			if (fabs(peones[i]->getX() - x) == 1 && variaciony == 1)
				return true;
		}
	}
	return false;
}

bool ListaPiezas::comprobar_jaquemate(int turno, ListaPiezas L) {
	char color = 'w'; // esta variable porque solamente pueden hacer jaque al rey las piezas del otro color
	int posreyX, posreyY; // estas variables me sirven para guardar cual es la posicion del rey;
	if (turno == 1)
		color = 'b';

	// En primer lugar, comprobamos si en la posición actual existe jaque o no
	for (int i = 0; i < numeroreyes; i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
		if (reyes[i]->getColor() == color) {
			posreyX = reyes[i]->getX();
			posreyY = reyes[i]->getY();
			if (comprobar_jaque(posreyX, posreyY, turno) == false)// Si en la situacion actual no existe jaque, no puede ser jaque mate
				return false;
		}
	}

	// ahora tenemos que comprobar que en todos los futuros posibles sigue habiendo jaque
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(reyes[i]->getX(), reyes[i]->getY(), j, h, turno, L) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimientocopia(reyes[i]->getX(), reyes[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroReyes(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getRey(i).getColor() == color) {
								if (piezas2.comprobar_jaque(j, h, turno) == false) {
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
					if (comprobar_movimiento(reinas[i]->getX(), reinas[i]->getY(), j, h, turno, L) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimientocopia(reinas[i]->getX(), reinas[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroReinas(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getReina(i).getColor() == color) {
								if (piezas2.comprobar_jaque(posreyX, posreyY, turno) == false)
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
					if (comprobar_movimiento(torres[i]->getX(), torres[i]->getY(), j, h, turno, L) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimientocopia(torres[i]->getX(), torres[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroTorres(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getTorre(i).getColor() == color) {
								if (piezas2.comprobar_jaque(posreyX, posreyY, turno) == false)
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
					if (comprobar_movimiento(caballos[i]->getX(), caballos[i]->getY(), j, h, turno, L) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimientocopia(caballos[i]->getX(), caballos[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroCaballos(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getCaballo(i).getColor() == color) {
								if (piezas2.comprobar_jaque(posreyX, posreyY, turno) == false)
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
					if (comprobar_movimiento(alfiles[i]->getX(), alfiles[i]->getY(), j, h, turno, L) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimientocopia(alfiles[i]->getX(), alfiles[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroAlfiles(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getAlfil(i).getColor() == color) {
								if (piezas2.comprobar_jaque(posreyX, posreyY, turno) == false)
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
					if (comprobar_movimiento(peones[i]->getX(), peones[i]->getY(), j, h, turno, L) == true) {
						ListaPiezas piezas2 = (L);
						piezas2.ejecuta_movimientocopia(peones[i]->getX(), peones[i]->getY(), j, h, turno);
						for (int i = 0; i < piezas2.getNumeroPeones(); i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
							if (piezas2.getPeon(i).getColor() == color)
								if (piezas2.comprobar_jaque(posreyX, posreyY, turno) == false)
									return false;
						}
					}
				}
			}
		}
	}
	return true;
}

bool ListaPiezas::comprobar_ahogado(int turno, ListaPiezas L) {
	char color = 'w';
	int posreyX, posreyY; // estas variables me sirven para guardar cual es la posicion del rey
	if (turno == 1)
		color = 'b';

	// En primer lugar, comprobamos si en la posición actual existe jaque o no
	for (int i = 0; i < numeroreyes; i++) { // este bucle sirve para identificar cual es el rey del jugador que le toca jugar
		if (reyes[i]->getColor() == color) {
			posreyX = reyes[i]->getX();
			posreyY = reyes[i]->getY();
			if (comprobar_jaque(posreyX, posreyY, turno) == true)// Si en la situacion actual no existe jaque, no puede ser jaque mate
				return false;
		}
	}

	// ahora tenemos que comprobar no podemos mover ninguna pieza
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(reyes[i]->getX(), reyes[i]->getY(), j, h, turno, L) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numeroreinas; i++) {
		if (reinas[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(reinas[i]->getX(), reinas[i]->getY(), j, h, turno, L) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numerotorres; i++) {
		if (torres[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(torres[i]->getX(), torres[i]->getY(), j, h, turno, L) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numerocaballos; i++) {
		if (caballos[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(caballos[i]->getX(), caballos[i]->getY(), j, h, turno, L) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numeroalfiles; i++) {
		if (alfiles[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(alfiles[i]->getX(), alfiles[i]->getY(), j, h, turno, L) == true)
						return false;
				}
			}
		}
	}
	for (int i = 0; i < numeropeones; i++) {
		if (peones[i]->getColor() == color) {
			for (int j = 1; j < 9; j++) {
				for (int h = 1; h < 9; h++) {
					if (comprobar_movimiento(peones[i]->getX(), peones[i]->getY(), j, h, turno, L) == true)
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

// el enroque se realiza seleccionando el rey
bool ListaPiezas::comprobar_enroque(int origen_x, int origen_y, int destino_x, int destino_y, int turno, Rey* k, Torre* t) {
	if (origen_x == 5 && origen_y == 1) { // comprobamos los enroques del rey blanco
		if (k->getPrimerMovimiento() == true && k->getX() == origen_x && k->getY() == origen_y && t->getPrimerMovimiento() == true) {
			// comprobamos el enroque corto
			if (t->getX() == 8 && t->getY() == 1) {
				if (comprobar_posicion(6, 1) == false && comprobar_posicion(7, 1) == false) {
					if (comprobar_jaque(5, 1, turno) == false && comprobar_jaque(6, 1, turno) == false && comprobar_jaque(7, 1, turno) == false) {
						if (destino_x == 7 && destino_y == 1)
							return true;
					}
				}
			}
			// comprobamos el enroque largo
			if (t->getX() == 1 && t->getY() == 1) {
				if (comprobar_posicion(2, 1) == false && comprobar_posicion(3, 1) == false && comprobar_posicion(4, 1) == false) {
					if (comprobar_jaque(3, 1, turno) == false && comprobar_jaque(4, 1, turno) == false && comprobar_jaque(5, 1, turno) == false) {
						if (destino_x == 3 && destino_y == 1)
							return true;
					}
				}
			}
		}
	}
	if (origen_x == 5 && origen_y == 8) { // comprobamos los enroques del rey negro
		if (k->getPrimerMovimiento() == true && k->getX() == origen_x && k->getY() == origen_y && t->getPrimerMovimiento() == true) {
			// comprobamos el enroque corto
			if (t->getX() == 8 && t->getY() == 8) {
				if (comprobar_posicion(6, 8) == false && comprobar_posicion(7, 8) == false) {
					if (comprobar_jaque(5, 8, turno) == false && comprobar_jaque(6, 8, turno) == false && comprobar_jaque(7, 8, turno) == false) {
						if (destino_x == 7 && destino_y == 8)
							return true;
					}
				}
			}
			// comprobamos el enroque largo
			if (t->getX() == 1 && t->getY() == 8) {
				if (comprobar_posicion(2, 8) == false && comprobar_posicion(3, 8) == false && comprobar_posicion(4, 8) == false) {
					if (comprobar_jaque(3, 8, turno) == false && comprobar_jaque(4, 8, turno) == false && comprobar_jaque(5, 8, turno) == false) {
						if (destino_x == 3 && destino_y == 8)
							return true;
					}
				}
			}
		}
	}
	return false;
}

bool ListaPiezas::agregar(Rey* k){
	bool iguales = false;
	// comprobamos que la pieza a introducir no ha sido ya introducida
	for (int i = 0; i < numeroreyes; i++) {
		if (reyes[i] == k)
			iguales = true;
	}
	// si no ha sido ya introducida y el vector no está lleno
	if ((numeroreyes < MAX_PIEZAS) && (iguales == false))
		reyes[numeroreyes++] = k; // último puesto sin rellenar 
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
	// si no ha sido ya introducida y el vector no está lleno
	if ((numeroreinas < MAX_PIEZAS) && (iguales == false))
		reinas[numeroreinas++] = q; // último puesto sin rellenar
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
	// si no ha sido ya introducida y el vector no está lleno
	if ((numerotorres < MAX_PIEZAS) && (iguales == false))
		torres[numerotorres++] = t; // último puesto sin rellenar 
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
	// si no ha sido ya introducida y el vector no está lleno
	if ((numerocaballos < MAX_PIEZAS) && (iguales == false))
		caballos[numerocaballos++] = c; // último puesto sin rellenar 
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
	// si no ha sido ya introducida y el vector no está lleno
	if ((numeroalfiles < MAX_PIEZAS) && (iguales == false))
		alfiles[numeroalfiles++] = a; // último puesto sin rellenar 
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
	// si no ha sido ya introducida y el vector no está lleno
	if ((numeropeones < MAX_PIEZAS) && (iguales == false))
		peones[numeropeones++] = p; // último puesto sin rellenar 
	else
		return false;
	return true;
}

void ListaPiezas::eliminar(Reina* q) {
	for (int j = 0; j < numeroreinas; j++)
		if (reinas[j] == q)
		{
			if (reinas[j]->getColor() == 'w')
				numeroreinasblancascomidas++;
			if (reinas[j]->getColor() == 'b')
				numeroreinasnegrascomidas++;
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
			if (torres[j]->getColor() == 'w')
				numerotorresblancascomidas++;
			if (torres[j]->getColor() == 'b')
				numerotorresnegrascomidas++;
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
			if (caballos[j]->getColor() == 'w')
				numerocaballosblancoscomidos++;
			if (caballos[j]->getColor() == 'b')
				numerocaballosnegroscomidos++;
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
			if (alfiles[j]->getColor() == 'w')
				numeroalfilesblancoscomidos++;
			if (alfiles[j]->getColor() == 'b')
				numeroalfilesnegroscomidos++;
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
			if (peones[j]->getColor() == 'w')
				numeropeonesblancoscomidos++;
			if (peones[j]->getColor() == 'b')
				numeropeonesnegroscomidos++;
			delete peones[j];
			numeropeones--;
			for (int i = j; i < numeropeones; i++)
				peones[i] = peones[i + 1];
		}
}

void ListaPiezas::destruirContenido() {
	for (int i = 0; i < numeroreyes; i++) // destrucción de reyess 
		delete reyes[i];
	for (int i = 0; i < numeroreinas; i++) // destrucción de reinas
		delete reinas[i];
	for (int i = 0; i < numerotorres; i++) // destrucción de torres
		delete torres[i];
	for (int i = 0; i < numerocaballos; i++) // destrucción de caballos
		delete caballos[i];
	for (int i = 0; i < numeroalfiles; i++) // destrucción de alfiles
		delete alfiles[i];
	for (int i = 0; i < numeropeones; i++) // destrucción de peones
		delete peones[i];
	numero_jugadas = 1; // inicializa lista 
	numeroreyes = 0; // inicializa lista 
	numeroreinas = 0; // inicializa lista
	numerotorres = 0; // inicializa lista
	numerocaballos = 0; // inicializa lista
	numeroalfiles = 0; // inicializa lista
	numeropeones = 0; // inicializa lista
	numeroreinasblancascomidas = 0; // inicializa lista
	numeroreinasnegrascomidas = 0; // inicializa lista
	numerotorresblancascomidas = 0; // inicializa lista
	numerotorresnegrascomidas = 0; // inicializa lista
	numerocaballosblancoscomidos = 0; // inicializa lista
	numerocaballosnegroscomidos = 0; // inicializa lista
	numeroalfilesblancoscomidos = 0; // inicializa lista
	numeroalfilesnegroscomidos = 0; // inicializa lista
	numeropeonesblancoscomidos = 0; // inicializa lista
	numeropeonesnegroscomidos = 0; // inicializa lista
}
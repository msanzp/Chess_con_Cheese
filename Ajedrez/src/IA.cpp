#include "IA.h"
#include <iostream>

#define PUNTUACION_JAQUE 50
#define PUNTUACION_PEON 100
#define PUNTUACION_ALFIL 400
#define PUNTUACION_CABALLO 400
#define PUNTUACION_TORRE 500
#define PUNTUACION_REINA 800
#define PUNTUACION_JAQUE_MATE 10000

int Mapa_Caballo[8][8] = {
		{1, 2, 3, 3, 3, 3, 2, 1},
		{2, 4, 5, 5, 4, 5, 4, 2},
		{3, 5, 5, 6, 6, 5, 5, 3},
		{3, 5, 6, 6, 6, 6, 5, 3},
		{3, 5, 6, 6, 6, 6, 5, 3},
		{3, 5, 5, 6, 6, 5, 5, 3},
		{2, 4, 5, 5, 5, 5, 4, 2},
		{1, 2, 3, 3, 3, 3, 2, 1},
};

int Mapa_Rey[8][8] = {
		{2, 2, 2, 1, 1, 2, 2, 2},
		{2, 2, 2, 1, 1, 2, 2, 2},
		{3, 2, 2, 1, 1, 2, 2, 3},
		{3, 2, 2, 1, 1, 2, 2, 3},
		{4, 3, 3, 2, 2, 3, 3, 4},
		{4, 3, 3, 3, 3, 3, 3, 4},
		{5, 5, 3, 3, 3, 5, 5, 5},
		{5, 6, 4, 3, 3, 4, 6, 5},
};

int Mapa_Reina[8][8] = {
		{2, 3, 4, 4, 4, 4, 3, 2},
		{3, 5, 5, 5, 5, 5, 5, 3},
		{4, 5, 6, 6, 6, 6, 5, 4},
		{4, 5, 6, 6, 6, 6, 5, 4},
		{4, 5, 6, 6, 6, 6, 5, 4},
		{4, 5, 6, 6, 6, 6, 5, 4},
		{3, 5, 5, 5, 5, 5, 5, 3},
		{2, 3, 4, 4, 4, 4, 3, 2},
};

int Mapa_Torre[8][8] = {
		{5, 5, 5, 5, 5, 5, 5, 5},
		{5, 6, 6, 6, 6, 6, 6, 5},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{4, 4, 5, 5, 5, 5, 4, 4},
};

int Mapa_Alfil[8][8] = {
		{1, 2, 2, 2, 2, 2, 2, 1},
		{2, 3, 3, 3, 3, 3, 3, 2},
		{2, 3, 4, 5, 5, 4, 3, 2},
		{2, 4, 4, 5, 5, 4, 4, 2},
		{2, 3, 6, 4, 4, 6, 3, 2},
		{2, 5, 5, 5, 5, 5, 5, 2},
		{2, 5, 3, 3, 3, 3, 5, 2},
		{3, 2, 2, 2, 2, 2, 2, 1},
};

int Mapa_Peon[8][8] = {
		{5, 5, 5, 5, 5, 5, 5, 5},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{3, 3, 5, 5, 5, 5, 3, 3},
		{3, 3, 3, 5, 5, 3, 3, 3},
		{3, 3, 3, 5, 5, 3, 3, 3},
		{4, 3, 2, 3, 3, 2, 3, 4},
		{4, 4, 3, 1, 1, 3, 4, 4},
		{4, 4, 4, 4, 4, 4, 4, 4},
};

int  IA::ValorPrioridad(int b, int c, string tipo, char color)
{
	if (tipo == "Reina") {
		return Mapa_Reina[b - 1][c - 1];
	}
	else if (tipo == "Rey") {
		if (color == 'w') {
			return Mapa_Rey[b - 1][c - 1];
		}
		else {
			return Mapa_Rey[8 - b][8 - c];
		}
	}
	else if (tipo == "Alfil") {
		if (color == 'w') {
			return Mapa_Alfil[b - 1][c - 1];
		}
		else {
			return Mapa_Alfil[8 - b][8 - c];
		}
	}
	else if (tipo == "Caballo") {
		return Mapa_Caballo[b - 1][c - 1];
	}
	else if (tipo == "Torre") {
		if (color == 'w') {
			return Mapa_Torre[b - 1][c - 1];
		}
		else {
			return Mapa_Torre[8 - b][8 - c];
		}
	}
	else if (tipo == "Peon") {
		if (color == 'w') {
			return Mapa_Peon[b - 1][c - 1];
		}
		else {
			return Mapa_Peon[8 - b][8 - c];
		}
	}
}

int IA::puntuacion(int origen_x, int origen_y, int destino_x, int destino_y, int turno, ListaPiezas piezas, string tipo, char color) {
	int puntuacion_total = 0;
	char colorcontrario = 'w';
	if (color == 'w')
		colorcontrario = 'b';

	// primero compruebo los posibles jaques
	ListaPiezas piezas2 = (piezas);
	piezas2.ejecuta_movimientocopia(origen_x, origen_y, destino_x, destino_y, turno);
	for (int j = 0; j < piezas2.getNumeroReyes(); j++) {
		if (piezas2.getRey(j).getColor() == colorcontrario) {
			if (piezas2.comprobar_jaquemate(turno, piezas2) == true)
				puntuacion_total += PUNTUACION_JAQUE_MATE;
			if (piezas2.comprobar_jaque(piezas2.getRey(j).getX(), piezas2.getRey(j).getY(), turno) == true)
				puntuacion_total += PUNTUACION_JAQUE;
		}
	}
	piezas2.~ListaPiezas();

	// despues compruebo si puedo o no comer ficha
	for (int i = 0; i < piezas.getNumeroReinas(); i++) {
		if (piezas.getReina(i).getX() == destino_x && piezas.getReina(i).getY() == destino_y)
			puntuacion_total += PUNTUACION_REINA; // sumamos puntuación si puede comer pieza
	}
	for (int i = 0; i < piezas.getNumeroTorres(); i++) {
		if (piezas.getTorre(i).getX() == destino_x && piezas.getTorre(i).getY() == destino_y)
			puntuacion_total += PUNTUACION_TORRE;
	}
	for (int i = 0; i < piezas.getNumeroCaballos(); i++) {
		if (piezas.getCaballo(i).getX() == destino_x && piezas.getCaballo(i).getY() == destino_y)
			puntuacion_total += PUNTUACION_CABALLO;
	}
	for (int i = 0; i < piezas.getNumeroAlfiles(); i++) {
		if (piezas.getAlfil(i).getX() == destino_x && piezas.getAlfil(i).getY() == destino_y)
			puntuacion_total += PUNTUACION_ALFIL;
	}
	for (int i = 0; i < piezas.getNumeroPeones(); i++) {
		if (piezas.getPeon(i).getX() == destino_x && piezas.getPeon(i).getY() == destino_y)
			puntuacion_total += PUNTUACION_PEON;
	}

	puntuacion_total += ValorPrioridad(destino_x, destino_y, tipo, color);

	return puntuacion_total;
}

Jugada IA::comparacion(int origen_x, int origen_y, int destino_x, int destino_y, int puntuacion, Jugada mejor) {
	Jugada actual = { 0,0,0,0,0 };
	if (mejor.origen_x == 0 && mejor.origen_y == 0 && mejor.destino_x == 0 && mejor.destino_y == 0) {
		actual.origen_x = origen_x;
		actual.origen_y = origen_y;
		actual.destino_x = destino_x;
		actual.destino_y = destino_y;
		actual.puntuacion = puntuacion;
		return actual;
	}
	if (puntuacion > mejor.puntuacion) {
		actual.origen_x = origen_x;
		actual.origen_y = origen_y;
		actual.destino_x = destino_x;
		actual.destino_y = destino_y;
		actual.puntuacion = puntuacion;
		return actual;
	}
	return mejor;
}

Jugada IA::analisis_jugada(int turno, ListaPiezas piezas) {
	Jugada mejor_jugada = {0,0,0,0,-20000};
	int puntuacion_jugada_mia = 0, puntuacion_mejor_jugada_oponente = 0, puntuacion_total;
	char color = 'w';
	char colorcontrario = 'b';
	int turnocontrario = 1;
	if (turno == 1)	{
		color = 'b';
		colorcontrario = 'w';
		turnocontrario = 0;
	}

	if (turno == 0 && piezas.getNumeroJugadas() == 1)
		mejor_jugada = { 5,2,5,3,10 };
	if (turno == 1 && piezas.getNumeroJugadas() == 2)
		mejor_jugada = { 5,7,5,6,10 };
	if (turno == 0 && piezas.getNumeroJugadas() == 3)
		mejor_jugada = { 7,1,6,3,10 };
	if (turno == 1 && piezas.getNumeroJugadas() == 4)
		mejor_jugada = { 7,8,6,6,10 };
	if (turno == 0 && piezas.getNumeroJugadas() == 5)
		mejor_jugada = { 2,1,3,3,10 };
	if (turno == 1 && piezas.getNumeroJugadas() == 6)
		mejor_jugada = { 2,8,3,6,10 };

	for (int a = 0; a < piezas.getNumeroCaballos(); a++) {
		if (piezas.getCaballo(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, turno, piezas) == true) {
						puntuacion_jugada_mia = puntuacion(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, turnocontrario, piezas, "Caballo", color);
						ListaPiezas piezas2 = (piezas);
						piezas2.ejecuta_movimientocopia(piezas2.getCaballo(a).getX(), piezas2.getCaballo(a).getY(), b, c, turno);
						puntuacion_mejor_jugada_oponente = mejor_jugada_oponente(turno, piezas2);
						piezas2.~ListaPiezas();
						puntuacion_total = puntuacion_jugada_mia - puntuacion_mejor_jugada_oponente;
						mejor_jugada = comparacion(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, puntuacion_total, mejor_jugada);
					}
				}
			}
		}
	}
	
	for (int a = 0; a < piezas.getNumeroPeones(); a++) {
		if (piezas.getPeon(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, turno, piezas) == true) {
						puntuacion_jugada_mia = puntuacion(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, turnocontrario, piezas, "Peon", color);
						ListaPiezas piezas2 = (piezas);
						piezas2.ejecuta_movimientocopia(piezas2.getPeon(a).getX(), piezas2.getPeon(a).getY(), b, c, turno);
						puntuacion_mejor_jugada_oponente = mejor_jugada_oponente(turno, piezas2);
						piezas2.~ListaPiezas();
						puntuacion_total = puntuacion_jugada_mia - puntuacion_mejor_jugada_oponente;
						mejor_jugada = comparacion(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, puntuacion_total, mejor_jugada);
					}
				}
			}
		}
	}

	for (int a = 0; a < piezas.getNumeroAlfiles(); a++) {
		if (piezas.getAlfil(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, turno, piezas) == true) {
						puntuacion_jugada_mia = puntuacion(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, turnocontrario, piezas, "Alfil", color);
						ListaPiezas piezas2 = (piezas);
						piezas2.ejecuta_movimientocopia(piezas2.getAlfil(a).getX(), piezas2.getAlfil(a).getY(), b, c, turno);
						puntuacion_mejor_jugada_oponente = mejor_jugada_oponente(turno, piezas2);
						piezas2.~ListaPiezas();
						puntuacion_total = puntuacion_jugada_mia - puntuacion_mejor_jugada_oponente;
						mejor_jugada = comparacion(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, puntuacion_total, mejor_jugada);
					}
				}
			}
		}
	}

	for (int a = 0; a < piezas.getNumeroTorres(); a++) {
		if (piezas.getTorre(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, turno, piezas) == true) {
						puntuacion_jugada_mia = puntuacion(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, turnocontrario, piezas, "Torre", color);
						ListaPiezas piezas2 = (piezas);
						piezas2.ejecuta_movimientocopia(piezas2.getTorre(a).getX(), piezas2.getTorre(a).getY(), b, c, turno);
						puntuacion_mejor_jugada_oponente = mejor_jugada_oponente(turno, piezas2);
						piezas2.~ListaPiezas();
						puntuacion_total = puntuacion_jugada_mia - puntuacion_mejor_jugada_oponente;
						mejor_jugada = comparacion(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, puntuacion_total, mejor_jugada);
					}
				}
			}
		}
	}

	for (int a = 0; a < piezas.getNumeroReinas(); a++) {
		if (piezas.getReina(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, turno, piezas) == true) {
						puntuacion_jugada_mia = puntuacion(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, turnocontrario, piezas, "Reina", color);
						ListaPiezas piezas2 = (piezas);
						piezas2.ejecuta_movimientocopia(piezas2.getReina(a).getX(), piezas2.getReina(a).getY(), b, c, turno);
						puntuacion_mejor_jugada_oponente = mejor_jugada_oponente(turno, piezas2);
						piezas2.~ListaPiezas();
						puntuacion_total = puntuacion_jugada_mia - puntuacion_mejor_jugada_oponente;
						mejor_jugada = comparacion(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, puntuacion_total, mejor_jugada);
					}
				}
			}
		}
	}

	for (int a = 0; a < piezas.getNumeroReyes(); a++) {
		if (piezas.getRey(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, turno, piezas) == true) {
						puntuacion_jugada_mia = puntuacion(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, turnocontrario, piezas, "Rey", color);
						ListaPiezas piezas2 = (piezas);
						piezas2.ejecuta_movimientocopia(piezas2.getRey(a).getX(), piezas2.getRey(a).getY(), b, c, turno);
						puntuacion_mejor_jugada_oponente = mejor_jugada_oponente(turno, piezas2);
						piezas2.~ListaPiezas();
						puntuacion_total = puntuacion_jugada_mia - puntuacion_mejor_jugada_oponente;
						mejor_jugada = comparacion(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, puntuacion_total, mejor_jugada);
					}
				}
			}
		}
	}
	
	return mejor_jugada;
}

int IA::mejor_jugada_oponente(int turno, ListaPiezas piezas) {
	int puntuacion_mejor_jugada = 0, puntuacion_jugada = 0;
	char colorcontrario = 'b';
	int turnocontrario = 1;
	if (turno == 1) {
		colorcontrario = 'w';
		turnocontrario = 0;
	}

	for (int a = 0; a < piezas.getNumeroReyes(); a++) {
		if (piezas.getRey(a).getColor() == colorcontrario) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, turnocontrario, piezas) == true) {
						puntuacion_jugada = puntuacion(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, turno, piezas, "Rey", colorcontrario);
						if (puntuacion_jugada > puntuacion_mejor_jugada)
							puntuacion_mejor_jugada = puntuacion_jugada;
					}
				}
			}
		}
	}

	for (int a = 0; a < piezas.getNumeroReinas(); a++) {
		if (piezas.getReina(a).getColor() == colorcontrario) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, turnocontrario, piezas) == true) {
						puntuacion_jugada = puntuacion(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, turno, piezas, "Reina", colorcontrario);
						if (puntuacion_jugada > puntuacion_mejor_jugada)
							puntuacion_mejor_jugada = puntuacion_jugada;
					}
				}
			}
		}
	}

	for (int a = 0; a < piezas.getNumeroTorres(); a++) {
		if (piezas.getTorre(a).getColor() == colorcontrario) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, turnocontrario, piezas) == true) {
						puntuacion_jugada = puntuacion(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, turno, piezas, "Torre", colorcontrario);
						if (puntuacion_jugada > puntuacion_mejor_jugada)
							puntuacion_mejor_jugada = puntuacion_jugada;
					}
				}
			}
		}
	}

	for (int a = 0; a < piezas.getNumeroCaballos(); a++) {
		if (piezas.getCaballo(a).getColor() == colorcontrario) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, turnocontrario, piezas) == true) {
						puntuacion_jugada = puntuacion(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, turno, piezas, "Caballo", colorcontrario);
						if (puntuacion_jugada > puntuacion_mejor_jugada)
							puntuacion_mejor_jugada = puntuacion_jugada;
					}
				}
			}
		}
	}

	for (int a = 0; a < piezas.getNumeroAlfiles(); a++) {
		if (piezas.getAlfil(a).getColor() == colorcontrario) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, turnocontrario, piezas) == true) {
						puntuacion_jugada = puntuacion(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, turno, piezas, "Alfil", colorcontrario);
						if (puntuacion_jugada > puntuacion_mejor_jugada)
							puntuacion_mejor_jugada = puntuacion_jugada;
					}
				}
			}
		}
	}

	for (int a = 0; a < piezas.getNumeroPeones(); a++) {
		if (piezas.getPeon(a).getColor() == colorcontrario) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, turnocontrario, piezas) == true) {
						puntuacion_jugada = puntuacion(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, turno, piezas, "Peon", colorcontrario);
						if (puntuacion_jugada > puntuacion_mejor_jugada)
							puntuacion_mejor_jugada = puntuacion_jugada;
					}
				}
			}
		}
	}
	return puntuacion_mejor_jugada;
}
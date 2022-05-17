#include "IA.h"
#include <iostream>

#define PUNTUACION_PEON 100
#define PUNTUACION_ALFIL 200
#define PUNTUACION_CABALLO 200
#define PUNTUACION_TORRE 300
#define PUNTUACION_REINA 400

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

int Mapa_Rey_Blanco[8][8] = {
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

int Mapa_Torre_Blanco[8][8] = {
		{5, 5, 5, 5, 5, 5, 5, 5},
		{5, 6, 6, 6, 6, 6, 6, 5},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{3, 4, 4, 4, 4, 4, 4, 3},
		{4, 4, 5, 5, 5, 5, 4, 4},
};

int Mapa_Alfil_Blanco[8][8] = {
		{1, 2, 2, 2, 2, 2, 2, 1},
		{2, 3, 3, 3, 3, 3, 3, 2},
		{2, 3, 4, 5, 5, 4, 3, 2},
		{2, 4, 4, 5, 5, 4, 4, 2},
		{2, 3, 6, 4, 4, 6, 3, 2},
		{2, 5, 5, 5, 5, 5, 5, 2},
		{2, 5, 3, 3, 3, 3, 5, 2},
		{3, 2, 2, 2, 2, 2, 2, 1},
};

int Mapa_Peon_Blanco[8][8] = {
		{5, 5, 5, 5, 5, 5, 5, 5},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{3, 3, 5, 5, 5, 5, 3, 3},
		{3, 3, 3, 5, 5, 3, 3, 3},
		{3, 3, 3, 5, 5, 3, 3, 3},
		{4, 3, 2, 3, 3, 2, 3, 4},
		{4, 4, 3, 1, 1, 3, 4, 4},
		{4, 4, 4, 4, 4, 4, 4, 4},
};

int  IA :: ValorPrioridad(int b, int c, string tipo, char color)
{
	if (tipo == "Reina") {
		return Mapa_Reina[b - 1][c - 1];
	}
	else if (tipo == "Rey") {
		if (color == 'w') {
			return Mapa_Rey_Blanco[b - 1][c - 1];
		}
		else {
			return Mapa_Rey_Blanco[8 - b][8 - c];
		}
	}
	else if (tipo == "Alfil") {
		if (color == 'w') {
			return Mapa_Alfil_Blanco[b - 1][c - 1];
		}
		else {
			return Mapa_Alfil_Blanco[8 - b][8 - c];
		}
	}
	else if (tipo == "Caballo") {
		return Mapa_Caballo[b - 1][c - 1];
	}
	else if (tipo == "Torre") {
		if (color == 'w') {
			return Mapa_Torre_Blanco[b - 1][c - 1];
		}
		else {
			return Mapa_Torre_Blanco[8 - b][8 - c];
		}
	}
	else if (tipo == "Peon") {
		if (color == 'w') {
			return Mapa_Peon_Blanco[b - 1][c - 1];
		}
		else {
			return Mapa_Peon_Blanco[8 - b][8 - c];
		}
	}
}

int IA::puntuacion(int destino_x, int destino_y, ListaPiezas piezas, string tipo, char color) {

	/*	
		Primero se evalua las puntuaciones de una jugada en la que se come
		comprobando que hay una pieza en la casilla de destino
		y añadiendola comparacioon de prioridad de posiciones
	*/

	for (int i = 0; i < piezas.getNumeroReinas(); i++) {
		if (piezas.getReina(i).getX() == destino_x && piezas.getReina(i).getY() == destino_y)
			return PUNTUACION_REINA + ValorPrioridad(destino_x, destino_y, tipo, color);
	}
	for (int i = 0; i < piezas.getNumeroTorres(); i++) {
		if (piezas.getTorre(i).getX() == destino_x && piezas.getTorre(i).getY() == destino_y)
			return PUNTUACION_TORRE + ValorPrioridad(destino_x, destino_y, tipo, color);
	}
	for (int i = 0; i < piezas.getNumeroCaballos(); i++) {
		if (piezas.getCaballo(i).getX() == destino_x && piezas.getCaballo(i).getY() == destino_y)
			return PUNTUACION_CABALLO + ValorPrioridad(destino_x, destino_y, tipo, color);
	}
	for (int i = 0; i < piezas.getNumeroAlfiles(); i++) {
		if (piezas.getAlfil(i).getX() == destino_x && piezas.getAlfil(i).getY() == destino_y)
			return PUNTUACION_ALFIL + ValorPrioridad(destino_x, destino_y, tipo, color);
	}
	for (int i = 0; i < piezas.getNumeroPeones(); i++) {
		if (piezas.getPeon(i).getX() == destino_x && piezas.getPeon(i).getY() == destino_y)
			return PUNTUACION_PEON + ValorPrioridad(destino_x, destino_y, tipo, color);
	}

	/*
		Al llegar hasta este punto la función ha comprobado
		que no va a comer y va devolver la valoración de la 
		jugada en cuanto a posiciones favorables 
	*/

	return ValorPrioridad(destino_x, destino_y, tipo, color);


}

Jugada IA::comparacion(int origen_x, int origen_y, int destino_x, int destino_y, int puntuacion, Jugada mejor) {
	Jugada actual = { 0,0,0,0,0 };
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
	Jugada mejor_jugada = { 0,0,0,0,0 };
	int puntuacion_jugada_1, puntuacion_jugada_2, puntuacion_total;
	int turno_contrario = 1;
	char color = 'w'; 
	char color_contrario = 'b';
	if (turno == 1) {
		turno_contrario = 0;
		color = 'b';
		color_contrario = 'w';
	}
	// dado que al principio no va a poder tomar una decisión, vamos a poner que sus 4 primeros movimientos siempre sean los mismos
	if (turno == 0 && piezas.getNumeroJugadas() == 1)
		return mejor_jugada = { 5,2,5,4,0 };
	if (turno == 1 && piezas.getNumeroJugadas() == 2)
		return mejor_jugada = { 5,7,5,5,0 };
	if (turno == 0 && piezas.getNumeroJugadas() == 3)
		return mejor_jugada = { 7,1,8,3,0 };
	if (turno == 1 && piezas.getNumeroJugadas() == 4)
		return mejor_jugada = { 7,8,8,6,0 };
	if (turno == 0 && piezas.getNumeroJugadas() == 5)
		return mejor_jugada = { 6,1,4,3,0 };
	if (turno == 1 && piezas.getNumeroJugadas() == 6)
		return mejor_jugada = { 6,8,4,6,0 };
	if (turno == 0 && piezas.getNumeroJugadas() == 7)
		return mejor_jugada = { 5,1,7,1, };
	if (turno == 1 && piezas.getNumeroJugadas() == 8)
		return mejor_jugada = { 5,8,7,8,0 };

	// una vez ya hemos hecho los primeros movimientos, empezamos a analizar los movimientos
		
	for (int a = 0; a < piezas.getNumeroReyes(); a++) {
		if (piezas.getRey(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, turno) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, piezas2, "Rey", color);
						piezas2.ejecuta_movimientocopia(piezas2.getRey(a).getX(), piezas2.getRey(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Rey", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroReinas(); d++) {
							if(piezas2.getReina(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Reina", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroTorres(); d++) {
							if (piezas2.getTorre(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Torre", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroCaballos(); d++) {
							if (piezas2.getCaballo(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Caballo", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroAlfiles(); d++) {
							if (piezas2.getAlfil(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Alfil", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroPeones(); d++) {
							if (piezas2.getPeon(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Peon", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (int a = 0; a < piezas.getNumeroReinas(); a++) {
		if (piezas.getReina(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, turno) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, piezas2, "Reina", color);
						piezas2.ejecuta_movimientocopia(piezas2.getReina(a).getX(), piezas2.getReina(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Rey", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroReinas(); d++) {
							if (piezas2.getReina(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Reina", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroTorres(); d++) {
							if (piezas2.getTorre(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Torre", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroCaballos(); d++) {
							if (piezas2.getCaballo(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Caballo", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroAlfiles(); d++) {
							if (piezas2.getAlfil(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Alfil", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroPeones(); d++) {
							if (piezas2.getPeon(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Peon", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (int a = 0; a < piezas.getNumeroTorres(); a++) {
		if (piezas.getTorre(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, turno) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, piezas2, "Reina", color);
						piezas2.ejecuta_movimientocopia(piezas2.getTorre(a).getX(), piezas2.getTorre(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Rey", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroReinas(); d++) {
							if (piezas2.getReina(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Reina", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroTorres(); d++) {
							if (piezas2.getTorre(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Torre", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroCaballos(); d++) {
							if (piezas2.getCaballo(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Caballo", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroAlfiles(); d++) {
							if (piezas2.getAlfil(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Alfil", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroPeones(); d++) {
							if (piezas2.getPeon(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Peon", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (int a = 0; a < piezas.getNumeroCaballos(); a++) {
		if (piezas.getCaballo(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, turno) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, piezas2, "Caballo", color);
						piezas2.ejecuta_movimientocopia(piezas2.getCaballo(a).getX(), piezas2.getCaballo(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Rey", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroReinas(); d++) {
							if (piezas2.getReina(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Reina", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroTorres(); d++) {
							if (piezas2.getTorre(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Torre", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroCaballos(); d++) {
							if (piezas2.getCaballo(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Caballo", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroAlfiles(); d++) {
							if (piezas2.getAlfil(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Alfil", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroPeones(); d++) {
							if (piezas2.getPeon(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Peon", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (int a = 0; a < piezas.getNumeroAlfiles(); a++) {
		if (piezas.getAlfil(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, turno) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, piezas2, "Alfil", color);
						piezas2.ejecuta_movimientocopia(piezas2.getAlfil(a).getX(), piezas2.getAlfil(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Rey", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroReinas(); d++) {
							if (piezas2.getReina(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Reina", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroTorres(); d++) {
							if (piezas2.getTorre(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Torre", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroCaballos(); d++) {
							if (piezas2.getCaballo(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Caballo", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroAlfiles(); d++) {
							if (piezas2.getAlfil(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Alfil", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroPeones(); d++) {
							if (piezas2.getPeon(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Peon", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (int a = 0; a < piezas.getNumeroPeones(); a++) {
		if (piezas.getPeon(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, turno) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, piezas2, "Peon", color);
						piezas2.ejecuta_movimientocopia(piezas2.getPeon(a).getX(), piezas2.getPeon(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Rey", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroReinas(); d++) {
							if (piezas2.getReina(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Reina", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroTorres(); d++) {
							if (piezas2.getTorre(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Torre", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroCaballos(); d++) {
							if (piezas2.getCaballo(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Caballo", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroAlfiles(); d++) {
							if (piezas2.getAlfil(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Alfil", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
						for (int d = 0; d < piezas2.getNumeroPeones(); d++) {
							if (piezas2.getPeon(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, piezas2, "Peon", color_contrario);
											puntuacion_total = puntuacion_jugada_1 - puntuacion_jugada_2;
											mejor_jugada = comparacion(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, puntuacion_total, mejor_jugada);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return mejor_jugada;
}
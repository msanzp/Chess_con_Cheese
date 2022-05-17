#include "IA.h"

#define PUNTUACION_PEON 100
#define PUNTUACION_ALFIL 200
#define PUNTUACION_CABALLO 200
#define PUNTUACION_TORRE 300
#define PUNTUACION_REINA 400
#define PUNTUACION_JAQUEMATE 100000

int IA::puntuacion(int destino_x, int destino_y, int turno, ListaPiezas piezas) {
	int puntuacion_jugada = 0;

	if (piezas.comprobar_jaquemate(turno, piezas) == true)
		puntuacion_jugada += PUNTUACION_JAQUEMATE;

	for (int i = 0; i < piezas.getNumeroReinas(); i++) {
		if (piezas.getReina(i).getX() == destino_x && piezas.getReina(i).getY() == destino_y)
			puntuacion_jugada += PUNTUACION_REINA;
	}
	for (int i = 0; i < piezas.getNumeroTorres(); i++) {
		if (piezas.getTorre(i).getX() == destino_x && piezas.getTorre(i).getY() == destino_y)
			puntuacion_jugada += PUNTUACION_TORRE;
	}
	for (int i = 0; i < piezas.getNumeroCaballos(); i++) {
		if (piezas.getCaballo(i).getX() == destino_x && piezas.getCaballo(i).getY() == destino_y)
			puntuacion_jugada += PUNTUACION_CABALLO;
	}
	for (int i = 0; i < piezas.getNumeroAlfiles(); i++) {
		if (piezas.getAlfil(i).getX() == destino_x && piezas.getAlfil(i).getY() == destino_y)
			puntuacion_jugada += PUNTUACION_ALFIL;
	}
	for (int i = 0; i < piezas.getNumeroPeones(); i++) {
		if (piezas.getPeon(i).getX() == destino_x && piezas.getPeon(i).getY() == destino_y)
			puntuacion_jugada += PUNTUACION_PEON;
	}
	return puntuacion_jugada;
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
		return mejor_jugada = { 5,1,7,1,0 };
	if (turno == 1 && piezas.getNumeroJugadas() == 8)
		return mejor_jugada = { 5,8,7,8,0 };

	// una vez ya hemos hecho los primeros movimientos, empezamos a analizar los movimientos
		
	for (int a = 0; a < piezas.getNumeroReyes(); a++) {
		if (piezas.getRey(a).getColor() == color) {
			for (int b = 1; b < 9; b++) {
				for (int c = 1; c < 9; c++) {
					if (piezas.comprobar_movimiento(piezas.getRey(a).getX(), piezas.getRey(a).getY(), b, c, turno, piezas) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b,c,turno,piezas2);
						piezas2.ejecuta_movimientocopia(piezas2.getRey(a).getX(), piezas2.getRey(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
					if (piezas.comprobar_movimiento(piezas.getReina(a).getX(), piezas.getReina(a).getY(), b, c, turno, piezas) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, turno, piezas2);
						piezas2.ejecuta_movimientocopia(piezas2.getReina(a).getX(), piezas2.getReina(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
					if (piezas.comprobar_movimiento(piezas.getTorre(a).getX(), piezas.getTorre(a).getY(), b, c, turno, piezas) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, turno, piezas2);
						piezas2.ejecuta_movimientocopia(piezas2.getTorre(a).getX(), piezas2.getTorre(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
					if (piezas.comprobar_movimiento(piezas.getCaballo(a).getX(), piezas.getCaballo(a).getY(), b, c, turno, piezas) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, turno, piezas2);
						piezas2.ejecuta_movimientocopia(piezas2.getCaballo(a).getX(), piezas2.getCaballo(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
					if (piezas.comprobar_movimiento(piezas.getAlfil(a).getX(), piezas.getAlfil(a).getY(), b, c, turno, piezas) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, turno, piezas2);
						piezas2.ejecuta_movimientocopia(piezas2.getAlfil(a).getX(), piezas2.getAlfil(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
					if (piezas.comprobar_movimiento(piezas.getPeon(a).getX(), piezas.getPeon(a).getY(), b, c, turno, piezas) == true) {
						ListaPiezas piezas2 = (piezas);
						puntuacion_jugada_1 = puntuacion(b, c, turno, piezas2);
						piezas2.ejecuta_movimientocopia(piezas2.getPeon(a).getX(), piezas2.getPeon(a).getY(), b, c, turno);
						for (int d = 0; d < piezas2.getNumeroReyes(); d++) {
							if (piezas2.getRey(d).getColor() == color_contrario) {
								for (int e = 1; e < 9; e++) {
									for (int f = 1; f < 9; f++) {
										if (piezas2.comprobar_movimiento(piezas2.getRey(d).getX(), piezas2.getRey(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getReina(d).getX(), piezas2.getReina(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getTorre(d).getX(), piezas2.getTorre(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getCaballo(d).getX(), piezas2.getCaballo(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getAlfil(d).getX(), piezas2.getAlfil(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
										if (piezas2.comprobar_movimiento(piezas2.getPeon(d).getX(), piezas2.getPeon(d).getY(), e, f, turno_contrario, piezas) == true) {
											puntuacion_jugada_2 = puntuacion(e, f, turno_contrario, piezas2);
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
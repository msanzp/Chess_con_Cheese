#pragma once
#include "ListaPiezas.h"

struct Jugada {
	int origen_x;
	int origen_y;
	int destino_x;
	int destino_y;
	int puntuacion; // sirve para determinar si una jugada es mejor que otra o no
};

class IA {
public:
	static int puntuacion(int destino_x, int destino_y, int turno, ListaPiezas piezas); // sirve para asociar una puntuación si como pieza
	static Jugada comparacion(int origen_x, int origen_y, int destino_x, int destino_y, int puntuacion, Jugada mejor); // sirve para comparar 2 jugadas a ver cual es mejor
	static Jugada analisis_jugada(int turno, ListaPiezas piezas); // sirve para analizar 1 turno tuyo y otro del rival
};
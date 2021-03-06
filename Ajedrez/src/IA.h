#pragma once
#include "ListaPiezas.h"
#include <string>

struct Jugada {
	int origen_x;
	int origen_y;
	int destino_x;
	int destino_y;
	int puntuacion; // sirve para determinar si una jugada es mejor que otra o no
};

class IA {
private:
	static int ValorPrioridad(int b, int c, string tipo, char color); // Asocia un mapa de zonas favorables al movimiento de las piezas
public:
	static int puntuacion(int origen_x, int origen_y, int destino_x, int destino_y, int turno, ListaPiezas piezas, string tipo, char color); // sirve para asociar una puntuación a cada jugada
	static Jugada comparacion(int origen_x, int origen_y, int destino_x, int destino_y, int puntuacion, Jugada mejor); // sirve para comparar 2 jugadas a ver cual es mejor
	static Jugada analisis_jugada(int turno, ListaPiezas piezas);
	static int mejor_jugada_oponente(int turno, ListaPiezas piezas);
};
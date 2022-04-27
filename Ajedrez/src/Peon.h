#pragma once
#include "Pieza.h"
#include <math.h>
#include "freeglut.h"

class Peon : public Pieza {
private:
	bool PrimeraJugada = true;//Cuando no se ha movido el peon este valor es true
public:
	Peon(int x, int y, char c);
	void dibuja();
	bool comprobar_movimiento(int x, int y); // sirve para determinar si el movimiento a realizar es o no válido
	void CambiaPrimeraJugada();//Cuando se mueve una vez el peon se cambia PrimeraJugada a false
};
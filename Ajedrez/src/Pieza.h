#pragma once
#include "ETSIDI.h"

class Pieza {
protected:
	int posX;
	int posY;
	char color; //sirve para identificar si las piezas son blancas o negras
public:
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	char getColor();
};
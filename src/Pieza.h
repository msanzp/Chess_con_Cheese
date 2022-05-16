#pragma once
#include "ETSIDI.h"
#include "freeglut.h"
#include <fstream>
#include <string>

using namespace ETSIDI;

class Pieza {
protected:
	int posX;
	int posY;
	char color; //sirve para identificar si las piezas son blancas o negras
	int tipo; // 0=rey, 1=reina, 2=alfil, 3=peon, 4=caballo, 5=torre
public:

	void dibuja2D(const char foto1[], const char foto2[], const char foto3[], const char foto4[], const char foto5[], const char foto6[], int pieza_seleccionadaX, int pieza_seleccionadaY);
	void dibuja3D(const char foto1[]);

	void dibuja2D_borrada(GLfloat posicion_blacas, GLfloat posicion_negras);

	// funciones set y get que vamos a necesitar
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	char getColor();

	int esNegra();
	int esBlanca();

	int esRey();
	int esReina();
	int esAlfil();
	int esPeon();
	int esCaballo();
	int esTorre();
};
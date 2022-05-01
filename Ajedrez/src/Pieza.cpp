#include "Pieza.h"

void Pieza::setX(int x) {
	posX = x;
}

void Pieza::setY(int y) {
	posY = y;
}

int Pieza::getX() {
	return posX;
}

int Pieza::getY() {
	return posY;
}

char Pieza::getColor() {
	return color;
}
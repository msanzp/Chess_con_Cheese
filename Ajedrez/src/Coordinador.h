#pragma once
#include <Tablero.h>

class Coordinador {
private:
	int turno = 0;  // sirve para controlar quien juega, 0 juegan blancas y 1 juegan negras
	int opcion_juego; // valdrá 1 para el modo jugador vs jugador y 2 para el modo jugador vs máquina
	int opcion_color; // valdrá 1 si quiero jugar con blancas y 2 si quiero jugar con negras
	int opcion_graficos; // valdrá 1 para el juego 2D y 2 para el juego 3D
protected:
	Tablero tablero;
	enum Estado { INSTRUCCIONES, MENU, JUEGO };
	Estado estado;
public:
	Coordinador();
	~Coordinador();

	// para controlar el desarrollo de la partida
	void partida();

	// funciones set
	void setCoordenadaX_origen(int x) { tablero.setCoordenadaX_origen(tablero.coordenadaX(x)); }
	void setCoordenadaY_origen(int y) { tablero.setCoordenadaY_origen(tablero.coordenadaY(y)); }
	void setCoordenadaX_destino(int x) { tablero.setCoordenadaX_destino(tablero.coordenadaX(x)); }
	void setCoordenadaY_destino(int y) { tablero.setCoordenadaY_destino(tablero.coordenadaY(y)); }

	// funciones get
	bool getCasilla_origen() { return tablero.getCasilla_origen(); }
	bool getCasilla_destino() { return tablero.getCasilla_destino(); }

	// en el juego van a existir 3 menus de juego, por lo que vamos a crear 3 pantallas diferentes
	void dibuja();
	void dibujainstrucciones();
	void dibujaelecciones();

	// estas variables sirven para controlar el click por ratón
	int getEstado(); // sirve para saber en que parte/menu del juego nos encontramos
	void opcionSeleccionada(int x, int y); // sirve para navegar por los menus usando el ratón
};
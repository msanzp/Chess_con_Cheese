#include "Tablero.h"

void Tablero::GameStart(string eleccionJuego, string eleccionColor) // Funcion que inicia el juego
{ 
// Inicializa el tablero con los jugadores en las posiciones, define los contadores de juego

}

void Tablero::Imprimir() // Función que pone el tablero en pantalla
{
// Imprime el tablero en pantalla usando la matriz de juego TableroJuego
// Posiblemente se puede hacer una función que haga el movimiento de las piezas de forma animada,
// caso en que necesitaria la jugada como parámetro
}

string Tablero::CompruebaStatus() // Función que comprueba el estatus del juego, si está en juego o finalizado
{
// Comprueba el estatus del juego:
// Si está en juego, devuelve "en juego"
// Si está finalizado, devuelve el ganador o empate
// Debe devolver una string para poder ser comparada
}

void Tablero::Jugada() // Función que realiza la jugada
{
// Recibe la jugada del jugador mediante interfaz gráfica
// Comprueba si la jugada es válida
// Si es válida, realiza el movimiento
// Si no es válida, muestra un mensaje de error
// Utiliza la variable "QuienJuega" para saber quien juega
// Utiliza la variable "Roque" para saber si se puede hacer roque
// Utiliza la variable "EnPassant" para saber si se puede hacer en passant
}

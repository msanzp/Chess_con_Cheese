#include "Tablero.h"

void Tablero::GameStart(string EleccionJuego, string EleccionColor) // Funcion que inicia el juego
{
    TipoJuego = EleccionJuego;
    if (TipoJuego != "Dos Jugadores")
        Jugador = EleccionColor;
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
// Devuelve uno de estos valores {"En Juego", "Blancas Ganan", "Negras Ganan", "Empate"}
}

string ObtieneJugada() // Función que obtiene la jugada del jugador
{
// Muestra mensaje pidiendo jugada
// Recibe la jugada del jugador (en formato válido)
// Comprueba si la jugada es válida
// Si no es válida, muestra un mensaje de error y vuelve a pedir
// Ejemplo de respuesta: "e4e5"

// Utiliza la variable "QuienJuega" para saber quien juega
// Utiliza la variable "Roque" para saber si se puede hacer roque
// Utiliza la variable "EnPassant" para saber si se puede hacer en passant

// Dentro de esta función se creará otra para la obtención de la jugada del API,
// implementando la librería de conversion a FEN y la de interacción con el API
} 

void Tablero::Jugada() // Función que recibe la jugada, comprueba si es valida y realiza la jugada
{
string Movimiento = ObtieneJugada();
// Ejecuta movimiento en la matriz de juego 
//(mueve pieza a la casilla final y pone 0 en la casilla inicial o mueve rey y torre para posicion de roque o mueve peon para posicion de en passant y come el anterior)

// al terminar la jugada, se actualiza las variables de juego

}

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

// Dentro de esta función se usará otra para la obtención de la jugada del API,
// implementando la librería de conversion a FEN y la de interacción con el API
} 

void Tablero::Jugada() // Función que recibe la jugada, comprueba si es valida y realiza la jugada
{
string Movimiento = ObtieneJugada();
// Ejecuta movimiento en la matriz de juego 
// Comprueba tipo de jugada (roque, en passant, normal)
// (para roque, movimiento de rey blanco e1c1 o e1f1, movimiento de rey negro e8c8 o e8f8) (para en passant movimiento de peón en diagonal hacia EnPassant)
// Si es un roque mueve rey y torre para posicion de roque
// Si es una jugada normal mueve pieza a la casilla final y pone 0 en la casilla inicial 
// Si es En Passant mueve peon para posicion de en passant y come el peon que está detrás (solo se hace en passant en las filas de E y C)

// Actualiza la variable "QuienJuega" (Cambia de "w" a "b" o viceversa)
// Actualiza la variable "Roque" si se han cambiado las condiciones (movimiento de rey o torre, o si se ha hecho roque) (Atención, una jugada que impida el roque temporariamente no debe alterar esta variable)
// Actualiza la variable "EnPassant" (si hubo movimiento de dos casillas de otro peon hay nuevo valor, si no vuelve a "")

}

#include "Tablero.h"

void Tablero::Jugar(string eleccionJuego, string eleccionColor) // Funcion que inicia el juego
{ 

}
void Tablero::Imprimir() // Función que pone el tablero en pantalla
{

}
string Tablero::CompruebaStatus() // Función que comprueba el estatus del juego, si está en juego o finalizado
{

}
void Tablero::Jugada() // Función que realiza la jugada
{

}
Tablero :: Tablero() // Constructor
{
 TableroJuego = {
    {"r", "n", "b", "q", "k", "b", "n", "r"} ,   /*  initializers for row indexed by 0 -- linea 8 del tablero*/
    {"p", "p", "p", "p", "p", "p", "p", "p"} ,   /*  initializers for row indexed by 1  -- linea 7 del tablero*/
    {"0", "0", "0", "0", "0", "0", "0", "0"} ,   /*  initializers for row indexed by 2  -- linea 6 del tablero*/
    {"0", "0", "0", "0", "0", "0", "0", "0"} ,   /*  initializers for row indexed by 3  -- linea 5 del tablero*/
    {"0", "0", "0", "0", "0", "0", "0", "0"} ,   /*  initializers for row indexed by 4  -- linea 4 del tablero*/
    {"0", "0", "0", "0", "0", "0", "0", "0"} ,   /*  initializers for row indexed by 5  -- linea 3 del tablero*/
    {"P", "P", "P", "P", "P", "P", "P", "P"} ,   /*  initializers for row indexed by 6  -- linea 2 del tablero*/
    {"R", "N", "B", "Q", "K", "B", "N", "R"} ,   /*  initializers for row indexed by 7  -- linea 1 del tablero*/
    };
}
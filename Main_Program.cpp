// Chess main program

//#include libraries
#include "SplashScreen.h"
#include "Menus.h"
#include "Tablero.h"

string EleccionJuego;
string EleccionColor;
Tablero tablero;

void main()
{

    SplashScreen();
    EleccionJuego = Menu_TipoJuego(); // Seleccion de tipo de juego
    if (EleccionJuego != "Dos Jugadores"){ // Si el tipo de juego es contra máquina
        EleccionColor = Menu_Color(); // Seleccion de color
    }else {
        EleccionColor = "Dos Jugadores"; // Si el tipo de juego es contra jugador, no se necesita seleccionar color
    }
    
    tablero.GameStart(EleccionJuego, EleccionColor); // Inicializa el juego 
    tablero.Imprimir(); // Pone el tablero en pantalla

    while (tablero.CompruebaStatus() == "en juego") // Mientras el juego no termine
    {
        tablero.Jugada(); 
        tablero.Imprimir();
    }

    MensajeFinal(tablero.CompruebaStatus()); // Muestra el mensaje de finalización del juego, ganador o empate
}
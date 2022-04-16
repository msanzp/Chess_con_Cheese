#include <string>
using namespace std;
 
 class Tablero{
     private:
            string TableroJuego[8][8]; // Tablero de juego
            string Status; // Estatus del juego
            string QuienJuega; 
            string TipoJuego; // Tipo de juego, contra jugador o contra máquina
            string Jugador; 
            string Jugador2; 
    public:
            void Tablero::Jugar(string EleccionJuego,string EleccionColor); // Función que inicia el juego
            void Tablero::Imprimir(); // Función que pone el tablero en pantalla
            string Tablero::CompruebaStatus(); // Función que comprueba el estatus del juego, si está en juego o finalizado
            void Tablero::Jugada(); // Función que realiza la jugada
            Tablero(); // Constructor
 };

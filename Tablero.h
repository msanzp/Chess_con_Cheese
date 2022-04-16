#include <string>
using namespace std;

class Tablero
{
private:
        string TableroJuego[8][8] = {
            {"r", "n", "b", "q", "k", "b", "n", "r"}, //  linea 8 del tablero
            {"p", "p", "p", "p", "p", "p", "p", "p"},
            {"0", "0", "0", "0", "0", "0", "0", "0"}, 
            {"0", "0", "0", "0", "0", "0", "0", "0"}, 
            {"0", "0", "0", "0", "0", "0", "0", "0"}, 
            {"0", "0", "0", "0", "0", "0", "0", "0"}, 
            {"P", "P", "P", "P", "P", "P", "P", "P"}, 
            {"R", "N", "B", "Q", "K", "B", "N", "R"}  //  linea 1 del tablero
        };                                            // Tablero de juego inicial {Blancas en Mayusculas, Negras en minusculas}

        string QuienJuega = "w";                     // Quien juega la siguiente jugada {"w", "b"}
        string Jugador = "w";                        // Que lado juega el Jugador, por defecto juega las blancas {"w", "b"}
        string TipoJuego; // Tipo de juego, contra jugador o contra máquina {"Dos Jugadores", "Maquina"}
        string Roque  = "KQkq"; // Opcioned de roque disponibles {"KQkq", "KQk", "KQq", "KQ", "Kkq", "Kk", "Kq", "K", "Qkq", "Qk", "Qq", "Q", "kq", "k", "q", "-"}
        string EnPassant = ""; // Posible posicion de en passant (ejemplo: "e4")
        int HalfMoves = 0; // Contador de medios movimientos
        int FullMoves = 0; // Contador de movimientos completos
        string ObtieneJugada(); // Función que obtiene la jugada del jugador

public:
        void Tablero::GameStart(string EleccionJuego, string EleccionColor); // Función que inicia el juego
        void Tablero::Imprimir();                                        // Función que pone el tablero en pantalla
        string Tablero::CompruebaStatus();                               // Función que comprueba el estatus del juego, si está en juego o finalizado
        void Tablero::Jugada();                                          // Función que realiza la jugada
};

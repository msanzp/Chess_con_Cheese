#include <iostream>
#include <string>
using namespace std;

string convierte_a_FEN(string arg[8][8])
{
    cout << "AQUI EMPIEZA LA FUNCION"<< endl;

    string respuesta = "";
 
    int n = 0;
    int m = 0;
    int contador = 0;
    bool primera = true;

    cout << "AQUI he creado la string"<< endl;

    for (n = 0; n < 8; ++n)
    {
        if (n != 0 && m != 0)
            respuesta += "/";

        contador = 0;
        cout << "AQUI empieza una linea" << endl;

        for (m = 0; m < 8; ++m)
        {
            if (arg[n][m] == "0" && (m != 7)) // Espacio libre en el tablero, se añade 1 al contador
            {
                contador += 1;
            }
            else if (arg[n][m] == "0" && (m == 7)) //espacio libre pero es el espacio final, se añade 1 al contador y se implementa
            {
                contador += 1;
                respuesta += to_string(contador);
            } 
            else if (arg[n][m] != "0" && contador == 0) // Pieza en el tablero y contador 0, se añade al string
            {
                if (primera) 
                {
                    respuesta = arg[n][m]; // para que el string empieze por la primera pieza
                    primera = false;
                }
                else 
                {
                    respuesta += arg[n][m];
                }
                
            }
            else // Pieza en el tablero y contador no es 0, se añade contador + pieza al string
            {
                respuesta += to_string(contador);
                respuesta += arg[n][m];
                contador = 0;
            }
        }
        
    }
    return respuesta;
}

//Piece placement(from White's perspective).
//Each rank is described, starting with rank 8 and ending with rank 1;
//within each rank, the contents of each square are described from file "a" through file "h".
//(pawn = "P", knight = "N", bishop = "B", rook = "R", queen = "Q" and king = "K").
//White pieces are designated using upper-case letters ("PNBRQK")
//while black pieces use lowercase ("pnbrqk").
//Empty squares are noted using digits 1 through 8 (the number of empty squares)
//and "/" separates ranks.
//
//Active color. "w" means White moves next, "b" means Black moves next.
//
//Castling availability.If neither side can castle, this is "-".
//
//Otherwise, this has one or more letters : "K" (White can castle kingside), "Q" (White can castle queenside),
//"k" (Black can castle kingside), and /or "q" (Black can castle queenside).
//
//A move that temporarily prevents castling does not negate this notation.
//En passant target square in algebraic notation.
//If there's no en passant target square, this is "-". If a pawn has just made a two-square move, this is the position "behind" the pawn.
//This is recorded regardless of whether there is a pawn in position to make an en passant capture.[6]
//
//Halfmove clock : The number of halfmoves since the last capture or pawn advance, used for the fifty - move rule.[7]
//Fullmove number : The number of the full move.It starts at 1, and is incremented after Black's move.

int main()
{
    string tablero[8][8] = {
    {"r", "n", "b", "q", "k", "b", "n", "r"} ,   /*  initializers for row indexed by 0 -- linea 8 del tablero*/
    {"p", "p", "p", "p", "p", "p", "p", "p"} ,   /*  initializers for row indexed by 1  -- linea 7 del tablero*/
    {"0", "0", "0", "0", "0", "0", "0", "0"} ,   /*  initializers for row indexed by 2  -- linea 6 del tablero*/
    {"0", "0", "0", "0", "P", "0", "0", "0"} ,   /*  initializers for row indexed by 3  -- linea 5 del tablero*/
    {"0", "0", "0", "0", "0", "0", "0", "0"} ,   /*  initializers for row indexed by 4  -- linea 4 del tablero*/
    {"0", "0", "0", "0", "0", "0", "0", "0"} ,   /*  initializers for row indexed by 5  -- linea 3 del tablero*/
    {"P", "P", "P", "P", "0", "P", "P", "P"} ,   /*  initializers for row indexed by 6  -- linea 2 del tablero*/
    {"R", "N", "B", "Q", "K", "B", "N", "R"} ,   /*  initializers for row indexed by 7  -- linea 1 del tablero*/
    };
    cout << "AQUI PRIMERO" << endl;
    string payload = convierte_a_FEN(tablero);
    cout << "Aqui he terminado de converter" << endl;
    cout << payload << endl;
}
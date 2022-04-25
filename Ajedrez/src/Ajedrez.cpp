#include "Tablero.h"
#include "freeglut.h"
#include <iostream>

using namespace std;

Tablero tablero; // creamos la variable global que regulará todo el sistema de juego

//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); //esta funcion sera llamada para dibujar
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	

int main(int argc,char* argv[])
{
	// Definimos las variables que controlan el desarrollo de la partida
	int opcion;
	int turno = 0; //sirve para controlar quien juega, 0 juegan blancas y 1 juegan negras. Como siempre empiezan las blancas, inicialmente vale 0
	int final_de_partida = 0;

	// Lo primero que debemos hacer es determinar el estilo de juego que vamos a querer jugar
	do {
		cout << "Determina el modo de juego:" << endl;
		cout << "1: Jugador vs Jugador" << endl;
		cout << "2: Jugador vs Maquina" << endl;
		cin >> opcion;
	} while (opcion != 1 && opcion != 2);
	
	// Antes de comenzar con el desarrollo del juego, inicializamos el gestor de ventanas GLUT y creamos la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");
	//También, tenemos que habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	// una vez hemos determinado el estilo de juego y hemos configurado la pantalla, podemos comenzar a jugar
	
	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25,OnTimer,0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);

	tablero.comienzo_partida(); // sirve para determinar los valores iniciales de las piezas

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();	

	return 0;   
}

void OnDraw(void)
{
	//Borrado de la pantalla	
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	
	tablero.dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	tablero.tecla(key);

	glutPostRedisplay();
}

void OnTimer(int value)
{
//poner aqui el código de animacion
	tablero.mueve();
	tablero.ejecutar_movimiento();

	//no borrar estas lineas
	glutTimerFunc(25,OnTimer,0);
	glutPostRedisplay();
}
//Hola mundo
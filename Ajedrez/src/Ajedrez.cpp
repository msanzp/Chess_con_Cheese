#include "Tablero.h"
#include "freeglut.h"
#include <iostream>

using namespace std;

Tablero tablero; // creamos la variable global que regulará todo el sistema de juego

// los callback, funciones que seran llamadas automaticamente por la glut
// cuando sucedan eventos
// NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); // esta funcion sera llamada para dibujar
void OnTimer(int value); // esta funcion sera llamada cuando transcurra una temporizacion
void clickraton(int boton, int estado, int x, int y); // clic de la posicion de origen

int main(int argc, char* argv[])
{
	// Definimos las variables que controlan el desarrollo de la partida
	int opcion_juego; // sirve para determinar si queremos jugar JUGADOR VS JUGADOR o JUGADOR VS MAQUINA
	int opcion_color = 0; // si jugamos JUGADOR VS MAQUINA, sirve para determinar si queremos jugar con las negras o con las blancas 
	int opcion_graficos; // sirve para determinar si queremos jugar en 2D o en 3D

	// Lo primero que debemos hacer es determinar el estilo de juego que vamos a querer jugar
	do {
		cout << "Determina el modo de juego:" << endl;
		cout << "1: Jugador vs Jugador" << endl;
		cout << "2: Jugador vs Maquina" << endl;
		cin >> opcion_juego;
	} while (opcion_juego != 1 && opcion_juego != 2);
	
	do {
		cout << "Determina los gráficos:" << endl;
		cout << "1: Juego en 2D" << endl;
		cout << "2: Juego en 3D" << endl;
		cin >> opcion_graficos;
	} while (opcion_graficos != 1 && opcion_graficos != 2);

	// Antes de comenzar con el desarrollo del juego, inicializamos el gestor de ventanas GLUT y creamos la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 700);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	// También, tenemos que habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	// Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0); //le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	if(opcion_graficos == 1) // solamente vamos a jugar con raton para el modo de juego 2D debido a los altos tiempos de carga del modo 3D
		glutMouseFunc(clickraton);

	// Una vez hemos determinado el estilo de juego y hemos configurado la pantalla, podemos comenzar a jugar
	tablero.comienzo_partida(opcion_juego, opcion_color, opcion_graficos); // sirve para determinar los valores iniciales de las piezas

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
	if(tablero.getOpcionGraficos() == 1)
		tablero.dibuja2D();
	if (tablero.getOpcionGraficos() == 2)
		tablero.dibuja3D();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

void OnTimer(int value)
{
	//poner aqui el código de animacion

	tablero.ejecutar_movimiento();

	//no borrar estas lineas
	glutTimerFunc(25,OnTimer,0);
	glutPostRedisplay();
}

void clickraton(int boton, int estado, int x, int y) // sirve para controlar el juego por ratón
{
	if (boton == GLUT_LEFT_BUTTON && tablero.getCasilla_origen() == true)
	{
		tablero.setCoordenadaX_origen(tablero.coordenadaX(x));
		tablero.setCoordenadaY_origen(tablero.coordenadaY(y));
		glutPostRedisplay();
	}
	if (boton == GLUT_LEFT_BUTTON && tablero.getCasilla_destino() == true)
	{
		tablero.setCoordenadaX_destino(tablero.coordenadaX(x));
		tablero.setCoordenadaY_destino(tablero.coordenadaY(y));
		glutPostRedisplay();
	}
}
#include "Coordinador.h"
#include "freeglut.h"
#include <iostream>

using namespace std;

Coordinador ajedrez;

// los callback, funciones que seran llamadas automaticamente por la glut
// cuando sucedan eventos
// NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); // esta funcion sera llamada para dibujar
void OnTimer(int value); // esta funcion sera llamada cuando transcurra una temporizacion
void clickraton(int boton, int estado, int x, int y); // clic de la posicion de origen

int main(int argc, char* argv[])
{
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
	glutMouseFunc(clickraton);

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

	ajedrez.dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

void OnTimer(int value)
{
	//poner aqui el código de animacion

	ajedrez.partida();

	//no borrar estas lineas
	glutTimerFunc(25,OnTimer,0);
	glutPostRedisplay();
}

void clickraton(int boton, int estado, int x, int y) // sirve para controlar el juego por ratón
{
	if (ajedrez.getEstado() == 1 || ajedrez.getEstado() == 2) {
		if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
		{
			ajedrez.opcionSeleccionada(x, y);
			glutPostRedisplay();
		}
	}
	if (ajedrez.getEstado() == 3) {
		if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && ajedrez.getCasilla_origen() == true)
		{
			ajedrez.setCoordenadaX_origen(x);
			ajedrez.setCoordenadaY_origen(y);
			glutPostRedisplay();
		}
		if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && ajedrez.getCasilla_destino() == true)
		{
			ajedrez.setCoordenadaX_destino(x);
			ajedrez.setCoordenadaY_destino(y);
			glutPostRedisplay();
		}
	}
}
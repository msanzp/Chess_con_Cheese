#include "Pieza.h"

int Pieza::esNegra()
{
	return (color == 'b');
}

int Pieza::esBlanca()
{
	return (color == 'w');
}

int Pieza::esRey()
{
	if (tipo == 0)
		return 1;
	else 
		return 0;
}

int Pieza::esReina()
{
	if (tipo == 1)
		return 1;
	else
		return 0;
}

int Pieza::esAlfil()
{
	if (tipo == 2)
		return 1;
	else
		return 0;
}

int Pieza::esPeon()
{
	if (tipo == 3)
		return 1;
	else
		return 0;
}

int Pieza::esCaballo()
{
	if (tipo == 4)
		return 1;
	else
		return 0;
}

int Pieza::esTorre()
{
	if (tipo == 5)
		return 1;
	else
		return 0;
}

void Pieza::dibuja2D_borrada(GLfloat posicion_blacas, GLfloat posicion_negras)
{
	GLfloat pos_inicial_x;
	GLfloat posicion = posicion_blacas;		// 0: la primera, 1: la segunda, 2: la tercera...
	GLfloat pos_inicial_y = 0;	// altura de pintado inicial	
	GLfloat tam = 2;
		
	if (esBlanca())
	{
		pos_inicial_x = -4;
		posicion = posicion_blacas;
		if (esPeon())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonblanco_fondoblanco.png").id);
		if (esAlfil())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/alfilblanco_fondoblanco.png").id);
		if (esCaballo())	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/caballoblanco_fondoblanco.png").id);
		if (esTorre())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/torreblanca_fondoblanco.png").id);
		if (esReina())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reinablanca_fondoblanco.png").id);
		if (esRey())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reyblanco_fondoblanco.png").id);

	}
	else
	{
		pos_inicial_x = 34;
		posicion = posicion_negras;
		if (esPeon())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/peonnegro_fondoblanco.png").id);
		if (esAlfil())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/alfilnegro_fondoblanco.png").id);
		if (esCaballo())	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/caballonegro_fondoblanco.png").id);
		if (esTorre())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/torrenegra_fondoblanco.png").id);
		if (esReina())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reinanegra_fondoblanco.png").id);
		if (esRey())		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/2D/reynegro_fondoblanco.png").id);
	}
		
	glEnable(GL_TEXTURE_2D);
	posicion = (pos_inicial_y + posicion) * tam;

	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(pos_inicial_x		, posicion		, 0);
	glTexCoord2d(1, 1);		glVertex3f(pos_inicial_x + tam	, posicion		, 0);
	glTexCoord2d(1, 0);		glVertex3f(pos_inicial_x + tam	, posicion + tam, 0);
	glTexCoord2d(0, 0);		glVertex3f(pos_inicial_x		, posicion + tam, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Pieza::dibuja2D(const char foto1[], const char foto2[], const char foto3[], const char foto4[], const char foto5[], const char foto6[], int pieza_seleccionadaX, int pieza_seleccionadaY) {
	glEnable(GL_TEXTURE_2D);
	if (pieza_seleccionadaX == posX && pieza_seleccionadaY == posY)
	{
		if (color == 'w')
			glBindTexture(GL_TEXTURE_2D, getTexture(foto5).id);
		if (color == 'b')
			glBindTexture(GL_TEXTURE_2D, getTexture(foto6).id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1);		glVertex3f(posX * 4 - 4, posY * 4 - 4, 0);
		glTexCoord2d(1, 1);		glVertex3f(posX * 4, posY * 4 - 4, 0);
		glTexCoord2d(1, 0);		glVertex3f(posX * 4, posY * 4, 0);
		glTexCoord2d(0, 0);		glVertex3f(posX * 4 - 4, posY * 4, 0);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		return;
	}
	
	for (int j = 1; j < 9; j++) {
		for (int i = 1; i < 9; i++) {
			if (posX == j && posY == i) {
				if (j % 2 == 1) {//Bucle para las coordenadas y
					if (i % 2 == 1) {//Bucle para las coordenadas x
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, getTexture(foto2).id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, getTexture(foto4).id);
					}
					else {
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, getTexture(foto1).id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, getTexture(foto3).id);
					}
				}
				else {
					if (i % 2 == 0) {
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, getTexture(foto2).id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, getTexture(foto4).id);
					}
					else {
						if (color == 'w')
							glBindTexture(GL_TEXTURE_2D, getTexture(foto1).id);
						if (color == 'b')
							glBindTexture(GL_TEXTURE_2D, getTexture(foto3).id);
					}

				}
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);

				GLfloat _X1= posX * 4 - 4;
				GLfloat _X2= posX * 4;
				GLfloat _Y1= posY * 4 - 4;				
				GLfloat _Y2= posY * 4;				

				glTexCoord2d(0, 1);		glVertex3f(_X1	, _Y1	, 0);
				glTexCoord2d(1, 1);		glVertex3f(_X2	, _Y1	, 0);
				glTexCoord2d(1, 0);		glVertex3f(_X2	, _Y2	, 0);
				glTexCoord2d(0, 0);		glVertex3f(_X1	, _Y2	, 0);
				glEnd();
			}
		}
	}
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Pieza::dibuja3D(const char foto1[]) {

	// para dibujar las piezas en 3D tenemos que leer los archivos en formato txt
	// en primer lugar vamos a determinar cuantos vertices hay
	ifstream f1(foto1, ifstream::in);
	int numero_vertices = 0;
	string linea;
	while (getline(f1, linea)) { // copio una linea a linea del fichero en la "linea"
		if (linea[0] == 'v' && linea[1] == ' ')
			numero_vertices++;
	}
	f1.close();

	// tras ello, creamos un vector para almacenar todos los vertices
	ifstream f2(foto1, ifstream::in);
	int num_vertices = 0;
	float* coordenadaX = new float[numero_vertices];
	float* coordenadaY = new float[numero_vertices];
	float* coordenadaZ = new float[numero_vertices];
	while (getline(f2, linea)) { // copio una linea a linea del fichero en la "linea"
		int espacio1 = 0, espacio2 = 0, espacio3 = 0;
		if (linea[0] == 'v' && linea[1] == ' ') { // en el caso de ser un vértice
			// en primer lugar vamos a determinar donde se encuentran los espacios
			for (int i = 0; i < linea.size(); i++) {
				if (linea[i] == ' ' && espacio1 == 0)
					espacio1 = i;
				if (linea[i] == ' ' && espacio1 != i && espacio2 == 0)
					espacio2 = i;
				if (linea[i] == ' ' && espacio1 != i && espacio2 != i)
					espacio3 = i;
			}
			// una vez ya se donde se encuentran los espacios, copio los numeros en varias cadenas
			int aux1 = espacio2 - espacio1 - 1;
			int aux2 = espacio3 - espacio2 - 1;
			int aux3 = linea.size() - espacio3 - 1;
			char* cadena1 = new char[aux1];
			char* cadena2 = new char[aux2];
			char* cadena3 = new char[aux3];
			for (int j = espacio1 + 1; j < espacio2; j++)
				cadena1[j - espacio1 - 1] = linea[j];
			for (int j = espacio2 + 1; j < espacio3; j++)
				cadena2[j - espacio2 - 1] = linea[j];
			for (int j = espacio3 + 1; j < linea.size(); j++)
				cadena3[j - espacio3 - 1] = linea[j];
			// una vez ya hemos separado los numeros en cadenas, los convertimos a numeros
			coordenadaX[num_vertices] = stof(cadena1);
			coordenadaY[num_vertices] = stof(cadena2);
			coordenadaZ[num_vertices] = stof(cadena3);

			// dibujamos los vertices como esferitas para identificar mejor la forma
			glColor3ub(100, 100, 100);
			glTranslatef(coordenadaX[num_vertices] + posY * 6 - 3, coordenadaY[num_vertices], coordenadaZ[num_vertices] + posX * 6 - 3);
			glutSolidSphere(0.05f, 20, 20);
			glTranslatef(-(coordenadaX[num_vertices] + posY * 6 - 3), -(coordenadaY[num_vertices]), -(coordenadaZ[num_vertices] + posX * 6 - 3));
			num_vertices++;

			// borramos las cadenas
			delete[]cadena1;
			delete[]cadena2;
			delete[]cadena3;
		}
	}
	f2.close();

	// una vez tenemos todos los vertices en un vector, dibujamos las caras
	ifstream f3(foto1, ifstream::in);
	while (getline(f3, linea)) { // copio una linea a linea del fichero en la "linea"
		int espacio1 = 0, espacio2 = 0, espacio3 = 0;
		if (linea[0] == 'f' && linea[1] == ' ') { // en el caso de ser una cara
			// en primer lugar vamos a determinar donde se encuentran los espacios
			for (int i = 0; i < linea.size(); i++) {
				if (linea[i] == ' ' && espacio1 == 0)
					espacio1 = i;
				if (linea[i] == ' ' && espacio1 != i && espacio2 == 0)
					espacio2 = i;
				if (linea[i] == ' ' && espacio1 != i && espacio2 != i)
					espacio3 = i;
			}
			// ahora hay que identificar la primera barra dentro de cada hueco entre espacios
			int barra1 = 0, barra2 = 0, barra3 = 0;
			for (int i = espacio1 + 1; i < espacio2; i++) {
				if (linea[i] == '/' && barra1 == 0)
					barra1 = i;
			}
			for (int i = espacio2 + 1; i < espacio3; i++) {
				if (linea[i] == '/' && barra2 == 0)
					barra2 = i;
			}
			for (int i = espacio3 + 1; i < linea.size(); i++) {
				if (linea[i] == '/' && barra3 == 0)
					barra3 = i;
			}
			// una vez ya se donde se encuentran los espacios y barras, copio los numeros en varias cadenas
			int aux1 = barra1 - espacio1 - 1;
			int aux2 = barra2 - espacio2 - 1;
			int aux3 = barra3 - espacio3 - 1;
			char* cadena1 = new char[aux1];
			char* cadena2 = new char[aux2];
			char* cadena3 = new char[aux3];
			for (int j = espacio1 + 1; j < barra1; j++)
				cadena1[j - espacio1 - 1] = linea[j];
			for (int j = espacio2 + 1; j < barra2; j++)
				cadena2[j - espacio2 - 1] = linea[j];
			for (int j = espacio3 + 1; j < barra3; j++)
				cadena3[j - espacio3 - 1] = linea[j];

			// una vez ya hemos separado los numeros en cadenas, los convertimos a numeros
			// una vez ya hemos separado los numeros en cadenas, los convertimos a numeros
			int primer_vertice = stof(cadena1);
			int segundo_vertice = stof(cadena2);
			int tercer_vertice = stof(cadena3);

			// dibujamos la figura
			if(color == 'w')
				glColor3ub(255, 255, 255);
			if (color == 'b')
				glColor3ub(0, 0, 0);
			glBegin(GL_TRIANGLES);
			glVertex3f(coordenadaX[primer_vertice - 1] + posY * 6 - 3, coordenadaY[primer_vertice - 1], coordenadaZ[primer_vertice - 1] + posX * 6 - 3);
			glVertex3f(coordenadaX[segundo_vertice - 1] + posY * 6 - 3, coordenadaY[segundo_vertice - 1], coordenadaZ[segundo_vertice - 1] + posX * 6 - 3);
			glVertex3f(coordenadaX[tercer_vertice - 1] + posY * 6 - 3, coordenadaY[tercer_vertice - 1], coordenadaZ[tercer_vertice - 1] + posX * 6 - 3);
			glEnd();

			// borramos las cadenas
			delete[]cadena1;
			delete[]cadena2;
			delete[]cadena3;
		}
	}
	f3.close();

	delete[]coordenadaX;
	delete[]coordenadaY;
	delete[]coordenadaZ;
}

void Pieza::setX(int x) {
	posX = x;
}

void Pieza::setY(int y) {
	posY = y;
}

int Pieza::getX() {
	return posX;
}

int Pieza::getY() {
	return posY;
}

char Pieza::getColor() {
	return color;
}
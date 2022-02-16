#include "mina.h"

void cargar_mina(ifstream& file, tMina& mina) {//Carga la mina en funcion al tamaño
	char c, aux;
	file >> mina.nfilas;
	file >> mina.ncolum;

	for (int i = 0; i < mina.nfilas; i++) {
		file.get(aux);
		for (int j = 0; j < mina.ncolum; j++) {
			file.get(c);
			mina.plano[i][j] = toCasilla(c);
			if (mina.plano[i][j] == MINERO) {
				mina.posf = i;
				mina.posc = j;
			}
		}
	}
	file.close();
}

tCasilla toCasilla(char c) {// Devuelve la casilla correspondiente al carácter que recibe.
	tCasilla casilla;
	switch (c) {
	case 'J': {
		casilla = MINERO;
	}break;
	case 'M': {
		casilla = MURO;
	}break;
	case 'G': {
		casilla = GEMA;
	}break;
	case 'T': {
		casilla = TIERRA;
	}break;
	case 'S': {
		casilla = SALIDA;
	}break;
	case'P': {
		casilla = PIEDRA;
	}break;
	case ' ': {
		casilla = LIBRE;
	}break;
	}
	return casilla;
}

void dibujar1_1(const tMina& mina) { //Dibuja el formato 1x1.
	char muestra;
	for (int i = 0; i < mina.nfilas; i++) {
		cout << "|";

		for (int j = 0; j < mina.ncolum; j++) {
			muestra = tipoCasilla(mina.plano[i][j]);
			cout << muestra << " ";
			colorFondo(15);

		}
		cout << "|";
		colorFondo(15);
		cout << endl;
	}
	cout << endl;
}

void dibujar1_3(const tMina& mina) { //Dibuja el formato 3x1.
	tPlanoCaracteres caracteres;
	tPlanoColores colores;
	for (int i = 0; i < mina.nfilas; i++) {
		for (int j = 0; j < mina.ncolum; j++) {
			dibuja3x3(mina.plano[i][j], caracteres, colores, i, j);
		}
	}
	for (int i = 0; i < mina.nfilas * 3; i++) {
		for (int j = 0; j < mina.ncolum * 3; j++) {
			colorFondo(colores[i][j]);
			cout << caracteres[i][j] << " ";
			colorFondo(15);

		}
		cout << endl;
	}

}

void dibuja3x3(tCasilla casilla, tPlanoCaracteres& caracteres, tPlanoColores& colores, int i, int j) {//Crea los caracteres y colores del plano 3x1.
	string nombreDinamita = "TNTN NTNT", nombreGema = "MI TESORO", nombreSalida = "SALIDAESC", nombreMinero = "MI--NERO!", nombreTierra = "    T    ";
	int pos = 0;
	for (int x = i * 3; x < (i * 3 + 3); x++) {
		for (int y = j * 3; y < j * 3 + 3; y++) {

			switch (casilla) {
			case LIBRE: {
				colores[x][y] = 0;
				caracteres[x][y] = ' ';
			}break;
			case TIERRA: {
				colores[x][y] = 15;
				caracteres[x][y] = nombreTierra[pos];
			}break;
			case GEMA: {
				colores[x][y] = 2*16+15;
				caracteres[x][y] = nombreGema[pos];
			}break;
			case PIEDRA: {
				colores[x][y] = 7*16 + 15;
				caracteres[x][y] = '@';
			}break;
			case MURO: {
				colores[x][y] = 8*16;
				caracteres[x][y] = 'X';
			}break;
			case SALIDA: {
				colores[x][y] = 5*16 + 15;
				caracteres[x][y] = nombreSalida[pos];
			}break;
			case MINERO: {
				colores[x][y] = 4*16 + 15;
				caracteres[x][y] = nombreMinero[pos];
			}break;
			case DINAMITA: {
				colores[x][y] = 12*16 + 7;
				caracteres[x][y] = nombreDinamita[pos];
			}break;
			}
			pos++;

		}
	}
}

void colorFondo(int color) {// Color de las casillas.

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

void gravedad(tMina& mina) {//Hace caer la dinamita, las piedras y gemas del tablero
	bool modificado = false;
	for (int j = 0; j < mina.ncolum; j++) {
		for (int i = 0; i < mina.nfilas; i++) {
			if ((mina.plano[i][j] == PIEDRA) && (mina.plano[i + 1][j] == 0) && i < mina.nfilas - 1) {
				mina.plano[i][j] = LIBRE;
				mina.plano[i + 1][j] = PIEDRA;
				modificado = true;
			}
			else if (mina.plano[i][j] == DINAMITA) {
				if (mina.plano[i + 1][j] == 0 && i < mina.nfilas - 1) {
					mina.plano[i][j] = LIBRE;
					mina.plano[i + 1][j] = DINAMITA;
				}
				else {
					explosion(mina, i, j);
				}
				system("cls");
				if (mina.tamanio == 1) {
					dibujar1_1(mina);
					Sleep(150);
				}
				else {
					dibujar1_3(mina);
					Sleep(150);

				}
				modificado = true;
			
			}
			else if ((mina.plano[i][j] == GEMA) && (mina.plano[i + 1][j] == 0) && i < mina.nfilas - 1) {

				mina.plano[i][j] = LIBRE;
				mina.plano[i + 1][j] = GEMA;
				modificado = true;
			}
		}
	}
	if (modificado) {
		gravedad(mina);
	}
}

void explosion(tMina& mina, int x, int y) {//Elimina lo que hay a los lados de la dinamita exceptuando la salida
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (i >= 0 && j >= 0) {
				if (mina.plano[i][j] != SALIDA) {
					mina.plano[i][j] = LIBRE;
					if (j == mina.posc && i == mina.posf) {
						mina.posc = -1;
						mina.posf = -1;
					}
				}
			}
		}
	}
}

bool AjustarVentana(int Ancho, int Alto) {//Ajusta el tamaño de ventada donde se muestra el juego
	_COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tamaño
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tamaño de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	return TRUE;
}

char tipoCasilla(tCasilla casilla) {
	char salida;
	int color;
	switch (casilla) {
	case LIBRE: {
		salida = ' ';
		color = 0+15;
	}break;
	case TIERRA: {
		salida = 'T';
		color = 0 + 15;
	}break;
	case GEMA: {
		salida = 'G';
		color = 2*16 + 15;
	}break;
	case PIEDRA: {
		salida = '@';
		color = 7 * 16 + 15;
	}break;
	case MURO: {
		salida = 'X';
		color = 8 * 16;
	}break;
	case SALIDA: {
		salida = 'S';
		color = 5 * 16 + 15;
	}break;
	case MINERO: {
		salida = 'M';
		color = 4 * 16 + 15;
	}break;
	case DINAMITA: {
		salida = 'D';
		color = 12 * 16 + 7;
	}break;
	}
	colorFondo(color);
	return salida;
}


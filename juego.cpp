#include "juego.h"

bool cargar_Juego(tJuego& juego) { // Inicia lo necesario para jugar.
	bool salida = false;
	ifstream file;
	string snivel;
	snivel = to_string(juego.nivel);
	file.open(snivel + ".txt");// Se abre el nivel.
	if (file.is_open()) {
		cargar_mina(file, juego.mina);// Carga la mina dependiendo del tamaño.
		salida = true;
		juego.contGemas = 0;
		juego.numDinamitas = 0;
		juego.numMovimientos = 0;
		file.close();
	}
	else {
		cout << "ERROR. no se pudo abrir el nivel." << endl;
		Sleep(1250);
	}
	if (juego.mina.ncolum > 0 && juego.mina.nfilas > 0) {
		salida = true;
	}


	return salida;
}

bool hacerMovimiento(tJuego& juego, tTecla tecla) { //Dependiendo de la tecla que recibe, examina el movimiento que debe hacer
	bool salida = false;
	
	if (puedeMover(juego, tecla)) {//Entra si se puede hacer el movimiento
		juego.mina.plano[juego.mina.posf][juego.mina.posc] = LIBRE;
		salida = true;

		switch (tecla) {
		case ARRIBA: {
			juego.mina.posf--;
		}break;
		case IZQUIERDA: {
			juego.mina.posc--;

		}break;
		case ABAJO: {
			juego.mina.posf++;

		}break;
		case DERECHA: {
			juego.mina.posc++;
		}break;
		case TNT: {
			juego.numDinamitas++;
			juego.numMovimientos--;
			juego.contDtotal++;
		}break;
		}
		if (juego.mina.plano[juego.mina.posf][juego.mina.posc] == TNT) {
			juego.mina.posf = -2;
			juego.mina.posc = -2;
		}
		juego.mina.plano[juego.mina.posf][juego.mina.posc] = MINERO;
		gravedad(juego.mina);
	}
	 else if (tecla == ESC|| tecla == CAMBIO) {
		salida = true;
	}
	if (teclaMov(tecla)) {
		juego.numMovimientos++;
		juego.contMtotal++;
	}
	return salida;
}

void dibujar(const tJuego& juego) { //Llama a las funciones 1x1 o 1x3 e inicializa los contadores.
	AjustarVentana(juego.mina.ncolum * 3 * juego.mina.tamanio + 6, juego.mina.nfilas * 2 * juego.mina.tamanio + 4);//Ajusta el tamaño de la consola.

	if (juego.mina.tamanio == 1) {
		dibujar1_1(juego.mina);
	}
	else {
		dibujar1_3(juego.mina);
	}
	//Contadores del programa
	cout << "Numero de movimientos: " << juego.contMtotal << endl;
	cout << "Numero de gemas: " << juego.contGtotal << endl;
	cout << "Numero de dinamitas: " << juego.contDtotal << endl;
}

tTecla leerTecla() { //Lee la tecla que se pulsa y devuelve la tecla correspondiente.
	tTecla tecla;
	int dir;
	cin.sync();
	dir = _getch(); // dir: tipo int
	if (dir == 0xe0) {//Caracter especial
		dir = _getch();
		tipoTecla(tecla, dir);
	}
	else if (dir == 27) {//Tecla de escape
		tecla = ESC;
	}
	else if (dir == 68 || dir == 100) {//Tecla D para poner una dinamita
		tecla = TNT;
	}
	else if (dir == 67 || dir == 99) {//Tecla C para cambiar la configuracion del programa
		tecla = CAMBIO;
	}
	else if (dir == 13) {
		tecla = ENTER;
	}
	else {//Caso de introducir una opcion incorrecta
		tecla = NADA;
	}
	return tecla;
}

void tipoTecla(tTecla& tecla, int dir) { //Analiza que tecla es de las teclas especiales.
	switch (dir) {
	case 72: {
		tecla = ARRIBA;
	}break;
	case 80: {
		tecla = ABAJO;
	}break;
	case 77: {
		tecla = DERECHA;
	}break;
	case 75: {
		tecla = IZQUIERDA;
	}break;
	}
}

bool puedeMover(tJuego& juego, tTecla tecla) { //Examina para cada tecla pulsada si se es posible el movimiento.
	bool salida = false;
	int cerca = 0;
	switch (tecla) {
	case ARRIBA: {
		cerca = juego.mina.plano[juego.mina.posf - 1][juego.mina.posc];
		if (cerca != 3 && cerca != 4 && juego.mina.posf > 0) {
			salida = true;
		}
	}break;
	case IZQUIERDA: {
		cerca = juego.mina.plano[juego.mina.posf][juego.mina.posc - 1];
		if (cerca != 3 && cerca != 4 && juego.mina.posc > 0) {
			salida = true;
		}
		else if (cerca == 3 && juego.mina.plano[juego.mina.posf][juego.mina.posc - 2] == 0) {
			salida = true;
			juego.mina.plano[juego.mina.posf][juego.mina.posc - 2] = PIEDRA;
		}
	}break;
	case ABAJO: {
		cerca = juego.mina.plano[juego.mina.posf + 1][juego.mina.posc];
		if (cerca != 3 && cerca != 4 && juego.mina.posf < juego.mina.nfilas - 1) {
			salida = true;
		}
		else if (cerca == 3 && juego.mina.plano[juego.mina.posf + 2][juego.mina.posc] == 0) {
			salida = true;
			juego.mina.plano[juego.mina.posf + 2][juego.mina.posc] = PIEDRA;
		}
	}break;
	case DERECHA: {
		cerca = juego.mina.plano[juego.mina.posf][juego.mina.posc + 1];
		if (cerca != 3 && cerca != 4 && juego.mina.posc < juego.mina.ncolum - 1) {
			salida = true;
		}
		else if (cerca == 3 && juego.mina.plano[juego.mina.posf][juego.mina.posc + 2] == 0) {
			salida = true;
			juego.mina.plano[juego.mina.posf][juego.mina.posc + 2] = PIEDRA;
		}
	}break;
	case TNT: {
		if (juego.mina.plano[juego.mina.posf + 1][juego.mina.posc] == 0) {
			juego.mina.plano[juego.mina.posf + 1][juego.mina.posc] = DINAMITA;

			salida = true;
		}
	}break;

	}
	if (cerca == 2) {
		juego.contGemas++;
		juego.contGtotal++;
	}
	return salida;
}

tTecla cargartecla(ifstream& archivo, string nombre) { // Carga la tecla del fichero y te la devuelve en formato tecla.
	char aux;
	tTecla tecla;
	if (archivo.is_open()) {
		archivo >> aux;//Lee la tecla correspondiente
		switch (aux) {//Analiza el tipo de tecla
		case 'A': {
			tecla = ARRIBA;
		}break;
		case 'Z': {
			tecla = ABAJO;
		}break;
		case 'N': {
			tecla = IZQUIERDA;
		}break;
		case 'M': {
			tecla = DERECHA;
		}break;
		case 'D': {
			tecla = TNT;
		}break;
		default: {//En caso de fin del archivo o un caracter no contemplado muestra un error
			cout << "ERROR en la lectura del fichero." << endl;
			Sleep(1500);
			tecla = CAMBIO;
		}
		}
	}
	else {
		cout << "falla";
	}
	return tecla;
}

int menuMov(ifstream &archivo) { //Te da a elegir el método de entrada de datos.
	int entrada;
	bool carga = false;
	string nombreMov;
	string pregunta = "Elija el metodo de entrada de datos:";
	string op1 = "TECLADO";
	string op2 = "FICHERO";
	do {
		entrada = opcion(pregunta, op1, op2, "");
		
	} while (entrada < 1 || entrada > 2);
	while (entrada == 2 && !carga) {
		cout << "\nNombre del archivo de movimientos: "<<endl;
		cin >> nombreMov;
		archivo.open(nombreMov + ".txt");
		if (archivo.is_open()) {
			carga = true;
		}
		else {
			cout << "No se ha podido abrir con exito el archivo" << endl;
		}
	}
	return entrada;
}

bool menuNivel() {//Te pregunta si quieres jugar el siguiente nivel o salir del juego
	int op;
	string pregunta = "Fin del nivel.";
	string op1 = "Siguiente nivel.";
	string op2 = "Salir.";
	do {
		op = opcion(pregunta, op1, op2, "");
		if (op == 2) {
			op = 0;
		}
		
	} while (op < 0 || op>1);
	return op;
}

bool tipoFin(const tJuego& juego, const tTecla& tecla) { // Analiza por qué ha finalizado la partida
	bool fin = true;
	if (tecla == ESC || juego.mina.tamanio == 0) {
		cout << "Elegiste salir " << endl;
		fin = false;

	}
	else if (juego.mina.posc == -1 && juego.mina.posf == -1) {
		cout << "Explotaste\n" << "GAME OVER :(\n";
		fin = false;
	}
	
	Sleep(750);

	return fin;
}

bool jugar(tJuego& juego) { //Funcion principal que organiza la jugabilidad
	tTecla tecla;
	int op;
	string nombreMov;
	bool fin = false;
	ifstream archivo;
	system("cls");
	op = menuMov(archivo);
		
		if (cargar_Juego(juego)) {
			do {
				system("cls");
				dibujar(juego);
				if (op == 1) {
					tecla = leerTecla();
				}
				else if (op == 2) {
					tecla = cargartecla(archivo, nombreMov);
					Sleep(200);
				}
				if (!hacerMovimiento(juego, tecla)) {
					cout << "No puede" << endl;
					Sleep(500);
				}
				if (tecla == ESC || (juego.mina.posc < 0 && juego.mina.posf < 0)) {
					fin = true;
				}
				else if (tecla == CAMBIO) {
					if (juego.mina.ncolum * 3 * juego.mina.tamanio + 6 < 30) {
						AjustarVentana(30, juego.mina.nfilas * 2 * juego.mina.tamanio + 4);
					}
					juego.mina.tamanio = menu();
					if (juego.mina.tamanio == 0) {
						fin = true;
					}
					else {
						op = menuMov(archivo);
					}
				}
			} while (!fin);

			fin = tipoFin(juego, tecla);
			
		}
		else {
			cout << "no carga" << endl;
		}
	archivo.close();

	 
	return fin;
}

int opcion(string pregunta, string op1, string op2, string op3) {//Muestra las opciones a elegir del menu y perimte seleccionar con las flechas
	int salida = 1,color = 3*16, color1, color2 = 15, color3 = 15, dir, op = 2;
	tTecla tecla;
	color1 = color;
	AjustarVentana(82, 20);

	do {
		system("cls");
		colorFondo(15);
		cout << pregunta << endl<<endl;
		colorFondo(color1);
		cout << op1;
		colorFondo(0);
		cout << endl;
		colorFondo(color2);
		cout << op2;
		colorFondo(0);
		cout << endl;

		if (op3.length() > 1) {
			colorFondo(color3);
			cout << op3;
			colorFondo(0);
			cout << endl;
			op = 3;
		}
		tecla = leerTecla();
		if (tecla == ARRIBA && salida > 1) {
			salida--;
		}
		else if (tecla == ABAJO && salida < op) {
			salida++;

		}
		color1 = 15;
		color2 = 15;
		color3 = 15;
		if (salida == 1)
			color1 = color;
		else if (salida == 2)
			color2 = color;
		else if (salida == 3)
			color3 = color;

	} while (tecla != ENTER);
	colorFondo(15);
	return salida;
}

int menu() {//Muestra el menu de tamaño de la partida
	string op1 = "Jugar partida a escala 1:1";
	string op2 = "Jugar partida a escala 1:3";
	string op3 = "SALIR";
	int op;
	op = opcion("", op1, op2, op3);
	if (op ==3) {
		op = 0;
	}
	return op;
}

bool teclaMov(tTecla tecla) {
	bool salida = false;
	switch (tecla) {
	case ARRIBA: {}
	case IZQUIERDA: {}
	case ABAJO: {}
	case DERECHA: {
		salida = true;
	}break;
	}
	return salida;
}

void presentacion() {
	int op;
	cout << setw(52) << "M A S T E R   M I N E R" << endl << endl;
	cout << setw(59) << "BIENVENIDO AL JUEGO DEL MASTER MINER" << endl;
	cout << setw(60) << "-El juego trata de hacerse camino por-" << endl;
	cout << setw(62) << "-una mina solo con un pico y la dinamita-" << endl;
	cout << setw(62) << "-para poder conseguir la mayor  cantidad-" << endl;
	cout << setw(62) << "-de gemas posibles y encontrar la salida-" << endl;
	cout << endl << setw(72) << "-Para moverte podras hacerlo con las flechas de tu ordenador-" << endl;
	cout << setw(80) << "-Con la tecla D pones dinamita hacia abajo (cuidado que hace un buen agujero)-" << endl;
	cout << setw(68) << "-Pulsa la tecla C para cambiar las opciones del juego-" << endl;
	cout << setw(75) << "-Muevete por el menu con las flechas y pulsa ENTER para seleccionar-" << endl;
	cout << setw(64) << "-Con la tecla ESC podras abandonar la partida-" << endl << endl;
	cout << setw(56) << "Estas listo para esta aventura?\n";
	system("Pause");
	system("cls");
}



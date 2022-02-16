#include "memoria.h"

bool cargar_Marcador(tPuntuaciones& marcador) {
	bool salida = false;
	ifstream file;
	string nuevo;
	file.open("Puntuaciones.txt");
	if (file.is_open()) {
		do {
			file >> nuevo;
			if (nuevo != "000") {
				marcador.arrayPuntos[marcador.numJug].nombre = nuevo;
				file >> marcador.arrayPuntos[marcador.numJug].puntTotal;
				file >> marcador.arrayPuntos[marcador.numJug].minasRecor;
				for (int i = 0; i < marcador.arrayPuntos[marcador.numJug].minasRecor; i++) {
					file >> marcador.arrayPuntos[marcador.numJug].datos[i].IdMina;
					file >> marcador.arrayPuntos[marcador.numJug].datos[i].numM;
					file >> marcador.arrayPuntos[marcador.numJug].datos[i].numG;
					file >> marcador.arrayPuntos[marcador.numJug].datos[i].numD;
					file >> marcador.arrayPuntos[marcador.numJug].datos[i].puntos;
				}
				marcador.numJug++;
				if (marcador.numJug == marcador.cap) {
					aumentar_Capacidad(marcador);
				}
				
			}
		} while (nuevo != "000");
		salida = true;
		file.close();
	}
	else {
		cout << "ERROR. No se ha podido abrir el fichero." << endl;
	}
	return salida;
}

bool guardar_Marcador(tPuntuaciones& marcador) {
	bool salida = false;
	ofstream file;
	file.open("Puntuaciones.txt");
	if (file.is_open()) {
		for (int j = 0; j < marcador.numJug; j++) {
			file << marcador.arrayPuntos[j].nombre << endl;
			file << marcador.arrayPuntos[j].puntTotal << endl;
			file << marcador.arrayPuntos[j].minasRecor<<endl;
			for (int i = 0; i < marcador.arrayPuntos[j].minasRecor; i++) {
				file << marcador.arrayPuntos[j].datos[i].IdMina<<" ";
				file << marcador.arrayPuntos[j].datos[i].numM << " ";
				file << marcador.arrayPuntos[j].datos[i].numG << " ";
				file << marcador.arrayPuntos[j].datos[i].numD << " ";
				file << marcador.arrayPuntos[j].datos[i].puntos<<endl;
			}
		}
		salida = true;
		file << "000";
		file.close();
	}
	else {
		cout << "ERROR. No se ha podido abrir el fichero." << endl;
	}
	return salida;
}

void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont) {
	int tam;
	tam = 8 - marcador.arrayPuntos[cont].nombre.length();
	AjustarVentana(82, marcador.numJug * 7);
	if (cont < marcador.numJug) {
		if (marcador.arrayPuntos[cont].minasRecor > 0) {
			cout << endl << marcador.arrayPuntos[cont].nombre << setw(14 + tam) << "Movimientos" << setw(8) << "Gemas" << setw(12) << "Dinamitas" << setw(10) << "Puntos" << endl;
			for (int i = 0; i < marcador.arrayPuntos[cont].minasRecor; i++) {
				cout << "Mina:  " << marcador.arrayPuntos[cont].datos[i].IdMina;
				cout << setw(10) << marcador.arrayPuntos[cont].datos[i].numM;
				cout << setw(10) << marcador.arrayPuntos[cont].datos[i].numG;
				cout << setw(10) << marcador.arrayPuntos[cont].datos[i].numD;
				cout << setw(12) << marcador.arrayPuntos[cont].datos[i].puntos;
				cout << endl;
			}
		}
	}
	else {
		cout << "ERROR en la representacion de los datos del usuario" << endl;
	}

}

void mostrar_Alfabetico(const tPuntuaciones& marcador) {
	AjustarVentana(82, marcador.numJug * 7);

	cout << endl;
	for (int i = 0; i < marcador.numJug; i++) {
		if (marcador.arrayPuntos[i].minasRecor != 0) {
			cout << marcador.arrayPuntos[i].nombre << " " << marcador.arrayPuntos[i].puntTotal << endl;
		}
	}
	cout << endl;


}

void mostrar_Datos_Usuario(const tPuntuaciones& marcador) {
	int aux=0;
	AjustarVentana(82, marcador.numJug * 7);
	for (int i = 0; i < marcador.numJug; i++) {
		aux += marcador.arrayPuntos[i].minasRecor;
		mostrar_Minas_Usuario(marcador, i);

	}
}

void incicializar_Marcador(tPuntuaciones& marcador) {
	marcador.arrayPuntos = new tPuntosJug[marcador.cap];
	if (!cargar_Marcador(marcador)) {
		cout << "ERROR en la carga de los marcadores" << endl;
	}
	system("cls");

}

void aumentar_Capacidad(tPuntuaciones& marcador) {
	tPuntuaciones aux;
	aux.arrayPuntos = new tPuntosJug[marcador.numJug];
	aux.cap = marcador.cap;
	for (int i = 0; i < marcador.numJug; i++) {
		aux.arrayPuntos[i] = marcador.arrayPuntos[i];
	}
	marcador.cap = marcador.cap * 2;
	marcador.arrayPuntos = new tPuntosJug[marcador.cap];
	for (int i = 0; i < marcador.numJug; i++) {
		marcador.arrayPuntos[i] = aux.arrayPuntos[i];
	}
	aux.cap = 0;
	delete[] aux.arrayPuntos;
}

void destruir(tPuntuaciones& marcador) {
	delete[] marcador.arrayPuntos;
	marcador.cap = 0;
}

bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos){
	int ini = 0, fin, mitad;
	fin = marcador.numJug-1;
	bool salida = false;
	pos = -1;
	mitad = (ini + fin) / 2;

	do {
		if (nombre == marcador.arrayPuntos[mitad].nombre) {
			salida = true;
		}
		else {
			if (nombre > marcador.arrayPuntos[mitad].nombre) {
				ini = mitad + 1;
			}
			else if (nombre < marcador.arrayPuntos[mitad].nombre){
				
				fin = mitad - 1;
			}
			mitad = (ini + fin) / 2;

		}
	} while (!salida && ini<=fin);
	pos = ini;
	
	return salida;
}

void insertar(tPuntuaciones& marcador, const string& nombre, int pos) {

	if (marcador.numJug == marcador.cap) {
		aumentar_Capacidad(marcador);
	}

	for (int i = marcador.numJug - 1; i >= pos; i--) {
		marcador.arrayPuntos[i + 1] = marcador.arrayPuntos[i];
	}
	marcador.arrayPuntos[pos].nombre = nombre;
	for (int i = 0; i < 5;i++){
		marcador.arrayPuntos[pos].datos[i].IdMina = 0;
		marcador.arrayPuntos[pos].datos[i].numD = 0;
		marcador.arrayPuntos[pos].datos[i].numG = 0;
		marcador.arrayPuntos[pos].datos[i].numM = 0;
		marcador.arrayPuntos[pos].datos[i].puntos = 0;
	}
	marcador.arrayPuntos[pos].minasRecor = 0;
	marcador.arrayPuntos[pos].puntTotal = 0;
	marcador.numJug++;
	
}

int inicio(tPuntuaciones& marcador) {
	string nombre;
	int pos = 0;
	incicializar_Marcador(marcador);

	cout << "Antes de empezar dinos como te llamas: ";
	cin >> nombre;
	if (nombre[0] <= 123 && nombre[0]>= 97) {
		nombre[0] = nombre[0] - 32;
		
	}
	if (buscar(nombre, marcador, pos)) {
		cout << "ESTUPENDO hemos encontrado registros con ese nombre:";
		mostrar_Minas_Usuario(marcador, pos);
	}
	else {
		cout << "No tenemos datos con ese nombre..." << endl;
		cout << "Esta bien, vemos que eres nuevo." << endl;
		cout << "Mira las puntuaciones de los otros jugadores y humillalos." << endl;
		
		insertar(marcador, nombre, pos);
		mostrar_Alfabetico(marcador);
	}
	system("pause");
	system("cls");
	return pos;
}

bool partida(tPuntuaciones& marcador, tJuego &juego) {
	bool salida = false, recorrida = false;
	int min = 0, puntos = 0,pos = 0;
	if (jugar(juego) && juego.nivel !=0) {
		do {
			if (marcador.arrayPuntos[juego.jug].datos[min].IdMina == juego.nivel) {
				puntos = (juego.mina.ncolum * juego.mina.nfilas) + (A * juego.contGemas) - juego.numMovimientos - (B * juego.numMovimientos);
				if (puntos > marcador.arrayPuntos[juego.jug].datos[min].puntos) {
					marcador.arrayPuntos[juego.jug].datos[min].numD = juego.numDinamitas;
					marcador.arrayPuntos[juego.jug].datos[min].numG = juego.contGemas;
					marcador.arrayPuntos[juego.jug].datos[min].numM = juego.numMovimientos;
					marcador.arrayPuntos[juego.jug].datos[min].puntos = puntos;
				}
				else {
					cout << "Tienes una mejor puntuacion en otra partida" << endl;
					Sleep(1750);
				}
				recorrida = true;
			}
			else if (marcador.arrayPuntos[juego.jug].datos[min].IdMina > juego.nivel) {
				pos = min;
				min = ultimoN;
			}
			min++;

		} while (min < ultimoN && !recorrida);
		if (!recorrida) {
			if (min == ultimoN) {
				pos = -1;
				do {
					pos++;
				} while (marcador.arrayPuntos[juego.jug].datos[pos].IdMina != 0);
			}
			else {
				for (int i = marcador.arrayPuntos[juego.jug].minasRecor - 1; i >= pos; i--) {
					marcador.arrayPuntos[juego.jug].datos[i + 1] = marcador.arrayPuntos[juego.jug].datos[i];
				}
			}
			marcador.arrayPuntos[juego.jug].datos[pos].IdMina = juego.nivel;
			puntos = juego.mina.ncolum * juego.mina.nfilas + A * juego.contGemas - juego.numMovimientos - B * juego.numMovimientos;
			marcador.arrayPuntos[juego.jug].datos[pos].numD = juego.numDinamitas;
			marcador.arrayPuntos[juego.jug].datos[pos].numG = juego.contGemas;
			marcador.arrayPuntos[juego.jug].datos[pos].numM = juego.numMovimientos;
			marcador.arrayPuntos[juego.jug].datos[pos].puntos = puntos;
			marcador.arrayPuntos[juego.jug].minasRecor++;
		}
		marcador.arrayPuntos[juego.jug].puntTotal = 0;
		for (int i = 0; i < marcador.arrayPuntos[juego.jug].minasRecor; i++) {
			marcador.arrayPuntos[juego.jug].puntTotal += marcador.arrayPuntos[juego.jug].datos[i].puntos;
		}
	}
	else {
		cout << "Fin de la partida" << endl;
	}
	system("cls");
	if (menuFinMina(marcador,juego)) {
		salida = true;
	}
	else {
		if (guardar_Marcador(marcador)) {
			cout << "Puntuacion guardada con exito" << endl;
		}
	}
	return salida;
}

void pedirNivel(tPuntuaciones& marcador, tJuego& juego) {
	cout << "Que nivel quieres jugar:" << endl<<"Estos son las puntuaciones de todos los jugadores"<<endl;
	mostrar_Datos_Usuario(marcador);
	do {
		cout << "Introduce un nivel entre el 1-" << ultimoN << " o 0 para salir: ";
		cin >> juego.nivel;
		if (juego.nivel > ultimoN || juego.nivel < 0) {
			cout << "Introduzca una opcion valida"<< endl;
		}
	} while (juego.nivel > ultimoN || juego.nivel < 0);
}

bool menuFinMina(tPuntuaciones& marcador, tJuego& juego) {
	string pregunta, op1, op2, op3;
	int op, opP;
	bool salida = false;
	AjustarVentana(82, 20);
	system("cls");
	pregunta = "Elija una opcion para continuar: ";
	op1 = "Jugar de nuevo una mina.";
	op2 = "Ver las puntuaciones.";
	op3 = "SALIR";
	op = opcion(pregunta, op1, op2, op3);
	system("cls");
	if (op == 1) {
		pedirNivel(marcador, juego);
		if (juego.nivel != 0) {
			salida = true;
		}
	}
	else if (op == 2) {
		opP = opcion("Que puntuaciones quieres ver?", "Puntuaciones globales", "Puntuaciones de todos los jugadores", "Tus puntuaciones");
		system("cls");
		if (opP == 1) {
			mostrar_Alfabetico(marcador);
		}
		else if (opP == 2) {
			mostrar_Datos_Usuario(marcador);
		}
		else {
			mostrar_Minas_Usuario(marcador, juego.jug);
		}
		system("pause");
		if (menuFinMina(marcador, juego)) {
			salida = true;
		}
	}

	return salida;
}

void minero() {
	tJuego juego;
	tPuntuaciones marcador;
	bool fin = false;
	AjustarVentana(82, 20);
	presentacion();
	juego.mina.tamanio = menu();

	if (juego.mina.tamanio != 0) {
		juego.jug = inicio(marcador);
		pedirNivel(marcador, juego);
		if (juego.nivel != 0) {
			do {
				fin = partida(marcador, juego);
				system("cls");
			} while (fin);
		}
		AjustarVentana(82, 20);
		cout << "FIN DEL JUEGO." << endl;
	}
}

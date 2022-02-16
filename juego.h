#ifndef JUEGO_H
#define JUEGO_H
#include "conio.h"
#include "iomanip"
#include "mina.h"

const int ultimoN = 5, A=10,B=2;

typedef struct {
	tMina mina;
	int contGemas = 0, numMovimientos = 0, numDinamitas = 0, jug, nivel = 1, contGtotal = 0, contMtotal =0, contDtotal=0 ;
}tJuego;
typedef enum { ARRIBA, IZQUIERDA, ABAJO, DERECHA, ESC, TNT, NADA, CAMBIO, ENTER }tTecla;

bool cargar_Juego(tJuego& juego);
bool hacerMovimiento(tJuego& juego, tTecla tecla);
void dibujar(const tJuego& juego);
tTecla leerTecla();
void tipoTecla(tTecla& tecla, int dir);
bool puedeMover(tJuego& juego, tTecla tecla);
bool tipoFin(const tJuego& juego, const tTecla& tecla);
int menuMov(ifstream& archivo);
bool menuNivel();
tTecla cargartecla(ifstream& archivo, string nombre);
bool jugar(tJuego& juego);
int menu();
int opcion(string pregunta, string op1, string op2, string op3);
bool teclaMov(tTecla tecla);
void presentacion();

#endif

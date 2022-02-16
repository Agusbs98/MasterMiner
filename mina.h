#ifndef MINA_H
#define MINA_H

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

const int MAX = 50;//Constante con el tamaño maximo del array

typedef enum { LIBRE, TIERRA, GEMA, PIEDRA, MURO, SALIDA, MINERO, DINAMITA }tCasilla;//Declara el enum de las posibilidades del plano
typedef tCasilla tPlano[MAX][MAX];//Crea el plano de tamaño MAX con el tipo enum

typedef struct {//Declara tMina que guarda las cosas del plano
	tPlano plano;
	int nfilas, ncolum, posf, posc, tamanio;
}tMina;




typedef char tPlanoCaracteres[3 * MAX][3 * MAX];
typedef int tPlanoColores[3 * MAX][3 * MAX];

void cargar_mina(ifstream& file, tMina& mina);
void dibujar1_1(const tMina& mina);
void dibujar1_3(const tMina& mina);
void dibuja3x3(tCasilla casilla, tPlanoCaracteres& caracteres, tPlanoColores& colores, int i, int j); 
tCasilla toCasilla(char c);
void colorFondo(int color);
void gravedad(tMina& mina);
void explosion(tMina& mina, int x, int y);
bool AjustarVentana(int Ancho, int Alto);
char tipoCasilla(tCasilla casilla);

#endif

#ifndef MEMORIA_H
#define MEMORIA_H

#include "juego.h"

typedef struct {
	int IdMina=0, numM=0, numG=0, numD=0, puntos=0;
}tDatosMina;

typedef struct {
	string nombre;
	int puntTotal=0, minasRecor=0;
	tDatosMina datos[ultimoN];
}tPuntosJug;

typedef struct {
	int cap=2, numJug = 0;
	tPuntosJug* arrayPuntos;
}tPuntuaciones;

bool cargar_Marcador(tPuntuaciones& marcador);
bool guardar_Marcador(tPuntuaciones& marcador);
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont);
void mostrar_Alfabetico(const tPuntuaciones& marcador);
void mostrar_Datos_Usuario(const tPuntuaciones& marcador);

void incicializar_Marcador(tPuntuaciones& marcador);
void aumentar_Capacidad(tPuntuaciones& marcador);
void destruir(tPuntuaciones& marcador);
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);
void insertar(tPuntuaciones& marcador, const string& nombre, int pos);

int inicio(tPuntuaciones& marcador);
bool partida(tPuntuaciones& marcador, tJuego &juego);
void pedirNivel(tPuntuaciones& marcador, tJuego& juego);
bool menuFinMina(tPuntuaciones& marcador, tJuego& juego);
void minero();
#endif // !MEMORIA_H


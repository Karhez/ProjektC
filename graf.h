#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "STRUCTWie.h"

void inicjuj_grafy(grafWieCal *wierzcholki, grafKraCal *krawedzie);
void zwolnij_grafy(grafWieCal *wierzcholki, grafKraCal *krawedzie);
bool wczytaj_z_tekstu(const char *filename, grafWieCal *wierzcholki, grafKraCal *krawedzie);
int znajdz_lub_dodaj_wierzcholek(grafWieCal *wierzcholki, int id);
// id - numer wierzcholka z pliku
/*
Potrzebne w srodku funkcji char kname[64] - nazwa krawedzi;
int n1 n2 - numery nodeow
double w - waga
int idx1 idx2 - znajdz lub dodaj wierzcholek ideksy pomocnicze
do znajdowania nodeow gdy id =1 to trafia do nody]0] czyli idx = 0
*/
bool zapisz_tekstowo(grafWieCal *wierzcholki, const char *filename);
bool zapisz_binarnie(grafWieCal *wierzcholki, const char *filename);

#endif
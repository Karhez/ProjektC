#ifndef GRAF_H
#define GRAF_H

#include <stdbool.h>
#include "struct.h"

void inicjuj_wierzcholki(graf_Nod_All *wierzcholki); // przypisanie jakiś lowosych współrzędnych dla wierzchołków
void buduj_wierzcholki_z_krawedzi(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie); // buwowanie wierzchołków z krawędiz poprzez np hash mapę lub inaczej
void zwolnij_grafy(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie); // zwalnianie pamięci dla grafu

int zapisz_tekstowo(const graf_Nod_All *wierzcholki, const char *nazwa_pliku); // funkcja która zpaisuje tekstowo węzły do pliku
int zapisz_binarnie(const graf_Nod_All *wierzcholki, const char *nazwa_pliku); // funkcja która zpaisuje binarnie węzły do pliku

#endif
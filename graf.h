#ifndef GRAF_H
#define GRAF_H

#include <stdbool.h>
#include "struct.h"

void inicjuj_wierzcholki(graf_Nod_All *wierzcholki);
void buduj_wierzcholki_z_krawedzi(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie);
void zwolnij_grafy(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie);

bool zapisz_tekstowo(const graf_Nod_All *wierzcholki, const char *nazwa_pliku);
bool zapisz_binarnie(const graf_Nod_All *wierzcholki, const char *nazwa_pliku);

#endif
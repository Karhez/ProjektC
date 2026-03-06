#ifndef GRAF_H
#define GRAF_H

#include <stdbool.h>
#include "struct.h"

void inicjuj_wierzcholki(grafWieCal *wierzcholki);
void buduj_wierzcholki_z_krawedzi(grafWieCal *wierzcholki, grafKraCal *krawedzie);
void zwolnij_grafy(grafWieCal *wierzcholki, grafKraCal *krawedzie);

bool zapisz_tekstowo(const grafWieCal *wierzcholki, const char *nazwa_pliku);
bool zapisz_binarnie(const grafWieCal *wierzcholki, const char *nazwa_pliku);

#endif
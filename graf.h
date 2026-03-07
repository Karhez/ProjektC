#ifndef GRAF_H
#define GRAF_H

#include <stdbool.h>
#include "struct.h"

<<<<<<< HEAD
void inicjuj_wierzcholki(graf_Nod_All *wierzcholki);
void buduj_wierzcholki_z_krawedzi(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie);
void zwolnij_grafy(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie);

bool zapisz_tekstowo(const graf_Nod_All *wierzcholki, const char *nazwa_pliku);
bool zapisz_binarnie(const graf_Nod_All *wierzcholki, const char *nazwa_pliku);
=======
void inicjuj_wierzcholki(grafWieCal *wierzcholki);
void buduj_wierzcholki_z_krawedzi(grafWieCal *wierzcholki, grafKraCal *krawedzie);
void zwolnij_grafy(grafWieCal *wierzcholki, grafKraCal *krawedzie);

bool zapisz_tekstowo(const grafWieCal *wierzcholki, const char *nazwa_pliku);
bool zapisz_binarnie(const grafWieCal *wierzcholki, const char *nazwa_pliku);
>>>>>>> d625148cb64d0ed6a2840019adb92603e72f5e08

#endif
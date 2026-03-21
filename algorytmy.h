#ifndef ALGORYTMY_H
#define ALGORYTMY_H

#include "struct.h"

void uklad_fre (graf_Edg_All *krawedzie, graf_Nod_All *wierzcholki, int iteracje);
void uklad_tut(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie, int iteracje);
void uklad_spe(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie, int iteracje);

#endif
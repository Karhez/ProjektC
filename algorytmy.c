
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "struct.h"

int FuchterMann (graf_Edg_All *Edge, graf_Nod_All *Node){

    for(int i = 1; i<Node->liczbaWierzcholkow; i++){
        double Fx = 0;
        double Fy = 0;
        
        for(int j = 1; j<Node->liczbaWierzcholkow+1; j++){ // zaczynamy od 1 bo tak zaczynają się wierzchołki i to jest wektor odpychania tutaj tylko między cząstkami

                if(i !=j){ // jeśli nazwa node jest ta sama to pomijamy bo będzie 1/0
                    double odlX  = Node->nody[i].x - Node->nody[j].x; // odl - odległość x w osi ox y w osi oy
                    double odlY  = Node->nody[i].y - Node->nody[j].y;
                    double odlXY = sqrt(pow(odlX,2) + pow(odlY,2));
                    if(odlXY ==0 || odlXY < 0.001 ) break;                // jeśli pkt się naktryają to pomijamy dzielenie przez 0 to nezdefinowany
                    double fOdpychania = 1/pow(odlXY,2); // 1 można zmienić jak jest za mało bo może być trochę za ciasno
                    double trojkatPodobny = fOdpychania/odlXY; // Trójkąt siły i odległości to tr. podobne w związku z tym odległośći też są proporcjonalne
                    Fx += trojkatPodobny*odlX; // dodajmy wektor przemieszczenia na (-) jeśłi jest za j-tym węzłem na + jeśli przed
                    Fy += trojkatPodobny*odlX;

                }
            
        }

        // tutaj sprężyny tylko dobrze dodć jakiąś listę z czym jest połączony bo inaczej to jest kolejny for


        Node->nody[i].x += Fx; // zmiana pozycji wd wektora FX oraz Fy
        Node->nody[i].y += Fy;
    }


}

void uklad_tut(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie, int iteracje){
    if(krawedzie->liczbaKrawedzi == 0) return;
    int max_id = 0; // okreslam maksymlane id aby wiedziec jaki jest zakres tablicy nodów
    for(int i =0; i<krawedzie->liczbaKrawedzi; i++){
        if(krawedzie->Krawedzie[i].node1 > max_id) max_id = krawedzie->Krawedzie[i].node1;
        if(krawedzie->Krawedzie[i].node2 > max_id) max_id = krawedzie->Krawedzie[i].node2;
    }
    int rozmiar_tablicy = max_id + 1; // ideksxujemy od 0 wiec gdy max_id = 100 to jest 99 node
    // tablice pomocnicze - wspolrzedne
    double * nowe_x = calloc(rozmiar_tablicy, sizeof(double));
    double * nowe_y = calloc(rozmiar_tablicy, sizeof(double));
    int *stopien = calloc(rozmiar_tablicy, sizeof(int)); // informacja ile sasiadow ma dany wierzcholek

    int rama[3] = {-1, -1, -1}; // puste miejsca
    int liczba_el_rama = 0;
    for(int i =0; i < krawedzie->liczbaKrawedzi && liczba_el_rama < 3; i++){
        int u = krawedzie->Krawedzie[i].node1;
        int v = krawedzie->Krawedzie[i].node2;
        int u_znane = 0;
        int v_znane = 0;
        for(int j =0; j <liczba_el_rama; j++){
            if(rama[j] == u) u_znane = 1;
            if(rama[j] == v) v_znane = 1;
        }
        if(u_znane == 0 &&liczba_el_rama <3){
            rama[liczba_el_rama] = u;
            liczba_el_rama++;
        }
        if(v_znane ==0 && liczba_el_rama < 3){
            rama[liczba_el_rama] = v;
            liczba_el_rama++;
        }
    }
    // rozstawienie nodow na pomocniczy okreg o promieniu 100
    // cos(kat) = x/promien - wzor dla trojkata prostokatnego sin(kat) = y/promien
    double promien = 100;
    for(int i =0; i < liczba_el_rama; i++){
        double kat = i *(2*PI/liczba_el_rama); // katy kolejno 0, 120, 240
        int id = rama[i];
        wierzcholki->nody[id].x = promien * cos(kat);
        wierzcholki->nody[id].y = promien * sin(kat);
    }
    for(int iter = 0; iter < iteracje; iter++){
        for(int i =0; i <rozmiar_tablicy; i++){
            nowe_x[i] = 0.0;
            nowe_y[i] = 0.0;
            stopien[i] = 0;
        }
        for(int k =0; k < krawedzie->liczbaKrawedzi; k++){
            int u = krawedzie->Krawedzie[k].node1;
            int v = krawedzie->Krawedzie[k].node2;
            nowe_x[u] += wierzcholki->nody[v].x;
            nowe_y[u] += wierzcholki->nody[v].y;
            stopien[u]++;
            nowe_x[v] += wierzcholki->nody[u].x;
            nowe_y[v] += wierzcholki->nody[u].y;
            stopien[v]++;
        }
        for(int i =0; i < rozmiar_tablicy; i++){
            if(stopien[i] > 0){    //sprawdzam czy wierzcholek istnieje
                int jest_rama =0;
                for(int j =0; j <liczba_el_rama; j++){
                    if(rama[j] ==i) jest_rama = 1;
                }
                if(jest_rama ==0){
                wierzcholki->nody[i].x = nowe_x[i] / stopien[i];
                wierzcholki->nody[i].y = nowe_y[i] / stopien[i];
                }
        }
     }
    }
    free(nowe_x);
    free(nowe_y);
    free(stopien);
}



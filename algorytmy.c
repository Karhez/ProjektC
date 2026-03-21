
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "struct.h"
#define SZEROKOSC_POLA 40.0
#define WYSOKOSC_POLA 40.0

#define PI  3.14159265358

void uklad_fre (graf_Edg_All *krawedzie, graf_Nod_All *wierzcholki, int iteracje){
    if(krawedzie->liczbaKrawedzi ==0) return;
    
    for(int h = 0; h < iteracje; h++){

        for(int i = 1; i<wierzcholki->liczbaWierzcholkow+1; i++){
            double Fx = 0;
            double Fy = 0;
            
            for(int j = 1; j<wierzcholki->liczbaWierzcholkow+1; j++){ // zaczynamy od 1 bo tak zaczynają się wierzchołki i to jest wektor odpychania tutaj tylko między cząstkami

                    if(i !=j ||  wierzcholki->nody[j].node1 == 0){ // jeśli nazwa node jest ta sama to pomijamy bo będzie 1/0
                        double odlX  = wierzcholki->nody[i].x - wierzcholki->nody[j].x; // odl - odległość x w osi ox y w osi oy
                        double odlY  = wierzcholki->nody[i].y - wierzcholki->nody[j].y;
                        double odlXY = sqrt(pow(odlX,2) + pow(odlY,2));
                        if(odlXY < 0.001 ) continue;                // jeśli pkt się naktryają to pomijamy dzielenie przez 0 to nezdefinowany
                        double fOdpychania =  20/pow(odlXY,2); // 1 można zmienić jak jest za mało bo może być trochę za ciasno
                        double trojkatPodobny = fOdpychania/odlXY; // Trójkąt siły i odległości to tr. podobne w związku z tym odległośći też są proporcjonalne
                        Fx += trojkatPodobny*odlX; // dodajmy wektor przemieszczenia na (-) jeśłi jest za j-tym węzłem na + jeśli przed
                        Fy += trojkatPodobny*odlY;
                        
                        
                    }
                
            }

            for(int j=0; j<krawedzie->liczbaKrawedzi; j++){
                if(krawedzie->Krawedzie[j].node1 == wierzcholki->nody[i].node1 || krawedzie->Krawedzie[j].node2 == wierzcholki->nody[i].node1 ){

                        
                    if(krawedzie->Krawedzie[j].node1 ==  wierzcholki->nody[i].node1){ // szukamy połączeń między krawędziami  jeśli jest połączony z node 2  
                        
                        node szukanyNode = wierzcholki->nody[krawedzie->Krawedzie[j].node2];
                        double odlX  = wierzcholki->nody[i].x - szukanyNode.x; // odl - odległość x w osi ox y w osi oy
                        double odlY  = wierzcholki->nody[i].y -szukanyNode.y;
                        double odlXY = sqrt(pow(odlX,2) + pow(odlY,2));
                        if(odlXY < 0.001 ) continue; 

                        double fPrzyciagania = krawedzie->Krawedzie[j].waga * (-0.4*odlXY); // 1 można zmienić jak jest za mało bo może być trochę za ciasno
                        double trojkatPodobnyPrzy = fPrzyciagania/odlXY; // Trójkąt siły i odległości to tr. podobne w związku z tym odległośći też są proporcjonalne
                        Fx += trojkatPodobnyPrzy*odlX; // dodajmy wektor przemieszczenia na (-) jeśłi jest za j-tym węzłem na + jeśli przed
                        Fy += trojkatPodobnyPrzy*odlY;
                    }
                    if(krawedzie->Krawedzie[j].node2 ==  wierzcholki->nody[i].node1){ // szukamy połączeń między krawędziami  jeśli jest połączony z node 2  
                            
                        node szukanyNode = wierzcholki->nody[krawedzie->Krawedzie[j].node1];
                        double odlX  = wierzcholki->nody[i].x - szukanyNode.x; // odl - odległość x w osi ox y w osi oy
                        double odlY  = wierzcholki->nody[i].y -szukanyNode.y;
                        double odlXY = sqrt(pow(odlX,2) + pow(odlY,2));
                        if(odlXY < 0.001 ) continue; 

                        double fPrzyciagania = krawedzie->Krawedzie[j].waga * (-0.4*odlXY); // 1 można zmienić jak jest za mało bo może być trochę za ciasno
                        double trojkatPodobnyPrzy = fPrzyciagania/odlXY; // Trójkąt siły i odległości to tr. podobne w związku z tym odległośći też są proporcjonalne
                        Fx += trojkatPodobnyPrzy*odlX; // dodajmy wektor przemieszczenia na (-) jeśłi jest za j-tym węzłem na + jeśli przed
                        Fy += trojkatPodobnyPrzy*odlY;
                        
                    }
                }
            }


            wierzcholki->nody[i].x += Fx; // zmiana pozycji wd wektora FX oraz Fy
            wierzcholki->nody[i].y += Fy;
           
        }
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
    int liczba_el_rama = 0; // moc zbioru ramki
    for(int i =0; i < krawedzie->liczbaKrawedzi && liczba_el_rama < 3; i++){ // szumaky elementów do ramik
        int u = krawedzie->Krawedzie[i].node1; // pierwszy node
        int v = krawedzie->Krawedzie[i].node2; // drugi node
        int u_znane = 0;
        int v_znane = 0;
        for(int j =0; j <liczba_el_rama; j++){ // sprawdzamy czy element ramki jest dostępny
            if(rama[j] == u) u_znane = 1; 
            if(rama[j] == v) v_znane = 1;
        }
        if(u_znane == 0 &&liczba_el_rama <3){
            rama[liczba_el_rama] = u; // dodajemy element do ramki
            liczba_el_rama++;
        }
        if(v_znane ==0 && liczba_el_rama < 3){
            rama[liczba_el_rama] = v; // dodajemy element do ramik
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
            nowe_x[i] = 0.0; // wsp noda x
            nowe_y[i] = 0.0; // wsp noda y
            stopien[i] = 0; // ile ma nodów pośredniczących od ramki
        }
        for(int k =0; k < krawedzie->liczbaKrawedzi; k++){
            int u = krawedzie->Krawedzie[k].node1; // nazwa node 1
            int v = krawedzie->Krawedzie[k].node2; // nazwa node 2
            nowe_x[u] += wierzcholki->nody[v].x; // zmiana wsp x node 1
            nowe_y[u] += wierzcholki->nody[v].y; // zmiana wsp y node 1
            stopien[u]++;                        // zmiana stopnia wierzchołka 1
            nowe_x[v] += wierzcholki->nody[u].x;
            nowe_y[v] += wierzcholki->nody[u].y;
            stopien[v]++;
        }
        for(int i =0; i < rozmiar_tablicy; i++){
            if(stopien[i] > 0){    //sprawdzam czy wierzcholek istnieje
                int jest_rama =0;
                for(int j =0; j <liczba_el_rama; j++){
                    if(rama[j] ==i) jest_rama = 1; // jeśli jest ramka to ustawiamy na 1
                }
                if(jest_rama ==0){ // jeśłi to nie ramka to zmieniamy pozycje 
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

void uklad_spe(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie, int iteracje) {
    if (krawedzie->liczbaKrawedzi == 0) return;

    //  wyznaczenie max id wierzcholka 
    int max_id = 0;
    for (int i = 0; i < krawedzie->liczbaKrawedzi; i++) {
        if (krawedzie->Krawedzie[i].node1 > max_id) max_id = krawedzie->Krawedzie[i].node1;
        if (krawedzie->Krawedzie[i].node2 > max_id) max_id = krawedzie->Krawedzie[i].node2;
    }
    int n = max_id + 1; // rozmiar macierzy (indeksujemy od 0)

    //  alokacja macierzy Laplace'a L jako tablicy plaskiej n x n 
    double *L = calloc(n * n, sizeof(double));
    if (!L) return;

    //  budowa macierzy sasiedztwa A i diagonalnej D -> L = D - A 
    for (int k = 0; k < krawedzie->liczbaKrawedzi; k++) {
        int u = krawedzie->Krawedzie[k].node1;
        int v = krawedzie->Krawedzie[k].node2;
        double w = krawedzie->Krawedzie[k].waga;

        L[u * n + v] -= w; // -A
        L[v * n + u] -= w; // -A (graf nieskierowany)
        L[u * n + u] += w; // +D
        L[v * n + v] += w; // +D
    }

    //  szukamy lambda_max aby zbudowac macierz przesuniecia M = lambda_max*I - L 
    // przyblizamy lambda_max jako max element na przekatnej D (wystarczajace przyblizenie)
    double lambda_max = 0.0;
    for (int i = 0; i < n; i++) {
        if (L[i * n + i] > lambda_max) lambda_max = L[i * n + i];
    }
    lambda_max += 1.0; // male przesuniecie gwarantujace dodatniosc

    // M = lambda_max * I - L (in-place: nadpisujemy L -> M)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                L[i * n + j] = lambda_max - L[i * n + j];
            } else {
                L[i * n + j] = -L[i * n + j];
            }
        }
    }
    // od teraz L przechowuje macierz M

    //  pomocnicze tablice dla metody potegowania 
    double *vec  = malloc(n * sizeof(double));
    double *tmp  = malloc(n * sizeof(double));
    double *v0   = malloc(n * sizeof(double)); // wektor wlasny nr 0 (stalego - odpowiadajacy lambda=0 L)
    double *v1   = malloc(n * sizeof(double)); // wektor wlasny nr 1 (2. najmniejsza)
    double *v2   = malloc(n * sizeof(double)); // wektor wlasny nr 2 (3. najmniejsza)
    if (!vec || !tmp || !v0 || !v1 || !v2) {
        free(L); free(vec); free(tmp); free(v0); free(v1); free(v2);
        return;
    }

    //  funkcja lokalna: mnozenie M * vec -> tmp 
    // (realizowana inline ponizej w petlach)

    //  wektor wlasny v0 odpowiadajacy lambda_max M 
    // (to jest wektor stalej [1,1,...,1]/sqrt(n) odpowiadajacy lambda=0 L)
    for (int i = 0; i < n; i++) vec[i] = 1.0;
    for (int iter = 0; iter < iteracje; iter++) {
        // tmp = M * vec
        for (int i = 0; i < n; i++) {
            tmp[i] = 0.0;
            for (int j = 0; j < n; j++) tmp[i] += L[i * n + j] * vec[j];
        }
        // normalizacja
        double norm = 0.0;
        for (int i = 0; i < n; i++) norm += tmp[i] * tmp[i];
        norm = sqrt(norm);
        if (norm < 1e-12) break;
        for (int i = 0; i < n; i++) vec[i] = tmp[i] / norm;
    }
    for (int i = 0; i < n; i++) v0[i] = vec[i];

    //  wektor wlasny v1 (2. co do wielkosci M = 2. najmniejsza L) 
    // losowa inicjalizacja + deflacja wzgledem v0
    srand(42);
    for (int i = 0; i < n; i++) vec[i] = (double)(rand() % 100 + 1);
    for (int iter = 0; iter < iteracje; iter++) {
        // deflacja: odejmujemy skladowa wzgledem v0
        double dot = 0.0;
        for (int i = 0; i < n; i++) dot += vec[i] * v0[i];
        for (int i = 0; i < n; i++) vec[i] -= dot * v0[i];
        // tmp = M * vec
        for (int i = 0; i < n; i++) {
            tmp[i] = 0.0;
            for (int j = 0; j < n; j++) tmp[i] += L[i * n + j] * vec[j];
        }
        // normalizacja
        double norm = 0.0;
        for (int i = 0; i < n; i++) norm += tmp[i] * tmp[i];
        norm = sqrt(norm);
        if (norm < 1e-12) break;
        for (int i = 0; i < n; i++) vec[i] = tmp[i] / norm;
    }
    for (int i = 0; i < n; i++) v1[i] = vec[i];

    //  wektor wlasny v2 (3. co do wielkosci M = 3. najmniejsza L) 
    // deflacja wzgledem v0 i v1
    srand(123);
    for (int i = 0; i < n; i++) vec[i] = (double)(rand() % 100 + 1);
    for (int iter = 0; iter < iteracje; iter++) {
        // deflacja wzgledem v0
        double dot0 = 0.0;
        for (int i = 0; i < n; i++) dot0 += vec[i] * v0[i];
        for (int i = 0; i < n; i++) vec[i] -= dot0 * v0[i];
        // deflacja wzgledem v1
        double dot1 = 0.0;
        for (int i = 0; i < n; i++) dot1 += vec[i] * v1[i];
        for (int i = 0; i < n; i++) vec[i] -= dot1 * v1[i];
        // tmp = M * vec
        for (int i = 0; i < n; i++) {
            tmp[i] = 0.0;
            for (int j = 0; j < n; j++) tmp[i] += L[i * n + j] * vec[j];
        }
        // normalizacja
        double norm = 0.0;
        for (int i = 0; i < n; i++) norm += tmp[i] * tmp[i];
        norm = sqrt(norm);
        if (norm < 1e-12) break;
        for (int i = 0; i < n; i++) vec[i] = tmp[i] / norm;
    }
    for (int i = 0; i < n; i++) v2[i] = vec[i];

    //  przypisanie wspolrzednych xi = v1[i], yi = v2[i] 
    // v1 odpowiada 2. najmniejszej wartosci wlasnej L (wspolrzedna X)
    // v2 odpowiada 3. najmniejszej wartosci wlasnej L (wspolrzedna Y)
    for (int i = 0; i < krawedzie->liczbaKrawedzi; i++) {
        int u = krawedzie->Krawedzie[i].node1;
        int v_id = krawedzie->Krawedzie[i].node2;
        wierzcholki->nody[u].x = v1[u];
        wierzcholki->nody[u].y = v2[u];
        wierzcholki->nody[v_id].x = v1[v_id];
        wierzcholki->nody[v_id].y = v2[v_id];
    }

    //   5: normalizacja do obszaru SZEROKOSC_POLA x WYSOKOSC_POLA 
    // (interpolacja liniowa jak opisano w PDF)
    double x_min = v1[0], x_max = v1[0];
    double y_min = v2[0], y_max = v2[0];
    for (int i = 1; i < n; i++) {
        if (v1[i] < x_min) x_min = v1[i];
        if (v1[i] > x_max) x_max = v1[i];
        if (v2[i] < y_min) y_min = v2[i];
        if (v2[i] > y_max) y_max = v2[i];
    }
    double x_range = x_max - x_min;
    double y_range = y_max - y_min;
    if (x_range < 1e-12) x_range = 1.0;
    if (y_range < 1e-12) y_range = 1.0;

    for (int i = 0; i < krawedzie->liczbaKrawedzi; i++) {
        int u   = krawedzie->Krawedzie[i].node1;
        int v_id = krawedzie->Krawedzie[i].node2;
        // interpolacja liniowa: mapowanie na [-W/2, W/2] x [-H/2, H/2]
        wierzcholki->nody[u].x   = ((v1[u]    - x_min) / x_range - 0.5) * SZEROKOSC_POLA;
        wierzcholki->nody[u].y   = ((v2[u]    - y_min) / y_range - 0.5) * WYSOKOSC_POLA;
        wierzcholki->nody[v_id].x = ((v1[v_id] - x_min) / x_range - 0.5) * SZEROKOSC_POLA;
        wierzcholki->nody[v_id].y = ((v2[v_id] - y_min) / y_range - 0.5) * WYSOKOSC_POLA;
    }

    free(L);
    free(vec);
    free(tmp);
    free(v0);
    free(v1);
    free(v2);
}


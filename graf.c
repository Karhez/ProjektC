
#include "struct.h"
#include "graf.h"

#include<stdio.h>
#include<stdlib.h>


void buduj_wierzcholki_z_krawedzi(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie){
    int licza_Dodanych = 0;

    int najNrWie = krawedzie->Krawedzie[0].node1;
    for(int i =0; i< krawedzie->liczbaKrawedzi; i++){ // zabezpieczenie przed możliwością gdy wierzchołki są nie liniowe
        if(krawedzie->Krawedzie[i].node1> najNrWie) najNrWie = krawedzie->Krawedzie[i].node1;
        if(krawedzie->Krawedzie[i].node2> najNrWie) najNrWie = krawedzie->Krawedzie[i].node2;

    }

    int *hash_Map_Edg = calloc(krawedzie->liczbaKrawedzi*najNrWie,sizeof(short));// to jest maksymalna liczba wierzchołków każda krawędź ma dwa końce
    // short bo sprawdzamy czy dodana a więc int jest nie potrzebny

    wierzcholki->nody = malloc(sizeof(node)*wierzcholki->liczbaWierzcholkow+1); // gwarancja że nie przepełnimy buforu bo liczba węzłów to maks 2 razy liczba krawędzi 

    for(int i = 0; i<krawedzie->liczbaKrawedzi; i++){
        int nazwa_Node1 = krawedzie->Krawedzie->node1;
        int nazwa_Node2 = krawedzie->Krawedzie->node2;
        
        if(hash_Map_Edg[nazwa_Node1]==0 || hash_Map_Edg[nazwa_Node2]==0){

            if(hash_Map_Edg[nazwa_Node1] == 0 ){ // dodajemy node 1
                wierzcholki->nody[nazwa_Node1].node1 = nazwa_Node1;
                hash_Map_Edg[nazwa_Node1] = 1;
                licza_Dodanych ++;
            }

            if(hash_Map_Edg[nazwa_Node2] == 0){ // dodajemy node 2
                wierzcholki->nody[nazwa_Node2].node1 = nazwa_Node2;
                hash_Map_Edg[nazwa_Node2] = 1;
                licza_Dodanych ++;
            }
        }
    }

    wierzcholki->liczbaWierzcholkow = licza_Dodanych; // liczba wierzchołków to i tak zawsze liczba krawędzi * 2
    free(hash_Map_Edg); // zwalniam zbędną liste czy dodałem
}

void inicjuj_wierzcholki(graf_Nod_All *wierzcholki){
    srand(time(NULL));
    
    for(int i = 0; i< wierzcholki->liczbaWierzcholkow;i++){

        wierzcholki->nody[i].x = (rand() % 201) - 100; // losowanie wsp x od -100 do 100
        wierzcholki->nody[i].y = (rand() % 201) - 100; // losowanie wsp y od -100 do 100

    }

} 

void zwolnij_grafy(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie){
    free(wierzcholki->nody);// tutaj będzie trzeba zmienić bo jest malloc na listę a nie element no chyba że tak możę być nie ma to większego znaczenia 
    free(krawedzie->Krawedzie); // 
    free(krawedzie);
    free(wierzcholki);
    printf("------Pomyślnie zwolniono pamięć------");

}

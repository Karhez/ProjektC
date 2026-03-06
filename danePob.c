
#include "danePob.h"
#include "struct.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int PrintElements(grafKraCal *structZKra){
    for(int i =0; i < structZKra->liczbaKrawedzi; i++){
        printf("krawędz nazywa się: %s\n",structZKra->Krawedzie[i].nazwa);
    }
    return 1;
}

int pobieranieDanych(char * nazwaPliku, grafKraCal *krawedzieGrafu ){

    FILE *fptr = fopen(nazwaPliku,"r");
    if(!fptr) return 0;

    int nrOfEle = 10;
    
    int i=0;

    int node1,node2; // dodanie zmiennych pomocniczych 
    double waga;
    char nazwa[50];

    while (fscanf(fptr,"%s %d %d %lf", nazwa, &node1, &node2, &waga) == 4){
        
        
        if(i>=nrOfEle) {

            nrOfEle = nrOfEle*2;
            Krawedz *tmp = realloc(krawedzieGrafu->Krawedzie,sizeof(Krawedz)*nrOfEle);// !!! dodajemy tego in by dodać potem liczbe krawędzi co nam ułatwi działanie
            
            if(!tmp){

                printf("brak pamięci !!! błąd w pliku danePob linia 22");
                free (krawedzieGrafu);
                fclose(fptr);
                return 0;
            }
            krawedzieGrafu->Krawedzie = tmp;
            

        }

        strcpy(krawedzieGrafu->Krawedzie[i].nazwa, nazwa);
        krawedzieGrafu->Krawedzie[i].node1 =  node1;
        krawedzieGrafu->Krawedzie[i].node2 =  node2;
        krawedzieGrafu->Krawedzie[i].waga = waga;
        
        i++;
    }

    krawedzieGrafu->liczbaKrawedzi = i;

    fclose(fptr);
    return 1;
}    




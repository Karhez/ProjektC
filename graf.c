
#include "struct.h"
#include "graf.h"

#include<stdio.h>
#include<stdlib.h>
#include <time.h>


/* void buduj_wierzcholki_z_krawedzi(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie){
    int liczba_Dodanych = 0;

    int najNrWie = krawedzie->Krawedzie[0].node1;
    for(int i =0; i< krawedzie->liczbaKrawedzi; i++){ // zabezpieczenie przed możliwością gdy wierzchołki są nie liniowe
        
        if(krawedzie->Krawedzie[i].node1> najNrWie) najNrWie = krawedzie->Krawedzie[i].node1;
        if(krawedzie->Krawedzie[i].node2> najNrWie) najNrWie = krawedzie->Krawedzie[i].node2;

    }
    printf("%d\n", najNrWie);
    int *hash_Map_Edg = calloc(najNrWie+1,sizeof(int));// to jest maksymalna liczba wierzchołków każda krawędź ma dwa końce
    // short bo sprawdzamy czy dodana a więc int jest nie potrzebny

    wierzcholki->nody = calloc(najNrWie+1,sizeof(node)); // gwarancja że nie przepełnimy buforu bo liczba węzłów to maks 2 razy liczba krawędzi 
    
    for(int j=0; j<najNrWie+1;j++){
            wierzcholki->nody[j].listaPol = calloc(najNrWie+1 ,sizeof(double));
     }

    for(int i = 0; i<krawedzie->liczbaKrawedzi; i++){
        int nazwa_Node1 = krawedzie->Krawedzie[i].node1;
        int nazwa_Node2 = krawedzie->Krawedzie[i].node2;
        
        

        if(hash_Map_Edg[nazwa_Node1] == 0 ){ // dodajemy node 1
            wierzcholki->nody[nazwa_Node1].node1 = nazwa_Node1;
            hash_Map_Edg[nazwa_Node1] = 1;
            liczba_Dodanych ++;

            
        }

        if(hash_Map_Edg[nazwa_Node2] == 0){ // dodajemy node 2
            wierzcholki->nody[nazwa_Node2].node1 = nazwa_Node2;
            hash_Map_Edg[nazwa_Node2] = 1;
            liczba_Dodanych ++;

            
        }
        wierzcholki->nody[nazwa_Node1].listaPol[nazwa_Node2] = krawedzie->Krawedzie[i].waga; // zapisujemy z czym ma on połączenie
        wierzcholki->nody[nazwa_Node2].listaPol[nazwa_Node1] = krawedzie->Krawedzie[i].waga;
        
    }
    printf("liczba dodanych: %d",liczba_Dodanych);
    wierzcholki->liczbaWierzcholkow = najNrWie; // liczba wierzchołków to i tak zawsze liczba krawędzi * 2
    free(hash_Map_Edg); // zwalniam zbędną liste czy dodałem
} */
 void buduj_wierzcholki_z_krawedzi(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie){
    int najNrWie =0;
    for(int i=0; i <krawedzie->liczbaKrawedzi;i++){
        if(krawedzie->Krawedzie[i].node1 > najNrWie) najNrWie = krawedzie->Krawedzie[i].node1;
        if(krawedzie->Krawedzie[i].node2 > najNrWie) najNrWie = krawedzie->Krawedzie[i].node2;
    }
    wierzcholki->nody = calloc(najNrWie+1, sizeof(node));
    if(wierzcholki->nody ==NULL){
        fprintf(stderr, "Blad alokacji pamiec\n");
        exit(EXIT_FAILURE);
    }
    int liczba_Dodanych =0;
    for(int i=0; i <krawedzie->liczbaKrawedzi; i++){
        int n1 = krawedzie->Krawedzie[i].node1;
        int n2 = krawedzie->Krawedzie[i].node2;
        //sprawdzam czy dodany dla n1
        if(wierzcholki->nody[n1].node1 == 0){
            wierzcholki->nody[n1].node1 = n1;
            liczba_Dodanych++;
        }
        // sprawdzam czy dodany dla n2
        if(wierzcholki->nody[n2].node1 ==0){
            wierzcholki->nody[n2].node1 = n2;
            liczba_Dodanych++;
        }
    }
    wierzcholki->liczbaWierzcholkow = najNrWie;
    printf("UWAGA dodcano %d unikalnych wierzcholkow\n", liczba_Dodanych);
 }

void inicjuj_wierzcholki(graf_Nod_All *wierzcholki){
    srand(time(NULL));
    
    for(int i = 0; i< wierzcholki->liczbaWierzcholkow;i++){
        if(wierzcholki->nody[i].node1 != 0){
            wierzcholki->nody[i].x = (rand() % 201) - 100; // losowanie wsp x od -100 do 100
            wierzcholki->nody[i].y = (rand() % 201) - 100; // losowanie wsp y od -100 do 100
        }else{
            wierzcholki->nody[i].x = 0;
            wierzcholki->nody[i].y = 0;
        }
    }

} 

int zapisz_tekstowo(const graf_Nod_All *wierzcholki, const char *nazwa_pliku){
    FILE *file = fopen( nazwa_pliku, "w");
    if(!file) return 0;
    printf("otwarto plik\n");
    for(int i = 1; i< wierzcholki->liczbaWierzcholkow+1; i++ ){
        node *Wie = &(wierzcholki->nody[i]);

        if(Wie->node1 != 0 || Wie->node1 < 0){
            printf("%d %lf %lf\n",Wie->node1, Wie->x, Wie->y);
            fprintf(file,"%d %lf %lf\n",Wie->node1, Wie->x, Wie->y );
        }
    }
    fclose(file);
    return 1;
}
int zapisz_binarnie(const graf_Nod_All *wierzcholki, const char *nazwa_pliku){
    FILE *file = fopen( nazwa_pliku, "wb");
    if(!file) return 0;

    for(int i = 1; i< wierzcholki->liczbaWierzcholkow; i++ ){
        node *Wie = &(wierzcholki->nody[i]);
        if(Wie->node1 != 0 || Wie->node1 < 0){
            fwrite(&(Wie->node1),sizeof(int),1,file);
            fwrite(&(Wie->x),sizeof(double),1,file);
            fwrite(&(Wie->y),sizeof(double),1,file);
        }
    }
    fclose(file);
    return 1;

}
// poprawa zwolnij grafy
void zwolnij_grafy(graf_Nod_All *wierzcholki, graf_Edg_All *krawedzie){
   if(wierzcholki->nody !=NULL){
    free(wierzcholki->nody);
   }
   if(krawedzie->Krawedzie !=NULL){
    free(krawedzie->Krawedzie);
   }
    printf("------Pomyślnie zwolniono pamięć------");

}

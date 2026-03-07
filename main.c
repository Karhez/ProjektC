#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
<<<<<<< HEAD

#include "struct.h"


=======
#include "struct.h"
#include "danePob.h"
#include "graf.h"
#include "algorytmy.h"
>>>>>>> d625148cb64d0ed6a2840019adb92603e72f5e08
#define DOMYSLNE_ITERACJE 200
#define SZEROKOSC_POLA 40.0
#define WYSOKOSC_POLA 40.0
//./graph -i  <plik_wejsciowy> -o <plik_wyjsciowy> -a <algorytm> -b (binarnie)

void pomoc(){
    printf("Użycie programu ./graph -i  <plik_wejsciowy> -o <plik_wyjsciowy> -a <algorytm> -b \n");
    printf("Dostepne opcje: \n");
    printf(" -i  <plik wejsciowy> \n");
    printf(" -o <plik wyjsciowy> \n");
    // skroty literowe fre - fruchterman_reingold tut - tutte, Spe - Spectral layout 
    printf(" -a <algorytm>: 'fre' lub 'tut' lub 'Spe'\n");
    printf(" -b (zapis binarny do pliku, domyslnie tekstowy)\n");
}

int main(int argc, char *argv[]){
    pomoc();
    char *file_in = NULL;
    char *file_out = NULL;
    char *algo = NULL;
    bool binarny = false;

    if(argc < 2 ){
        printf("Podano zbyt mala liczbe argumentow wyswietlam pomoc: \n");
        pomoc();
        return EXIT_FAILURE;
    }
    for(int i =1; i< argc; i++){
        if(strcmp(argv[i], "-i") ==0 && i+1 < argc){
            file_in = argv[++i];
        }else if(strcmp(argv[i], "-o") ==0 && i+1 < argc){
            file_out = argv[++i];
        }else if(strcmp(argv[i], "-a" ) ==0 && i+1 < argc){
            algo = argv[i++];
        }else if(strcmp(argv[i], "-b") ==0){
            binarny = true;
        }
    }
    if(!file_in || !file_out || !algo){
        pomoc();
        return EXIT_FAILURE;
    }
    srand(time(NULL));

<<<<<<< HEAD
    graf_Nod_All wierzcholki;
    graf_Edg_All krawedzie;
=======
    grafWieCal wierzcholki;
    grafKraCal krawedzie;

    krawedzie.Krawedzie =NULL;
    krawedzie.liczbaKrawedzi = 0;
>>>>>>> d625148cb64d0ed6a2840019adb92603e72f5e08
    inicjuj_grafy(&wierzcholki, &krawedzie);

    if(!pobieranieDanych(file_in,&krawedzie)){
        fprintf(stderr, "Blad: Nie mozna wczytac pliku %s\n", file_in);
        return EXIT_FAILURE;
    }
    buduj_wierzcholki_z_krawedzi(&wierzcholki, &krawedzie);
    // Uruchamianie algorytmu
    if(strcmp(algo, "fre")  == 0){
        uklad_fre(&wierzcholki, &krawedzie, DOMYSLNE_ITERACJE, SZEROKOSC_POLA, WYSOKOSC_POLA);
    }else if(strcmp(algo, "tut")==0){
        uklad_tut(&wierzcholki, &krawedzie, DOMYSLNE_ITERACJE);
    }else if(strcmp(algo, "spe") ==0){
        uklad_spe(&wierzcholki, &krawedzie, DOMYSLNE_ITERACJE);
    }else{
        fprintf(stderr, "Nie rozpoznano algorytmu %s\n", algo);
        zwolnij_grafy(&wierzcholki, &krawedzie);
        return EXIT_FAILURE;
    }
    bool sukces;
    //zapis_tekstowo oraz zapisz bomarmoe to funkcje typu bool
    // jesli zapisza to true jesli nie to false
    if(binarny){
        sukces = zapisz_binarnie(&wierzcholki, file_out);
    }else{
        sukces = zapisz_tekstowo(&wierzcholki, file_out);
    }
    if(sukces){
        printf("Poprawnie wyznaczono wspolrzedne i zapisano do pliku %s\n", file_out);
    }
    zwolnij_grafy(&wierzcholki, &krawedzie);
    return 0;
}
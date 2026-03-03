

#include <stdio.h>
#include<stdlib.h>

#include "danePob.h"
#include "struct.h"

int main(int argc,char *argv[]){

    grafKraCal *kra = malloc(sizeof(grafKraCal));
    kra->liczbaKrawedzi = 0;
    kra->Krawedzie = malloc(sizeof(Krawedz)*10); 


    
    if(pobieranieDanych(argv[1], kra)==1)printf("udało się");
    else printf("pobieranie nie udało się");

    if(PrintElements(kra)==1) printf("udało się");
    else printf("pobieranie nie udało się");
    return 1;
}
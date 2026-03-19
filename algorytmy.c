
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



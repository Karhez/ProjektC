

#ifndef STRUCTWie_H
#define STRUCTWie_H

typedef struct {
    int node1; // number wierzchołka
    double x; // współrzędna x
    double y; // współrzędna y
   
} node;

typedef struct {
    
    node * nody; // lista z wierzchołkami
    int liczbaWierzcholkow; // liczba wierzchołków

}graf_Nod_All;


typedef struct { // struct ktory bedzie przechowywal dane o krawedziach
    char nazwa[50];
    int node1; // skąd 
    int node2; // do kąd
    double waga;

} Edge;

typedef struct{ // struct ktory bedzie przechowywal dane o krawedziach WSZYSTKICH
    Edge *Krawedzie; // lista z krawedziami
    int liczbaKrawedzi;
    
}graf_Edg_All;



#endif
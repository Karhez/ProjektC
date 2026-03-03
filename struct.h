

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

}grafWieCal;


typedef struct { // struct ktory bedzie przechowywal dane o krawedziach
    char *nazwa;
    int node1; // z kąd 
    int node2; // do kąd
    double waga;

} Krawedz;

typedef struct{ // struct ktory bedzie przechowywal dane o krawedziach WSZYSTKICH
    Krawedz *Krawedzie; // lista z krawedziami
    int liczbaKrawedzi;
    
}grafKraCal;



#endif
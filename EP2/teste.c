#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

#define MAX_PAISES 500

typedef int bool;
typedef struct aux {
    int id;
    int cor;
    int numVizinhos;
    struct aux** vizinhos;
} PAIS;

typedef struct {
    int numPaises;
    PAIS* paises;
} MAPA;

void imprimirMapa(MAPA map){
    int x, y;
    printf("Imprimindo mapa\n");
    for (x=0;x<map.numPaises;x++){
        printf("Pais %3i[%2i], Vizinhos:", map.paises[x].id, map.paises[x].cor);
        for (y=0;y<map.paises[x].numVizinhos;y++)
            printf(" %3i[%2i]", map.paises[x].vizinhos[y]->id, map.paises[x].vizinhos[y]->cor);
        printf("\n");
    }
}

void zerarCores(MAPA map){
    int x;
    for (x=0;x<map.numPaises;x++) map.paises[x].cor = -1;

}

int resolveGuloso(MAPA map){
    //complete aqui a função
}



bool resolveTentativaEErro(MAPA map, int maxCor) {
    //complete aqui a função
}

int main() {
    int x;
    int cores;
    int coresGuloso;
    MAPA map;
    map.numPaises =5;
    int numPaises =5;
    map.paises = (PAIS*) malloc(sizeof(PAIS)*numPaises);
    
    for (x = 0; x < numPaises; x++) {
        map.paises[x].id = x;
        map.paises[x].cor = -1;
        map.paises[x].numVizinhos = 0;
        map.paises[x].vizinhos = (PAIS**)malloc(sizeof(PAIS*) * MAX_PAISES); // Alocar memória para os vizinhos
    }

    map.paises[0].numVizinhos = 1;
    map.paises[1].numVizinhos = 2;
    map.paises[2].numVizinhos = 2;
    map.paises[3].numVizinhos = 2;
    map.paises[4].numVizinhos = 3;
    map.paises[0].vizinhos[0] = &(map.paises[4]);
    map.paises[1].vizinhos[0] = &(map.paises[2]);
    map.paises[1].vizinhos[1] = &(map.paises[3]);
    map.paises[2].vizinhos[0] = &(map.paises[1]); 
    map.paises[2].vizinhos[1] = &(map.paises[4]);
    map.paises[3].vizinhos[0] = &(map.paises[1]); 
    map.paises[3].vizinhos[1] = &(map.paises[4]); 
    map.paises[4].vizinhos[0] = &(map.paises[0]); 
    map.paises[4].vizinhos[1] = &(map.paises[2]); 
    map.paises[4].vizinhos[2] = &(map.paises[3]);

    imprimirMapa(map);
    coresGuloso = resolveGuloso(map);
    printf("\n\nO algoritmo guloso usou %i cor(es)\n",coresGuloso);
    imprimirMapa(map);
    printf("\n");

    for (cores=1; cores<=coresGuloso; cores++){
        zerarCores(map);
        printf("\n");
        if (resolveTentativaEErro(map,cores)) {
            printf("Foi possivel resolver o problema com %i cor(es).\n", cores);
            imprimirMapa(map);
            break;
        }
        else printf("Nao foi possivel resolver o problema com %i cor(es).\n", cores);
    }

    printf("\n\n");
}
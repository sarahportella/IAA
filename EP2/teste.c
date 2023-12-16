
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
    int p, v , c, livre;
    map.paises[0].cor = 0;// colore o primeiro pais
    int coresUsadas= 1;
    for ( p = 1 ; p < map.numPaises; p++){//itera entre casa pais
        for( c = 0 ; c < map.numPaises; c++){// itera entre cada cor
            if ( map.paises[p].cor == -1 ){
                livre = 0;
                for( v= 0 ; v < map.paises[p].numVizinhos; v++){//itera entre os vizinhos
                    if (map.paises[p].vizinhos[v]->cor == c) break;//testa se um vizinho já tem a cor testada atualmente
                    else livre ++;
                    if (livre == map.paises[p].numVizinhos){ 
                        map.paises[p].cor = c;
                        if (coresUsadas <= c) coresUsadas = (c+1);
                        break;
                    }
                }                
            } else if ( map.paises[p].cor != -1 ) break;
            
        }
    }
    return coresUsadas;
}

bool tenta(MAPA map, int maxCor, int paisAtual) {
    int c, v ;
    if (paisAtual == map.numPaises) return true;

    for (c = 0; c < maxCor; c++) {
        for (v = 0; v < map.paises[paisAtual].numVizinhos; v++) {
            if (map.paises[paisAtual].vizinhos[v]->cor == c) break;
        }
        if (v == map.paises[paisAtual].numVizinhos) {
            map.paises[paisAtual].cor = c;
            if (tenta(map, maxCor, paisAtual + 1)) return true;
        }
    }
    map.paises[paisAtual].cor = -1;
    return false;
}


bool resolveTentativaEErro(MAPA map, int maxCor) {
    map.paises[0].cor = 0;
    return tenta(map, maxCor, 0);
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

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






void zerarCores(MAPA map){
    int x;
    for (x=0;x<map.numPaises;x++) map.paises[x].cor = -1;

}

int resolveGuloso(MAPA map){
    int coresUsadas = 0;
    int p, v , c;

    for ( p = 0 ; p < map.numPaises; p++){
        //printf("1/n");
        //printf(" numero de paises no mapa é:%i\n", map.numPaises);
        for( c = 0 ; c < map.numPaises; c++){// itera entre cada pais
            //printf("2/n");// itera entre as cores
            for( v= 0; v < map.paises[p].numVizinhos; v++){//itera entre os vizinhos
                //printf("3/n");
                if ( map.paises[p].cor == -1 ){
                 //printf("4/n");
                    if (map.paises[p].vizinhos[v]->cor != c){ 
                        map.paises[p].cor = c;
                        coresUsadas ++;
                        //printf(" a cor do pais %i é:%i", p, c);
                    }
                }

            }
        }
    }
    printf(" As cores usadas foram :%i", coresUsadas);
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
    //map.paises[0].cor = 0;
    return tenta(map, maxCor, 0);
}


int main() {
    // Inicializando gerador de numeros pseudo aleatorios
    srand(42);
    int cores;
    int coresGuloso;
    MAPA map1;
    map.numPaises =4;
    map.paises = (PAIS*) malloc(sizeof(PAIS)*numPaises);
    for (x=0;x<numPaises;x++){
        map.paises[x].id = x;  
        map.paises[x].cor = -1;
    }
    map.paises[0].numvizinhos = 0;
    map.paises[1].numvizinhos = 2;
    map.paises[2].numvizinhos = 1;
    map.paises[3].numvizinhos = 1;
    map.paises[1].vizinhos[0] = &(map.paises[2]);
    map.paises[1].vizinhos[1] = &(map.paises[3]);
    map.paises[2].vizinhos[0] = &(map.paises[1]);
    map.paises[3].vizinhos[0] = &(map.paises[1]);



    imprimirMapa(map1);
    coresGuloso = resolveGuloso(map1);
    printf("\n\nO algoritmo guloso usou %i cor(es)\n",coresGuloso);
    imprimirMapa(map1);
    printf("\n");

    for (cores=1; cores<=coresGuloso; cores++){
        zerarCores(map1);
        printf("\n");
        if (resolveTentativaEErro(map1,cores)) {
            printf("Foi possivel resolver o problema com %i cor(es).\n", cores);
            imprimirMapa(map1);
            break;
        }
        else printf("Nao foi possivel resolver o problema com %i cor(es).\n", cores);
    }

    printf("\n\n");
}
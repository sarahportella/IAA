/*********************************************************************/
/**   ACH2002 - Introducao a Analise de Algoritmos                  **/
/**   EACH-USP - Segundo Semestre de 2023                           **/
/**   Turma 04 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Sarah Portella Forte                   8518075                **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

#define MAX_PAISES 500

typedef int bool;

/* Estrutura PAIS
   Tem por objetivo representar um pais. E uma estrutura que possui quatro campos:
   id do tipo inteiro que corresponde a um identificador unico de cada pais 
     (se houver dez paises no mapa, os identificadores serao de zero a nove);
   cor do tipo inteiro que corresponde a cor que suas funcoes irao atribuir a 
     cada paises (as cores validas correspondem a numeros inteiros nao negativos 
     [de zero em diante]); 
   numVizinhos do tipo inteiro que contem a quantidade de paises que sao 
     vizinhos do pais atual; e 
   vizinhos do tipo ponteiro para ponteiro de PAIS que corresponde a um ponteiro
     para um arranjo de ponteiros de paises, neste arranjo serao colocados os 
     enderecos de cada um dos paises que sao vizinhos do pais atual.
*/
typedef struct aux {
    int id;
    int cor;
    int numVizinhos;
    struct aux** vizinhos;
} PAIS;


/* Estrutura MAPA
   Tem por objetivo representar um mapa, isto e, um conjunto de paises.
   Esta estrutura possui dois campos:
   numPaises do tipo inteiro que contem a quantidade de paises do mapa; e 
   paises do tipo ponteiro para PAIS, correspondendo ao endereco do arranjo 
     de paises (de dados do tipo PAIS) do mapa.
*/
typedef struct {
    int numPaises;
    PAIS* paises;
} MAPA;


/* Funcao desenvolvida para criar mapas considerando o numero de paises e o 
   numero medio de vizinhos de cada pais.                                 
*/
MAPA criarMapa(int numPaises, int mediaVizinhos){
    printf("################# Criando mapa com %i pais(es) e com media de vizinhos igual a %i. #################\n",numPaises, mediaVizinhos);
    int x, y, v, total;
    MAPA map;
    if (numPaises < 1 || mediaVizinhos >= numPaises) {
        printf("Parametros invalidos, mapa nao sera gerado.\n");
        map.numPaises = 0;
        return map;    
    }
    map.numPaises = numPaises;
    map.paises = (PAIS*) malloc(sizeof(PAIS)*numPaises);
    
    int vizinhanca[numPaises][numPaises];
    for (x=0;x<numPaises;x++)
        for (y=0;y<numPaises;y++)
            vizinhanca[x][y] = 0;
            
    total = numPaises*mediaVizinhos/2;
    for (v=0;v<total;v++){
        x = rand()%numPaises;
        y = rand()%numPaises;
        if (x!=y && vizinhanca[x][y] == 0){
            vizinhanca[x][y] = 1;
            vizinhanca[y][x] = 1;
        }else v--; // precisara escolher outro
    }
    
    for (x=0;x<numPaises;x++){
        map.paises[x].id = x;  
        map.paises[x].cor = -1;
        v = 0;
        for (y=0;y<numPaises;y++) if (vizinhanca[x][y]) v++;
        map.paises[x].vizinhos = (PAIS**) malloc(sizeof(PAIS*)*v);
        map.paises[x].numVizinhos = v;
    }
        
    for (x=0;x<numPaises;x++){
        v = 0;
        for (y=0;y<numPaises;y++) 
            if (vizinhanca[x][y]){
                map.paises[x].vizinhos[v] = &(map.paises[y]);
                v++;
            }
    }
    return map;
}

/* Funcao desenvolvida para imprimir um mapa.
   Para cada pais, a funcao imprime seu id, sua cor e o conjunto de paises
   vizinhos com suas respectivas cores.      
*/
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


/* Funcao que coloca a cor 'invalida' -1 em todos os paises do mapa. */
void zerarCores(MAPA map){
    int x;
    for (x=0;x<map.numPaises;x++) map.paises[x].cor = -1;
    
}


/* Funcao que recebe um mapa como parametro, colore este mapa e retorna o 
   numero de cores utilizadas para colorir, de acordo com o criterio guloso 
   apresentado a seguir.
   Para cada pais do arranjo de paises (comecando do primeiro, isto e, daquele
   da posicao 0 (zero) do arranjo) colocar a primeira cor valida/viavel 
   (comecando da cor zero em diante [um, dois ...]). Uma cor e considerada 
   valida para o presente pais, caso nenhum de seus vizinhos ja esteja colorido
   com essa cor.
*/
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




/* Funcao que recebe um mapa como parametro e um numero de cores (maxCor) e
   tenta colorir o mapa usando o numero de cores passado como parametro.
   Se for possivel colorir o mapa, a funcao devera atribuir cores aos paises
   e retornar true, caso contrario, devera retornar false. Esta funcao deve 
   seguir estritamente a estrategia de Tentativa e Erro apresentada a seguir.
   ESTRATEGIA - Tentativa e Erro: a partir do pais atual (comecando do 
   primeiro do arranjo) ha maxCor acoes potencialmente possiveis (que devem
   ser seguidas nesta ordem): colocar a cor 0 (zero) no pais atual, colocar a
   cor 1 no pais atual, colocar a cor 2 no pais atual, ... colocar a cor 
   maxCor-1 no pais atual. Uma acao e considera viavel caso nenhum dos paises 
   vizinhos do pais atual ja esteja colorido com a cor da acao atual. Caso seja
   possivel tomar a acao, o pais atual devera receber a cor atual e o algoritmo
   devera tentar colorir o proximo pais. Se todos os paises estiverem coloridos,
   a funcao devera retornar true. Se nao for possivel colorir o pais com a cor 
   atual, o algoritmo devera tentar colorir com a proxima cor. Se nao for
   possivel colorir o pais atual com nenhuma cor, o algoritmo devera marcar o
   pais atual com a ``cor'' -1 e retornar (backtracking) para tentar outra 
   coloracao (tentar, por exemplo, colorir o pais anterior com outra cor.
*/

bool tenta(MAPA map, int maxCor, int paisAtual) {
    int c, v;
    int coresUsadas = 1;
    if (paisAtual == map.numPaises){
        for (v = 0; v < map.numPaises; v++){
            if (map.paises[v].cor >= coresUsadas) coresUsadas = map.paises[v].cor+1;
        }
        //printf("Cores usadas: %i", coresUsadas);
        if ( coresUsadas <= maxCor) return true;
        //return true;
    }  

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
    return tenta(map, maxCor, 1);
}


/* Funcao main que cria alguns mapas e invoca as funcoes gulosa e de tentativa
   e erro para tentar colorir cada um dos mapas.
   Esta funcao nao testa todos os detalhes envolvidos no problema de coloracao
   de mapas.
*/
int main() {
    // Inicializando gerador de numeros pseudo aleatorios
    srand(42);
    int cores;
    int coresGuloso;
    MAPA map1;
      
    
    map1 = criarMapa(1, 0);
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
    
    
        
    map1 = criarMapa(2, 1);
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
    
    
    map1 = criarMapa(4, 1);
    imprimirMapa(map1);
    coresGuloso = resolveGuloso(map1);
    printf("\n\nO algoritmo guloso usou %i cores\n",coresGuloso);
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
    
    
    
    map1 = criarMapa(20, 9);
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
    return 0;    
}
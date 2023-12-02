/*********************************************************************/
/**   ACH2002 - Introducao a Analise de Algoritmos                  **/
/**   EACH-USP - Segundo Semestre de 2023                           **/
/**   Turma 04 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   <nome do(a) aluno(a)>                   <numero USP>          **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

int varX[] = {1,0,0,-1};
int varY[] = {0,-1,1,0};

typedef int bool;


/* Estrutura que define um labirinto 
   linhas: numero de linhas (altura)
   colunas: numero de colunas (largura)
   inicioX: posicao inicial no eixo X
   inicioY: posicao inicial no eixo Y
   fimX: posicao final (destino/saida) no eixo X
   fimY: posicao final (destino/saida) no eixo Y
   labirinto: labirinto propriamente dito, representado como uma matriz
              (um arranjo de arranjos) de caracteres
*/
typedef struct {
    int linhas;
    int colunas;
    int inicioX;
    int fimX;
    int inicioY;
    int fimY;
    char** labirinto;
} LABIRINTO;

bool resolveLabirintoAux(LABIRINTO lab, int x, int y);


/* Funcao auxiliar para o sistema de correcao (nao mexer) */
void printf123(){
    // Funcao usada pelo sistema de correcao (nao mexer)
}


/* Funcao para criar um labirinto inicial (sem paredes internas), com as 
   dimensoes passadas como entrada, bem como as posicoes inicial e final. */
LABIRINTO criarLabirintoBase(int lin, int col, int iniX, int iniY, int fimX, int fimY){
    int x, y;
    printf("##### Criando labirindo de tamanho %i x %i, com inicio na posicao (%i,%i) e fim na posicao (%i,%i). #####\n", lin, col, iniX, iniY, fimX, fimY);
    LABIRINTO lab;
    lab.linhas = lin;
    lab.colunas = col;
    lab.inicioX = iniX;
    lab.fimX = fimX;
    lab.inicioY = iniY;
    lab.fimY = fimY;
    lab.labirinto = (char**) malloc(sizeof(char*)*lin);
    for (x=0;x<lin;x++)
        lab.labirinto[x] = (char*) malloc(sizeof(char)*col);  
    for (x=0;x<lin;x++)
        for (y=0;y<col;y++)
            lab.labirinto[x][y] = ' ';
            
    for (x=0;x<lin;x++){
        lab.labirinto[x][0] = '#';
        lab.labirinto[x][col-1] = '#';
    }
    
    for (y=0;y<col;y++){
        lab.labirinto[0][y] = '#';
        lab.labirinto[lin-1][y] = '#';
    }
    lab.labirinto[lab.inicioX][lab.inicioY] = 'I';
    lab.labirinto[lab.fimX][lab.fimY] = 'F';
    return lab;
}


/* Funcao para gerar ate uma certa quantidade de paredes de forma
   pseudoaleatoria dentro do labirinto passado como parametro.     */
void gerarParedes(LABIRINTO lab, int paredes){
    int px;
    int py;
    int p;
    for (p=0;p<paredes;p++){
        px = 1+rand() % (lab.linhas-1);
        py = 1+rand() % (lab.colunas-1);
        lab.labirinto[px][py] = '#';
    }
    lab.labirinto[lab.inicioX][lab.inicioY] = 'I';
    lab.labirinto[lab.fimX][lab.fimY] = 'F';
}


/* Funcao que imprime o labirinto passado como parametro */
void imprimirLabirinto(LABIRINTO lab){
    int x, y;
    printf("Imprimindo o labirinto\n");
    for (x=0;x<lab.linhas;x++){
        for (y=0;y<lab.colunas;y++)
            printf("%c",lab.labirinto[x][y]);
        printf("\n");
    }
    printf("\n");
}


/* Funcao que recebe um labirinto como parametro e deve resolve-lo seguindo
   estritamente uma abordagem de tentativa e erro. Se for possivel resolver
   o labirinto (isto e, a partir do inicio chegar no final) a funcao devera 
   retornar true, caso contrario devera retornar false.
   Adicionalmente, o percurso realizado dentro do labirinto deve ser indicado
   com o caractere '.' (ponto) no caso da funcao conseguir resolve-lo. Este 
   percurso devera seguir uma abordagem de tentativa e erro conforme descrito 
   a seguir.

   ESTRATEGIA: a partir de cada posicao (comecando do inicio) ha quatro acoes 
   potencialmente possiveis (que devem ser seguidas nesta ordem):
 1a) ir para baixo (isto e, aumentar 1 no valor da linha, sem mudar de coluna);
 2a) ir para a esquerda (isto e, diminuir 1 no valor da coluna, sem mudar de linha);
 3a) ir para a direita (isto e, aumentar 1 no valor da coluna, sem mudar de linha);
 4a) ir para cima (isto e, diminuir 1 no valor da linha, sem mudar de coluna).
   Um movimento possivel sera viavel caso a posicao de destino esteja preenchida
   com um espaco em branco no labirinto, neste caso, devera ser colocado um '.'
   (ponto) nessa posicao e o algoritmo devera tentar um novo movimento a partir
   dessa posicao. Se a posicao de destino for o fim ('F'), a funcao devera retornar
   true. Se nao for 'F' nem ' ', entao o movimento nao sera valido e o algoritmo 
   devera tentar outro movimento. Se nenhum movimento for possivel a partir da 
   posicao atual, o algoritmo devera desmarcar a posicao atual (substituir o '.' 
   por ' ') e voltar (backtracking) para tentar a solucao por outro caminho.
   
   Provavelmente voce precisar de uma funcao auxiliar (recursiva, usando 
   backtracking) para resolver este problema. A assinatura da funcao
   resolveLabirinto nao deve ser modificada, mas dentro dela voce pode chamar
   funcoes auxiliar, se desejar.
*/
bool resolveLabirinto(LABIRINTO lab){

    	/* COMPLETE A IMPLEMENTACAO DA FUNCAO*/
    	
    	return false;
}


/*
	Funcao main criada apenas para seus testes.
	Voce pode adicionar novos testes se quiser.
	ESTA FUNCAO SERA IGNORADA NA CORRECAO
*/
int main() {
    // Inicializando gerador de numeros pseudo aleatorios
    srand(42);
    LABIRINTO lab1;

    lab1 = criarLabirintoBase(4,4,1,1,2,2);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    printf("Gerando paredes aleatoriamente\n");
    gerarParedes(lab1, 1);
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);


    lab1 = criarLabirintoBase(5,5,1,1,3,3);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);



    lab1 = criarLabirintoBase(5,5,3,3,1,1);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);


    lab1 = criarLabirintoBase(10,20,8,1,8,18);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    printf("Gerando paredes aleatoriamente\n");
    gerarParedes(lab1, 60);
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);
    
    
    lab1 = criarLabirintoBase(4,4,1,1,2,2);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    lab1.labirinto[1][2] = '#';
    lab1.labirinto[2][1] = '#';
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);
    
    
    return 0;
}


/* SAIDA

##### Criando labirindo de tamanho 4 x 4, com inicio na posicao (1,1) e fim na posicao (2,2). #####
Labirinto vazio
Imprimindo o labirinto
####
#I #
# F#
####

Gerando paredes aleatoriamente
Imprimindo o labirinto
####
#I #
# F#
####

Saida encontrada!
Imprimindo o labirinto
####
#I #
#.F#
####

##### Criando labirindo de tamanho 5 x 5, com inicio na posicao (1,1) e fim na posicao (3,3). #####
Labirinto vazio
Imprimindo o labirinto
#####
#I  #
#   #
#  F#
#####

Saida encontrada!
Imprimindo o labirinto
#####
#I  #
#.  #
#..F#
#####

##### Criando labirindo de tamanho 5 x 5, com inicio na posicao (3,3) e fim na posicao (1,1). #####
Labirinto vazio
Imprimindo o labirinto
#####
#F  #
#   #
#  I#
#####

Saida encontrada!
Imprimindo o labirinto
#####
#F..#
#...#
#..I#
#####

##### Criando labirindo de tamanho 10 x 20, com inicio na posicao (8,1) e fim na posicao (8,18). #####
Labirinto vazio
Imprimindo o labirinto
####################
#                  #
#                  #
#                  #
#                  #
#                  #
#                  #
#                  #
#I                F#
####################

Gerando paredes aleatoriamente
Imprimindo o labirinto
####################
#   # # #    #  ## #
## #         #   ###
# ##   #   # # #   #
#     #   # # #  # #
#     # ##  ## ##  #
#   #              #
##  #  ##  # #  ## #
#I   #        #   F#
####################

Saida encontrada!
Imprimindo o labirinto
####################
#   # # #    #  ## #
## #         #   ###
# ##   #   # # #   #
#     #   # # #  # #
#.....# ##  ## ##  #
#.. #.      ...    #
##..#..##  #.#..## #
#I.. #....... #...F#
####################

##### Criando labirindo de tamanho 4 x 4, com inicio na posicao (1,1) e fim na posicao (2,2). #####
Labirinto vazio
Imprimindo o labirinto
####
#I #
# F#
####

Imprimindo o labirinto
####
#I##
##F#
####

Saida nao encontrada!
Imprimindo o labirinto
####
#I##
##F#
####

*/
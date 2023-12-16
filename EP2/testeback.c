1	
2	#include <stdio.h>
3	#include <stdlib.h>
4	#define true 1
5	#define false 0
6	
7	#define MAX_PAISES 500
8	
9	typedef int bool;
10	
11	
12	typedef struct aux {
13	    int id;
14	    int cor;
15	    int numVizinhos;
16	    struct aux** vizinhos;
17	} PAIS;
18	
19	typedef struct {
20	    int numPaises;
21	    PAIS* paises;
22	} MAPA;
23	
24	void imprimirMapa(MAPA map){
25	    int x, y;
26	    printf("Imprimindo mapa\n");
27	    for (x=0;x<map.numPaises;x++){
28	        printf("Pais %3i[%2i], Vizinhos:", map.paises[x].id, map.paises[x].cor);
29	        for (y=0;y<map.paises[x].numVizinhos;y++)
30	            printf(" %3i[%2i]", map.paises[x].vizinhos[y]->id, map.paises[x].vizinhos[y]->cor);
31	        printf("\n");
32	    }
33	}
34	
35	void zerarCores(MAPA map){
36	    int x;
37	    for (x=0;x<map.numPaises;x++) map.paises[x].cor = -1;
38	
39	}
40	
41	
42	
43	bool tenta(MAPA map, int maxCor, int paisAtual) {
44	    int c, v ;
45	    if (paisAtual == map.numPaises) return true;
46	
47	    for (c = 0; c < maxCor; c++) {
48	        for (v = 0; v < map.paises[paisAtual].numVizinhos; v++) {
49	            if (map.paises[paisAtual].vizinhos[v]->cor == c) break;
50	        }
51	        if (v == map.paises[paisAtual].numVizinhos) {
52	            map.paises[paisAtual].cor = c;
53	            if (tenta(map, maxCor, paisAtual + 1)) return true;
54	        }
55	    }
56	    map.paises[paisAtual].cor = -1;
57	    return false;
58	}
59	
60	
61	bool resolveTentativaEErro(MAPA map, int maxCor) {
62	    return tenta(map, maxCor, 0);
63	}
64	
65	
66	int main() {
67	    int cores;
68	    int x;
69	    int coresGuloso;
70	    MAPA map;
71	    int numPaises =4;
72	    map.numPaises =4;
73	    map.paises = (PAIS*) malloc(sizeof(PAIS)*numPaises);
74	    for (x=0;x<numPaises;x++){
75	        map.paises[x].id = x;  
76	        map.paises[x].cor = -1;
77	    }
78	    map.paises[0].numVizinhos = 0;
        map.paises[1].numVizinhos = 2;
        map.paises[2].numVizinhos = 2;
        map.paises[3].numVizinhos = 3;
        map.paises[4].numVizinhos = 3;
        map.paises[0].vizinhos[0] = &(map.paises[4]);
        map.paises[1].vizinhos[0] = &(map.paises[2]);
        map.paises[1].vizinhos[1] = &(map.paises[3]);
        map.paises[2].vizinhos[0] = &(map.paises[1]);
        map.paises[3].vizinhos[0] = &(map.paises[1]);
        map.paises[4].vizinhos[0] = &(map.paises[0]);
        map.paises[4].vizinhos[0] = &(map.paises[2]);
        map.paises[4].vizinhos[0] = &(map.paises[3]);
86	
87	
88	
89	    imprimirMapa(map);
90	    coresGuloso = 10;
91	
92	    for (cores=1; cores<=coresGuloso; cores++){
93	        zerarCores(map);
94	        printf("\n");
95	        if (resolveTentativaEErro(map,cores)) {
96	            printf("Foi possivel resolver o problema com %i cor(es).\n", cores);
97	            imprimirMapa(map);
98	            break;
99	        }
100	        else printf("Nao foi possivel resolver o problema com %i cor(es).\n", cores);
101	    }
102	
103	    printf("\n\n");
104	}
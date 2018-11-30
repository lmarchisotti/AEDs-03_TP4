#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<unistd.h>

// Estrutura que define cada Vértice do Grafo
typedef struct NO{
	char id;
	int nroVizinhos;
	struct NO **vizinhos;
	int visitado;
	int cor;
}*VERTICE;

int numv;
int cormax;

char string_i[40];
char string_o[40];
int max_arestas;
VERTICE criaVertice(int id);
void ligaVertices(VERTICE v1, VERTICE v2);
void Shellsort (VERTICE *vet, int tam);
void LIMPA_VISITAS (VERTICE *GRAFO, int tam);
void Colorindo (VERTICE *GRAFO, int tam);
int COR_MAX(VERTICE *GRAFO, int tam);
VERTICE *Leitura(char *string);
int CLR_HEURISTICA(VERTICE *GRAFO);
int CLR_SEQUENCIAL(VERTICE *GRAFO);
void CLR_BACKTRACK(VERTICE *GRAFO);
void Backtracking(VERTICE *GRAFO, int k, int N);
int Seguro(VERTICE *GRAFO, int k, int c);
void Argumentos (int argc, char *argv[]);
void Imprimir_usuario (struct timeval start, struct timeval tend);
void Imprimir_sistema (struct timeval start, struct timeval tend);


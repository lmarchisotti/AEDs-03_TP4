#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<unistd.h>

#ifndef _REENTRANT 
#define _REENTRANT 
#endif 

#define MAXWORKERS 4
// Estrutura que define cada Vértice do Grafo
typedef struct NO{
	int id;
	int nroVizinhos;
	struct NO **vizinhos;
	int visitado;
	int lock;
	int cor;
}*VERTICE;

pthread_mutex_t barrier;  /* mutex lock for the barrier */
pthread_mutex_t checkcormax; /* mutex lock for checking maximum and minimum*/ 
pthread_mutex_t teste;
pthread_mutex_t bagLock; /* mutex lock for bag of tasks*/
pthread_cond_t go;        /* condition variable for leaving */

int numWorkers;           /* number of workers */ 
int numArrived;       /* number who have arrived */

int nextRow;  /* Counter for our bag of task */
int nextVertice;
int numv;
int cormax;

char string_i[40];
char string_o[40];
int max_arestas;

VERTICE *CLR1;
VERTICE *CLR3;

void *funcao(void*arg);
void *Worker(void *arg);
void *Worker2(void *arg);
VERTICE criaVertice(int id);
void ligaVertices(VERTICE v1, VERTICE v2);
void Shellsort (VERTICE *vet, int tam);
void LIMPA_VISITAS (VERTICE *GRAFO, int tam);
void Colorindo (VERTICE *GRAFO, int tam);
int COR_MAX(VERTICE *GRAFO, int tam);
VERTICE *Leitura(char *string);
int CLR_HEURISTICA(VERTICE *GRAFO);
int CLR_SEQUENCIAL(VERTICE *GRAFO);
void CLR_BACKTRACK(VERTICE *GRAFO, int N);
void Backtracking(VERTICE *GRAFO, int k, int N);
int Seguro(VERTICE *GRAFO, int k, int c);
void Argumentos (int argc, char *argv[]);
void Imprimir_usuario (struct timeval start, struct timeval tend);
void Imprimir_sistema (struct timeval start, struct timeval tend);


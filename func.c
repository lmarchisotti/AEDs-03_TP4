#include "TP.h"

VERTICE criaVertice(int id){                    // Onde é feita a inicialização de cada vértice

	VERTICE novoVertice = (VERTICE) malloc(sizeof(struct NO)); // Aloca um novo Vértice
	novoVertice->id = id;                      // Identidade do Vértice
	novoVertice->nroVizinhos = 0;              // Número de vizinhos para a lista de adjacência
	novoVertice->visitado = 0;                 // Funciona como uma variável booleana, avisando se o vértice já foi visitado
	novoVertice->cor = 0;                      // Cor do vértice
    novoVertice->vizinhos = (VERTICE*) malloc (max_arestas * sizeof(struct NO));    // Vértices adjacentes
    for (int i = 0; i < max_arestas; i++){      // Número máximo de vértices adjacentes
		novoVertice->vizinhos[i] = NULL;
	}
	return novoVertice;                         // retorna o vértice
}

void ligaVertices(VERTICE v1, VERTICE v2){      // Faz a ligação entre os vértices
	int aux = 0;
	while(v1->vizinhos[aux] != NULL){ // Busca a primeira posição 'vazia'(NULL) dos vizinhos
		aux++;
	}
	v1->vizinhos[aux] = v2; // Adiciona o novo vizinho a lista de vizinhos
	aux = 0;
	while(v2->vizinhos[aux] != NULL){ // Busca a primeira posição 'vazia'(NULL) dos vizinhos
		aux++;
	}
	v2->vizinhos[aux] = v1; // Adiciona o novo vizinho a lista de vizinhos
	v1->nroVizinhos++; // Incrementa o número de vizinhos
	v2->nroVizinhos++; // Incrementa o número de vizinhos
}

void Shellsort (VERTICE *vet, int tam){                     // Algoritmo de ordenação em ordem crescente em função do 
                                                            // número de vizinhos (grau do vértice). 
    int i , j;                                              // Variáveis do contador: i e j. E variável int tam é o tamanho do meu vetor(ou quantidade de pontos)
    VERTICE aux;                                            // Crio uma variável auxiliar "aux" do tipo VERTICE
    int intervalo = 1;                                      
    
    while(intervalo < tam){                                                                 
    intervalo = 3*intervalo+1;                              
    }
    while ( intervalo > 1) {                                
    intervalo /= 3;                                         
        for(i = intervalo; i < tam; i++) {                  
        aux = vet[i];                                       
        j = i - intervalo;
            while (j >= 0 && aux->nroVizinhos < vet[j]->nroVizinhos) {
            vet[j + intervalo] = vet[j];
            j -= intervalo;
            }
        vet[j + intervalo] = aux;
        }
    }
}

void LIMPA_VISITAS (VERTICE *GRAFO, int tam){   // Reseta o número de visitas dos vértices do grafo

	for (int i = 0; i < tam; i++){
		GRAFO[i]->visitado = 0;
	}
}
void Colorindo (VERTICE *GRAFO, int tam){       // Função que encontra a menor cor possível para se colorir o vertice

int cor = 0;
int cont = -1;

// É passado por referência um vértice GRAFO[tam], tal que para encontrar a menor cor possível que o colore, é feito um laço
// que irá parar quando o contador "cont" for igual a zero. Toda vez que se inicia o laço, é incrementado a cor ( inicialmente setada como 0),
// e resetado o contador. Caso exista algum vértice adjacente com a mesma coloração, iremos incrementar o "cont", senão encontramos a menor cor possível
	while(cont!=0){                            
		cont = 0;
		cor++;
		for (int i = 0; ((cont == 0) && (i < GRAFO[tam]->nroVizinhos)); i++){
			if (cor == GRAFO[tam]->vizinhos[i]->cor){
				cont++;
			}
		}
	}
	GRAFO[tam]->cor = cor;                      // Colorimos o vértice
}

int COR_MAX(VERTICE *GRAFO, int tam){           
	int cor = 0;

	LIMPA_VISITAS (GRAFO,tam);                 // Reseta o número de visita dos vértices
	
	for (int i = tam; i >= 0; i--){            // Como foi feita uma ordenação crescente previamente, logo
                                               // é feito um for decrescente, para orderar de forma decrescente o grafo
		Colorindo(GRAFO,i);                    // Encontra a menor cor possível para o vértice dado
        // printf ("VERTICE: [%d] Cor: [%d]\n", GRAFO[i]->id, GRAFO[i]->cor);
        GRAFO[i]->visitado = 1;                // Define como visitado

        for (int j = 0; j < GRAFO[i]->nroVizinhos; j++){        // Confere todos os vértices adjacentes se já foram visitados
            if ( GRAFO[i]->vizinhos[j]->visitado == 0){         // Colore os vertices não-visitados com a cor do vértice mandante
                GRAFO[i]->vizinhos[j]->cor = GRAFO[i]->cor;
            }
        }
	}
	
	for (int i = 0; i <= tam ; i++){                            // Encontra a maior cor do grafo e determina o valor mínimo
		if (GRAFO[i]->cor > cor){                               // de cores necessário para colorir o grafo
            // printf ("VERTICE: [%d] Cor: [%d]\n", GRAFO[i]->id, GRAFO[i]->cor);
			cor = GRAFO[i]->cor;
		}
	}
	return cor;
}

VERTICE *Leitura(char *string){                               // Função que lê dados dos arquivos
    int i, A, B;                                              // int i = contador, int A = Vértice A e int B = Vértice B

    FILE *read;                                               // Ponteiro que irá ler o arquivo.
    read = fopen (string,"r");                                // Ponteiro "read" abre o arquivo de entrada e fará a leitura dos caracteres do arquivo
    if (read == NULL){                                        // Caso o ponteiro "read" não ler nada, aparecerá a mensagem de erro.
        printf ("Arquivo não existente.\n");
        exit (1);
    }
    else{
        fscanf(read, "%d", &numv);                            // Caso exista o arquivo, o ponteiro irá ler a primeira linha do documento
        printf ("Vertices: %d\n", numv);                      // e armazerar o valor do numéro máximo de vertices na variável global "numv"
        max_arestas = numv * (numv-1);                        // Logo será definido o número máximo de arestas  
        VERTICE *leitura = (VERTICE*) malloc(sizeof(VERTICE)*(numv+1));  // É feita uma alocação dinâmica para armazenar todos os vértices
        for ( i = 0; i < numv+1; i++){
            leitura[i] = criaVertice(i);                      // Os vértices são inicializados
        }
        while(!feof(read)){                                   // Depois o ponteiro irá seguir da segunda linha do documento até o fim
            fscanf (read,"%d" "%d", &A, &B);                  // Os dados recebidos são responsáveis por indicar a ligação entre os vértices
            ligaVertices(leitura[A], leitura[B]);             // que serão armazenados nas variáveis A e B e logo em seguida será feita a ligação dos vértices
        }                                                     // na função ligaVertices.
        fclose(read);                                         // Ponteiro "read" fecha o arquivo.

        return leitura;
        }                                                     // retorna o primeiro elemento do vetor de vértices (grafo)
    }

int CLR_HEURISTICA(VERTICE *GRAFO){                           // Heurística de coloração gulosa que utiliza um algoritmo de ordenação para ordenar os vértices 
// de um vetor em função do grau. Depois percorre cada vértice encontrando a menor cor possível que poderá ser colorida. Assim que encontrada a cor, ela será definitiva para este vértice.
// Em seguida, define o vetor colorido como "visitado" e o colore, com a mesma cor, seus vértices adjacentes que ainda não foram visitados(definidos).
    Shellsort(GRAFO,numv);                                    // Algoritmo de Ordenação

    int cor = COR_MAX(GRAFO,numv);                            // Função que colore os vértices

    printf ("\nCor Mínima: Coloração Heurística = %d\n", cor);// Printa o valor da cor mínima

    return cor;
}

int CLR_SEQUENCIAL(VERTICE *GRAFO){     // Heurística de coloração gulosa que percorre os vértices do grafo determinando a coloração
// mínima de cada vértice comparando com seus vértices adjacentes. Esta coloração é feita utilizando um vetor de vértices. Em seguida utilizaremos um laço
// para percorer o vetor. O vértice "GRAFO[i]" será enviado como argumento para a função "Colorindo". Cada vez que um vértice for colorido,
// será feita uma comparação entre a cor desse vertice com a variável "cor", se a cor do vértice for maior que a cor da variável "cor", logo a variável "cor" receberá
// o valor cromático do vértice.

    int cor = 0;

    for (int i = 0; i <= numv; i++){
        Colorindo(GRAFO,i);
		if (GRAFO[i]->cor > cor){
			cor = GRAFO[i]->cor;
		}
    }

    printf ("\nCor Mínima: Coloração Sequencial =  %d\n",cor);

    return cor;
}
void CLR_BACKTRACK(VERTICE *GRAFO, int N){     // Algoritmo de força bruta guloso que encontrará todas as possíveis soluções do grafo e retornará
// o menor valor cromático possível. A coloração com Backtracking utiliza a mesma estratégia da Heurística Sequencial, porém é replicando o
// mesmo comportamento da Heurística Sequencial para todos os caminhos possíveis.
    Backtracking(GRAFO,0,N);             // Função recursiva que faz as paradas
    printf ("\nCor Mínima: Coloração Backtracking = %d\n", cormax);
}
void Backtracking(VERTICE *GRAFO, int k, int N){   
    int cor;
    int c;

    if (k == 0){
        c = N;
    }
    else{
        c = 1;
    }
    while(c <= cormax+1){
    // for (c = N; c <= cormax+1; c++){                // Laço de "c" que vai até cormax ( dado inicialmente como max_arestas+1, porém é reduzido
    // a medida que vai encontrando colorações menores, funcionando como uma poda...)
        if (( N != c)&&( k == 0)){
        return;
        }
        if (Seguro(GRAFO, k, c) == 1){                  // Confere se este vértice pode ser colorido por "c"
            GRAFO[k]->cor = c;                          // Se passar no teste da função "Seguro", logo a cor de c é atribuida ao vértice[k]
            if ( k+1 <= numv){                          // Aqui acontece a recursividade do backtracking, se k+1 <= número de vértices,
                Backtracking(GRAFO,k+1,c);                // ele entra novamente passando por referencia o próximo vértice, senão
            }                                           // ele retorna um passo atrás. E fica nisso até percorrer todos os caminhos possíveis.
            else{
                cor = 0;
                for (int i = 0; i <= numv; i++){        // Encontra a maior cor do grafo atual
                    if (GRAFO[i]->cor > cor){
                        cor = GRAFO[i]->cor;
                    }
                    // printf ("VERTICE [%d] COR[%d]\n", GRAFO[i]->id, GRAFO[i]->cor);
                }
                // printf ("\n");
                pthread_mutex_lock(&checkcormax);       /* Critical area, here we check for the maximum and minimum element */       
                if (cor < cormax){                      // Se a cor encontrada for menor que a cor anteriormente conhecida como menor,
                    cormax = cor;                       // define a cor atual como menor.
                }
                pthread_mutex_unlock(&checkcormax);
                return;
            }
        }
    c++;
    }
}

int Seguro(VERTICE *GRAFO, int k, int c){               // Verifica se a cor em referência é diferente das cores
// dos vértices adjacentes.
    for (int i = 0; i < GRAFO[k]->nroVizinhos; i++){    // i até o número de vértices adjacentes
        if (c == GRAFO[k]->vizinhos[i]->cor){           // Se for igual, retorna 0 e sai da função.
            return 0;                                   // Se for diferente, sai da função retornando 1. Significa que a cor referenciada 
        }                                               // pode ser atribuida à cor do vértice
    }
    return 1;
}
void Argumentos (int argc, char *argv[]){      // Esta função manipula os arquivos de entrada e saída digitados na linha de comando 
  for(int i = 0; i < argc; i++){               // Utilizamos um "for" para percorrer os argumentos
    if(strcmp(argv[i], "-i")==0){              // quando encontrarmos o parâmetro "-i",
      i++;                                     // incrementamos i, logo o próximo argumento será a entrada.
      strcpy(string_i, argv[i]);               // Logo a string "string_i" recebe o argumento de argv[i](entrada).
    }                                          // E...
    else if(strcmp(argv[i], "-o")==0){         // quando encontrarmos o parâmetro "-o",
      i++;                                     // incrementamos i, logo o proximo argumento será a saída.
      strcpy(string_o, argv[i]);               // Logo a string "string_o" recebe o argumento de argv[i](saída).
    }
  }
}

void *Worker(void *arg){
    int *myid = arg;
    int row;

#ifdef DEBUG
printf("worker %d (pthread id %d) has started\n", myid, pthread_self());
#endif


    while(1){
    /* Get task from bag */
    pthread_mutex_lock(&bagLock);
    
    printf ("!!!%d\n", *myid);
    row = nextRow;
    printf ("???ROW = %d\n", row);
    nextRow++;

    pthread_mutex_unlock(&bagLock);

    /* If we are already finished with the bag, lets break out of the while loop */    
        if(row >= cormax){
            printf ("$$$$ACABOU\n");
        break;
        }

    CLR_BACKTRACK(CLR3,row);
    }
}
void *funcao(void *arg){
    int *myid = arg;

    printf ("Thread %i executando\n",*myid);
}

void Imprimir_usuario (struct timeval start, struct timeval tend){                    // Função Tempo utilizando getrusage
    // start.tv_sec e start.tv_usec são dadas em long int, porém são de grandezas escalares diferentes, pois são segundos
    // e micro-segundos(1 milhão de vezes menor que o segundo) respectivamente.
    // O tempo de leitura é dado por "startsec", que foi onde terminamos de analisar o tempo de leitura e começamos a analisar o tempo de processamento do algoritmo
    double startsec = (((double)start.tv_sec) + ((double)start.tv_usec/1000000));   // O tempo total do programa é dado por "endsec".
    double endsec = (((double)tend.tv_sec) + ((double)tend.tv_usec/1000000));       // O tempo de processamento do algoritmo de ordenação e 
    double process = (endsec - startsec);                                           // comparação é dado pela diferença de "endsec" e "startsec"
                                                                                    // 
    printf ("\nTempo de Leitura: %.5f segundos.\n Tempo de Processamento: %.5f segundos.\n", startsec, process);
}

void Imprimir_sistema (struct timeval start, struct timeval tend){                    // Função Tempo utilizando getrusage
  double sistema = (((double)tend.tv_sec) + ((double)tend.tv_usec/1000000)) - (((double)start.tv_sec) + ((double)start.tv_usec/1000000));
  printf ("Tempo Sistema: %.5f segundos.\n", sistema);
}
#include "TP.h"

int main(int argc, char *argv[]){
    Argumentos(argc, argv);

    int ID[MAXWORKERS];
    int ID2[MAXWORKERS];

    nextRow = 1;
    nextVertice = 0;
    numArrived = 0;
    numWorkers = MAXWORKERS;

    pthread_attr_t attr;
    pthread_t workerid[MAXWORKERS];

    /* set global thread attributes */
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    /* initialize mutex and condition variable */
    pthread_mutex_init(&barrier, NULL);
    pthread_cond_init(&go, NULL);

    /* initialize mutex for cormax and bag of tasks*/
    pthread_mutex_init(&checkcormax, NULL);
    pthread_mutex_init(&bagLock, NULL);
    pthread_mutex_init(&teste, NULL);

    struct rusage usage;                                // Struct utilizada para contagem de tempo da biblioteca #include<sys/time.h>
    
    struct timeval usu_comeco_seq, usu_fim_seq;         // Struct utilizada para marcar o começo e o fim da contagem
    struct timeval sis_comeco_seq, sis_fim_seq;         // de tempo do Algoritmo de Coloração Sequencial

    // struct timeval usu_comeco_heu, usu_fim_heu;         // Struct utilizada para marcar o começo e o fim da contagem
    // struct timeval sis_comeco_heu, sis_fim_heu;         // de tempo do Algoritmo de Coloração Heurística

    struct timeval usu_comeco_back, usu_fim_back;       // Struct utilizada para marcar o começo e o fim da contagem
    struct timeval sis_comeco_back, sis_fim_back;       // de tempo do Algoritmo de Coloração com Backtracking
    struct timeval comeco, fim;

    gettimeofday(&comeco,NULL);                         // Se inicia a contagem do tempo total do programa

    // COLORAÇÂO SEQUENCIAL

    CLR1 = Leitura(string_i);                           // É feito a leitura do arquivo de entrada e seu grafo resultante é 
                                                        // gravado em um vetor que será recebido pelo ponteiro CLR1
    getrusage(RUSAGE_SELF, &usage);                     // Função que irá fazer a contagem de tempo do usuário e do sistema 
    
    usu_comeco_seq = usage.ru_utime;                    // Inicia a contagem do tempo usuário para o Algoritmo de Coloração Sequencial
    sis_comeco_seq = usage.ru_stime;                    // Inicia a contagem do tempo sistema para o Algoritmo de Coloração Sequencial
    
    for (int l = 0; l < numWorkers; l++){
        ID2[l] = l+1;
        pthread_create(&workerid[l], &attr, Worker2, (void*)&ID2[l]);
    }
    for (int l = 0; l < numWorkers; l++){
        pthread_join(workerid[l], NULL);
    }
    CLR_SEQUENCIAL(CLR1);

    getrusage(RUSAGE_SELF, &usage);                     // Finaliza a contagem do tempo e retorna o tempo gasto executando do algoritmo 
    usu_fim_seq = usage.ru_utime;                       // Tempo total executando o algoritmo
    sis_fim_seq = usage.ru_stime;                       // Tempo real que o sistema gastou executando o algoritmo

    Imprimir_usuario(usu_comeco_seq, usu_fim_seq);          // Imprime o tempo de leitura, processamento e total
    Imprimir_sistema(sis_comeco_seq, sis_fim_seq);          // Imprime o tempo do sistema

    // COLORAÇÂO HEURISTICA

    // VERTICE *CLR2 = Leitura(string_i);                           // É feito a leitura do arquivo de entrada e seu grafo resultante é 
    //                                                     // gravado em um vetor que será recebido pelo ponteiro CLR1
    // getrusage(RUSAGE_SELF, &usage);                     // Função que irá fazer a contagem de tempo do usuário e do sistema
    // usu_comeco_heu = usage.ru_utime;                    // Inicia a contagem do tempo usuário para o Algoritmo de Coloração Heurística
    // sis_comeco_heu = usage.ru_stime;                    // Inicia a contagem do tempo sistema para o Algoritmo de Coloração Heurística
    
    // CLR_HEURISTICA(CLR2);                               // Algoritmo de Coloração Heurística
    
    // getrusage(RUSAGE_SELF, &usage);                     // Função que irá fazer a contagem de tempo do usuário e do sistema
    // usu_fim_heu = usage.ru_utime;                       // Tempo total executando o algoritmo
    // sis_fim_heu = usage.ru_stime;                       // Tempo real que o sistema gastou executando o algoritmo

    // Imprimir_usuario(usu_comeco_heu, usu_fim_heu);          // Imprime o tempo de leitura, processamento e total
    // Imprimir_sistema(sis_comeco_heu, sis_fim_heu);          // Imprime o tempo do sistema

    // COLORAÇÂO BACKTRACKING                           

    CLR3 = Leitura(string_i);                           // É feito a leitura do arquivo de entrada e seu grafo resultante é 
                                                        // gravado em um vetor que será recebido pelo ponteiro CLR3

    getrusage(RUSAGE_SELF, &usage);                     // Função que irá fazer a contagem de tempo do usuário e do sistema
    usu_comeco_back = usage.ru_utime;                   // Inicia a contagem do tempo usuário para o Algoritmo de Coloração com Backtracking
    sis_comeco_back = usage.ru_stime;                   // Inicia a contagem do tempo sistema para o Algoritmo de Coloração com Backtracking

    cormax = numv; // Variável Global que receberá o valor mínimo cromático do grafo

    for (int l = 0; l < numWorkers; l++){
        ID[l] = l+1;
        pthread_create(&workerid[l], &attr, Worker, (void*)&ID[l]);
    }
    for (int l = 0; l < numWorkers; l++){
        pthread_join(workerid[l], NULL);
    }
    
    printf ("\n!!!!!Cor Mínima: Coloração Backtracking = %d\n", cormax);

    getrusage(RUSAGE_SELF, &usage);                     // Função que irá fazer a contagem de tempo do usuário e do sistema
    usu_fim_back = usage.ru_utime;                      // Inicia a contagem do tempo usuário para o Algoritmo de Coloração Backtracking
    sis_fim_back = usage.ru_stime;                      // Inicia a contagem do tempo sistema para o Algoritmo de Coloração Backtracking

    Imprimir_usuario(usu_comeco_back, usu_fim_back);          // Imprime o tempo de leitura, processamento e total
    Imprimir_sistema(sis_comeco_back, sis_fim_back);          // Imprime o tempo do sistema

    gettimeofday(&fim,NULL);                                  // Finaliza a contagem do tempo total do programa

    double total = (((double)fim.tv_sec) + ((double)fim.tv_usec/1000000)) - (((double)comeco.tv_sec) + ((double)comeco.tv_usec/1000000));
    printf ("\nTempo Total: %.5f segundos.\n", total);        // tv_sec e tv_usec são dadas em long int, porém são de grandezas escalares diferentes, pois são segundos
    // e micro-segundos(1 milhão de vezes menor que o segundo) respectivamente. Para torná-los equivalente, logo é feito uma divisão do tv_usec por 1 milhão
    // Então são somados os segundos e os micro-segundos iniciais e finais e em seguida é feito uma subtração do tempo final pelo tempo inicial. 
    // O tempo é determinado pela função gettimeofday que é utilizado durante todo o processo de execução do programa.
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define PAELLASPORTACHO 12
#define NUMERODECONVIDADOS 30
#define UMTEMPO 1/60

// Variáveis de controle do sistema.
pthread_mutex_t mutTacho = PTHREAD_MUTEX_INITIALIZER;
            
pthread_cond_t  cozinheiroCond,
                convidadoCond;

// Variáveis de controle da lógica.
sem_t *paellasNoTacho;
int exit = 0;

// Variáveis de análise.
int tachosFeitos = 0,
    numRefeicoes = 0,
    numTotalRefeicoes = 0;

void main(){

    // Variáveis de criação.
    pthread_t   cozinheiro,
                convidado[NUMERODECONVIDADOS];

    //Criar todas as threads;   
    pthread_create(&cozinheiro, NULL, Cozinheiro, &paellasNoTacho);
    for(int i = 0 ; i < NUMERODECONVIDADOS ; ++i){ pthread_create(&convidado[i], NULL, Convidado, i); }

    //acao final do rei para medir tudo
    /*
    while(){
        sleep (3) ;
        pthread_mutex_lock (&mut) ;
        printf ("Refeições a cada 3 segundos: %d\n", numRefeicoes) ;
        numTotalRefeicoes += numRefeicoes;
        numRefeicoes = 0 ;
        pthread_mutex_unlock (&mut) ;
        i--;
    }*/

    /*
        Esperar todas as threads encerrarem;
    */

    /*
        mostrar lista de convidados e quantas refeições cada um pegou;
    */

    /*
        mostrar total de refeições servidas;
    */

    /*
        mostrar quantas vezes o cozinheiro teve que fazer tachos.
    */
}


//Convidado---------------------
void *Convidado(int threadIndice){
    pthread_mutex_lock(&mutTacho);
    while(!exit || sem_getvalue(paellasNoTacho, NULL) > 0){
        if(sem_getvalue(paellasNoTacho, NULL) > 0){
            servir(pthread_self, threadIndice);
            pthread_mutex_unlock(&mutTacho);
            comer(pthread_self, threadIndice);
        }else{
            pthread_mutex_unlock(&mutTacho);
            chamar_cozinheiro(pthread_self, threadIndice);
        }
        pthread_cond_wait(&convidadoCond, NULL);
    }
    pthread_exit(NULL);
}

void servir(int threadID, int threadIndice){
    printf("Thread: %d (Convidado[%d]) - servindo-se...", threadID, threadIndice);
    sleep(UMTEMPO);
}

void comer(int threadID, int threadIndice){
    printf("Thread: %d (Convidado[%d]) - comendo...", threadID, threadIndice);
    srand(time(NULL));
    sleep((2 + (rand() % 4)) * UMTEMPO);
}

void chamar_cozinheiro(int threadID, int threadIndice){
    printf("Thread: %d (Convidado[%d]) - chamando cozinheiro...", threadID, threadIndice);
    pthread_cond_signal(&cozinheiroCond);
}
//Convidado---------------------

//Cozinheiro---------------------
void *Cozinheiro(){
    while(!exit){
        if(sem_getvalue(paellasNoTacho, NULL) == 0){
            preparar_comida(pthread_self);
            encher_tacho(pthread_self);
            avisar_corte(pthread_self);
            voltar_cozinha(pthread_self);
        }
    }
    pthread_exit(NULL);
}

void preparar_comida(int threadID){
    printf("Thread: %d (Cozinheiro) - preparando o tacho...", threadID);
    sleep(3*UMTEMPO);
}

void encher_tacho(int threadID){
    pthread_mutex_lock(&mutTacho);
    printf("Thread: %d (Cozinheiro) - trocando tacho da mesa...", threadID);
    sleep(2*UMTEMPO);
    for(int i = 0 ; i < PAELLASPORTACHO ; ++i){sem_post(paellasNoTacho);}
    tachosFeitos++;
    pthread_mutex_unlock(&mutTacho);
}

void avisar_corte(int threadID){
    printf("Thread: %d (Cozinheiro) - avisando corte...", threadID);
    pthread_cond_broadcast(&convidadoCond);
}

void voltar_cozinha(int threadID){
    printf("Thread: %d (Cozinheiro) - voltando a cozinha...", threadID);
    pthread_cond_wait(&cozinheiroCond, NULL);
}
//Cozinheiro---------------------
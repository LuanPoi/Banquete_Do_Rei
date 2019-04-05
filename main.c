#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMERODECONVIDADOS 30
#define UMTEMPO 1/60
// Variáveis de análise.
int tachosFeitos = 0,
    numRefeicoes = 0,
    numTotalRefeicoes = 0;
// Variáveis de controle do sistema.
pthread_mutex_t mutTacho = PTHREAD_MUTEX_INITIALIZER,
                mutCozinheiro = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cozinheiroUP,
                tachoUP;
// Variáveis de controle da lógica.
int paellasNoTacho = 0;

void *print_message_function( void *ptr );

void main(){


    const char *messageking = "Thread rei criada!";
    const char *messagecook = "Thread cozinheiro foi criada!";
    // Variáveis de criação.
    pthread_t rei, cozinheiro, convidado[NUMERODECONVIDADOS];
    pthread_create(&rei, NULL, print_message_function, (void*) messageking);

    pthread_create(&cozinheiro, NULL, print_message_function, (void*) messagecook);

    //Criacao das threads convidado
    int i = 1;
    while(i <= NUMERODECONVIDADOS){
        pthread_mutex_lock(&mutTacho);
        //alterar o segundo NULL para que o print esteja nele...
        pthread_create(&convidado[i], NULL, print_message_function, (void*) &convidado[i]);
        printf("Criando thread convidado %d ...\n ",i);
        i++;
        pthread_mutex_unlock(&mutTacho);
    }
/*
    for(int k = 0; k <30; k++){
        printf("%02x", (((unsigned char) &k) + i - 1));
    }*/

    /*
        Inicializar todas as threads;
    */

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


void *print_message_function( void *ptr ){
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}

//Convidado---------------------
void *Convidado( void *ptr){
    while(1){
        if(paellasNoTacho > 0){
            servir();
            comer();
        }else{
            chamar_cozinheiro();
        }
    }
}

void servir(){}

void comer(){}

void chamar_cozinheiro(){}
//Convidado---------------------

void *Cozinheiro( void *ptr ){
    while(1){
        if(paellasNoTacho == 0){
            preparar_comida();
            encher_tacho();
            avisar_corte();
            voltar_cozinha();
        }
    }
}

void preparar_comida(){
    printf("O Cozinheiro (Thread: %s) esta preparando o tacho...", pthread_self);
    sleep(3*UMTEMPO);
}

void encher_tacho(){
    pthread_mutex_lock(&mutTacho);
    printf("O Cozinheiro (Thread: %s) esta trocando o tacho da mesa...", pthread_self);
    sleep(2*UMTEMPO);
    paellasNoTacho = 12;
    pthread_mutex_unlock(&mutTacho);
}

void avisar_corte(){int pthread_cond_broadcast(pthread_cond_t *tachoUP);}

void voltar_cozinha(){int pthread_cond_wait(pthread_cond_t *restrict cozinheiroUP, pthread_mutex_t *restrict mutCozinheiro);}
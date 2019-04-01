#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMERODECONVIDADOS 30



void *print_message_function( void *ptr );

void main(){
    

    const char *messageking = "Thread rei criada!";
    const char *messagecook = "Thread cozinheiro foi criada!";
    // Variáveis de criação.
    pthread_t rei, cozinheiro, convidado[NUMERODECONVIDADOS];
    pthread_create(&rei, NULL, print_message_function, (void*) messageking);
    
    pthread_create(&cozinheiro, NULL, print_message_function, (void*) messagecook);
    
    // Variáveis de análise.
    int tachosFeitos = 0, numRefeicoes = 0, numTotalRefeicoes = 0;
    // Variáveis de controle do sistema.
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
    // Variáveis de controle da lógica.
    int paellasNoTacho = 0;

    //Criacao das threads convidado
    int i = 1;
    while(i <= NUMERODECONVIDADOS){
        pthread_mutex_lock(&mut);
        //alterar o segundo NULL para que o print esteja nele...
        pthread_create(&convidado[i], NULL, print_message_function, (void*) &convidado[i]);
        printf("Criando thread convidado %d ...\n ",i);
        i++;
        pthread_mutex_unlock(&mut);
    }
/*
    for(int k = 0; k <30; k++){
        printf("%02x", *(((unsigned char*) &k) + i - 1));
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


void *print_message_function( void *ptr )
{
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}


/*
void preparar_comida(){
    pthread_mutex_lock (&mut);
    printf("Preparando comida...");
}
*/  
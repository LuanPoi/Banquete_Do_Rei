#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void main(){
    
    // Variáveis de criação.
    pthread_t convidados[30] = NULL, cozinheiro = NULL;
    // Variáveis de análise.
    int tachosFeitos = 0, numRefeicoes = 0, numTotalRefeicoes = 0;
    // Variáveis de controle do sistema.
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
    // Variáveis de controle da lógica.
    int paellasNoTacho = 0;

    /*
        Inicializar todas as threads;
    */

    while(/*até que tenha dado a condição de parada de 1 minuto*/){
        sleep (3) ;
        pthread_mutex_lock (&mut) ;
        printf ("Refeições a cada 3 segundos: %d\n", numRefeicoes) ;
        numTotalRefeicoes += numRefeicoes;
        numRefeicoes = 0 ;
        pthread_mutex_unlock (&mut) ;
    }

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
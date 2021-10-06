#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

//Question 1.2 :
// kill -s INT : le message 'success' est affiché
// sans le "-s INT" pour kill: le message 'success' ne s'affiche pas

// Question 1.2 (suivante)
// kill avec l'option -s INT affiche le message
// kill avec le PID du père sans option ne fait rien
// kill avec le PID du père avec l'option "-s INT" ne fait rien non plus

int running = 1;

void stop_handler(int sig) {
    printf("signal reçu : %i  \n", sig);
    running = 0;
}

int main() {

    struct sigaction action;
    action.sa_handler = stop_handler;
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);

    while(running == 1) {
        printf("hello world \n");

        int pid_fils = getpid();
        printf("pid fils vaut : %i \n", pid_fils);

        int pid_pere = getppid();
        printf("pid pere vaut : %i \n", pid_pere);

        int nombre_aleatoire = rand() % 100;
        printf("nombre aleatoire : %i \n", nombre_aleatoire);

        sleep(1);

    }
    printf("success ! \n");

    return EXIT_SUCCESS; //constante qui vaut 0
}
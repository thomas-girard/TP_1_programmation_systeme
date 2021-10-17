#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>


int running = 1;

void stop_handler(int sig) {
    printf("signal reçu : %i  \n", sig);
    running = 0;
}

void exit_message() {
    printf("message de exit_message \n");
}

int main() {

    struct sigaction action;
    action.sa_handler = stop_handler;
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);

    int cr = atexit( exit_message );

    pid_t pid = fork();

    int retour =0;

    wait(&retour);

    if (pid != 0) {
        printf("type arrêt  : %i \n", retour);

        if (retour == 9) {
            printf("kill avec kill -9 \n");
        }

        if (retour == 0) {
            printf("kill avec kill sans argument \n");
        }
    }

    while(running == 1) {
        printf("hello world \n");

        int pid_programme = getpid();
        printf("pid vaut : %i \n", pid_programme);

        int pid_pere = getppid();
        printf("pid pere vaut : %i \n", pid_pere);

        int nombre_aleatoire = rand() % 100;
        printf("nombre aleatoire : %i \n", nombre_aleatoire);

        sleep(3);

    }
    printf("success ! \n");

    return EXIT_SUCCESS; //constante qui vaut 0
}
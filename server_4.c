#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

//Question 1.2 :
// kill -s INT : le message 'success' est affiché
// sans le "-s INT" pour kill: le message 'success' ne s'affiche pas
// suite de 1.2 :
// kill avec l'option -s INT affiche le message
// kill avec le PID du père sans option n'affiche pas le message
// kill avec le PID du père avec l'option "-s KILL" fait crasher la fenêtre du bash
// il est impossible d'afficher un message avec -s KILL
//sans modifier la variable running : ctr + c tue le programme au bout de la 2ème fois// kill sans option ne tue pas le programme // kill -9 tue le programme sans message de fin

// Question 1.3 :
// avec ctr + c : fonction atexit activée
// avec kill : fonction atexit activée
// avec kill -9 : fonction atexit pas activée

// Question 2.1
// Le processus père du fils vaut est le pid fils du processus père, donc tout est bon : ils n'ont pas même PID et on peut donc les distinguer
// Les processus s'arrêtent avec ctr +c
// en tuant le processus fils puis ps a : on a un message <defunct> qui apparait pour le processus fils (et on a la lettre Z+ pour zombie)
// En tuant le père : avec ps a : on a plus ni processus pere ni fils, les messages


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

        int pid_fils = getpid();
        printf("pid fils vaut : %i \n", pid_fils);

        int pid_pere = getppid();
        printf("pid pere vaut : %i \n", pid_pere);

        int nombre_aleatoire = rand() % 100;
        printf("nombre aleatoire : %i \n", nombre_aleatoire);

        sleep(3);

    }
    printf("success ! \n");

    return EXIT_SUCCESS; //constante qui vaut 0
}
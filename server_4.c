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

    int fds[2];
    pipe(fds);

    pid_t pid = fork();

    while(running == 1) {
        //printf("hello world \n");

        int pid_programme = getpid();
        printf("pid vaut : %i \n", pid_programme);

        int pid_pere = getppid();
        printf("pid pere vaut : %i \n", pid_pere);

        int valeur_entree=rand() % 100;

        if(pid != 0) {  //pere
            close(fds[0]);
            write(fds[1], &valeur_entree , sizeof(valeur_entree));
            printf("processus pere, valeur envoyee : %i \n", valeur_entree);
            sigaction(SIGPIPE, &action, NULL); //permet au père d'afficher les messages du fils quand on tue le fils en premier
            }
        else {   //fils
            close(fds[1]);
            dup2(fds[0], STDIN_FILENO);
            int valeur_retour;
            read(fds[0], &valeur_retour , sizeof(valeur_retour));
            printf("processus fils, valeur reçue : %i \n", valeur_retour);
            if (getppid() == 1) { //le père a été tué, il faut tuer le fils
                return EXIT_SUCCESS;
            }
        }

        sleep(3);

    }
    printf("success ! \n");

    return EXIT_SUCCESS; //constante qui vaut 0
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>


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

    char * fifo = "fifo_q3";
    int file;
    file = open(fifo, O_RDONLY);


    while (running == 1) {
        int pid_programme = getpid();
        printf("pid vaut : %i \n", pid_programme);
        int valeur_retour;
        ssize_t size_read = read(file, & valeur_retour, sizeof(valeur_retour)); //a read() with a count of 0 returns zero
        printf("la valeur reçue par le client est : %i \n", valeur_retour);
        //sigaction(SIGPIPE, &action, NULL); ne sert que à l'écriture, pas à la lecture

        if (size_read== 0) {
            return EXIT_SUCCESS;
        }

        sleep(3);
    }

    close(file);
    printf("success ! \n");

    return EXIT_SUCCESS; //constante qui vaut 0
}
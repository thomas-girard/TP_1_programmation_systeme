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
// Le processus père du fils vaut est le pid du processus père, donc tout est bon : ils n'ont pas même PID et on peut donc les distinguer
// Les processus s'arrêtent avec ctr +c
// en tuant le processus fils puis ps a : on a un message <defunct> qui apparait pour le processus fils (et on a la lettre Z+ pour zombie)
// En tuant le père : avec ps a : on a plus ni processus pere ni fils, les messages

// Question 2.2
// Quand on arrête le fils (celui qui écoute), ça arrête le père
// Quand on arrête le père (celui qui parle), ça n'arrête pas le fils

//getppid + getkill


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

    //int valeur_entree=666;

    //int retour =0;

    //wait(&retour);

    // if (pid != 0) {
    //     printf("type arrêt  : %i \n", retour);
    //     if (retour == 9) {
    //         printf("kill avec kill -9 \n");
    //     }
    //     if (retour == 0) {
    //         printf("kill avec kill sans argument \n");
    //     }
    // }

    while(running == 1) {
        //printf("hello world \n");

        int pid_fils = getpid();
        printf("pid fils vaut : %i \n", pid_fils);

        int pid_pere = getppid();
        printf("pid pere vaut : %i \n", pid_pere);

        // int nombre_aleatoire = rand() % 100;
        // printf("nombre aleatoire : %i \n", nombre_aleatoire);

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
            //printf("101 pid pere = %i \n", getppid());
            if (getppid() == 1) { //le père a été tué, il faut tuer le fils
                return EXIT_SUCCESS;
            }
        }

        sleep(3);

    }
    printf("success ! \n");

    return EXIT_SUCCESS; //constante qui vaut 0
}
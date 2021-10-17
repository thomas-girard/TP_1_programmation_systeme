#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    while(1) {
        printf("hello world \n");

        int pid_programme = getpid();
        printf("pid vaut : %i \n", pid_programme);

        int pid_pere = getppid();
        printf("pid pere vaut : %i \n", pid_pere);

        int nombre_aleatoire = rand() % 100;
        printf("nombre aleatoire : %i \n", nombre_aleatoire);

        sleep(1);
    }
    printf("success ! \n");

    return EXIT_SUCCESS; //constante qui vaut 0
}
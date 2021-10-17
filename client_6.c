#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <netdb.h>
#include <sys/socket.h>


#define PORT 8080
#define SA struct sockaddr


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

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    int buff;
    while (running==1) {

        read(sockfd, &buff, sizeof(buff));
        printf("le client reçoit la valeur : %i \n", buff);
        sleep(3);
    }

    // close the socket
    close(sockfd);
    printf("success ! \n");

    return EXIT_SUCCESS; //constante qui vaut 0
}
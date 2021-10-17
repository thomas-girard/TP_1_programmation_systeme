# TP_1_programmation_systeme par Thomas Girard

## Réponses aux questions

### 1.2
* kill -s INT : le message 'success' est affiché, mais sans l'option "-s INT" pour kill, le message 'success' ne s'affiche pas.
* avec l'option "-s KILL", il n'y a pas de message affiché, et il est impossible d'en afficher un
* en donnant à la commande kill le numéro de processus père :
    - sans l'option "-s kill" : le message de fin ne s'affiche pas
    - avec l'option "-s kill" : la fenêtre du bash crash
* Modification de la fonction stop_handler() afin de ne plus modifier la variable running :
    - avec "ctr + c" : le programme s'arrête au bout du deuxième "ctr + c" (et sans message de fin)
    - avec "kill" : le programme ne s'arrête pas
    - avec "kill + 9" : le programme s'arrête sans message de fin de programme

### 1.3
* avec "ctr + c" : la fonction atexit est activée
* avec "kill" : la fonction atexit est activée
* avec "kill +9" : la fonction atexit n'est pas activée

### 2.1
* Le processus père du fils est le pid du processus père; père et fils n'ont pas le même PID et on peut ainsi les distinguer et savoir qui est le père et qui est le fils.
* Les 2 processus s'arrêtent avec ctr +c
* En tuant le processus fils avec "kill" puis avec "ps a" : on a un message <defunct> qui apparait pour le processus fils (et on a la lettre Z+ pour zombie). Puis en tuant le père, on n'a plus ni processus père ni fils.
* Modifier votre programme pour que le père attende la fin d'exécution du fils en utilisant la fonction wait() : cf code pour la comparaison

### 2.2
* Quand on arrête le fils (celui qui écoute), ça arrête le père
* Quand on arrête le père (celui qui parle), ça n'arrête pas le fils





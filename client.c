#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <time.h>

#include "global.h"
#include "ask_name.c"
#include "ask_choice.c"


int main(int argc, char** argv){
    int port_client=3000;
    if (argc>1)
    {
        port_client=atoi(argv[1]);
    }
    
    struct sockaddr_in client_addr={
        .sin_addr.s_addr=INADDR_ANY,
        .sin_family=AF_INET,
        .sin_port=htons(port_client)
    };
    struct sockaddr_in server_addr={
        .sin_addr.s_addr=INADDR_ANY,
        .sin_family=AF_INET,
        .sin_port=htons(PORT_SERVER)
    };

    socklen_t len;

    /* lire l'heure courante */
    time_t now = time (NULL);
    
    /* la convertir en heure locale */
    struct tm tm_now = *localtime (&now);
    
    /* Créer une chaine JJ/MM/AAAA HH:MM:SS */
    char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];
    
    strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);


    int client_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    if(client_fd==-1)return EXIT_FAILURE;

    int check_error = bind(client_fd,(struct sockaddr*)&client_addr,sizeof client_addr);perror("bind");
    if(check_error==-1)return EXIT_FAILURE;

    check_error = connect(client_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("connect");
    if(check_error==-1)return EXIT_FAILURE;

    char nom[TAILLE_NOM];memset(nom,0,TAILLE_NOM);
    ask_name(nom);
    char choix[5];memset(choix,0,5);

    ask_choice(choix);

    printf("%s",choix);
    
    return 0;
    

    
    





    close(client_fd);
    

    


}
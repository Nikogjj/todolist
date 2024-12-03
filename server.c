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

    struct task_t{
        int ID;
        char date_heure[50];
        char text[255];
        int fait_ou_pas;
    };

int main(){
    struct sockaddr_in server_addr={
        .sin_addr.s_addr=INADDR_ANY,
        .sin_family=AF_INET,
        .sin_port=htons(PORT_SERVER)
    };
    struct sockaddr_in client_addr;
    socklen_t len;

    int server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    if(server_fd==-1)return EXIT_FAILURE;

    int check_error = bind(server_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("bind");
    if(check_error==-1)return EXIT_FAILURE;

    check_error = listen(server_fd,0);perror("listen");
    if(check_error==-1)return EXIT_FAILURE;

    int client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&len);perror("accept");
    if(client_fd==-1)return EXIT_FAILURE;


    char choix[5];memset(choix,0,5);
    recv(client_fd,choix,sizeof choix,0);



















    if (strcmp(choix,"1")==0)
    {
        char nom[TAILLE_NOM];
        recv(client_fd,nom,TAILLE_NOM,0);perror("recv if choix 1");

        FILE* fd;
        if ((fd =fopen(nom,"r"))==NULL)
        {
            send(client_fd,"Aucune tache n'est attribuée a votre nom\n",43,0);
            fclose(fd);
        }
        else
        {
            char fichier_tache[BUFSIZ];
            fread(fichier_tache,1,BUFSIZ,fd);
            send(client_fd,fichier_tache,BUFSIZ,0);
            fclose(fd);
        }
            
    }

    else if(strcmp(choix,"2")==0)
    {
        char nom[TAILLE_NOM];
        recv(client_fd,nom,TAILLE_NOM,0);
        FILE * fd;
        if ((fd = fopen(nom,"r"))== NULL)
        {
            fd = fopen(nom,"a+");
        } 
        else
        {
            fclose(fd);
            fd = fopen(nom,"a+");
        }
        char second_recv[TAILLE_MAX_TACHE];memset(second_recv,0,TAILLE_MAX_TACHE);
        recv(client_fd,second_recv,TAILLE_MAX_TACHE,0);perror("recv 1");
        // strcat(second_recv,a_faire);

        fwrite(second_recv,1,strlen(second_recv),fd);
        fclose(fd);
    }
    else
    {
        char nom[TAILLE_NOM];
        recv(client_fd,nom,TAILLE_NOM,0);perror("recv");
        FILE* fd;
        if ((fd =fopen(nom,"r"))==NULL)
        {
            send(client_fd,"Aucune tache n'est attribuée a votre nom\n",43,0);
            fclose(fd);
        }
        else
        {
            char fichier_tache[BUFSIZ];
            fread(fichier_tache,1,BUFSIZ,fd);
            send(client_fd,fichier_tache,BUFSIZ,0);perror("send le fichier");
            fclose(fd);
        }
        memset(choix,0,5);
        recv(client_fd,choix,5,0);
        fd = fopen(nom,"r+");
        fseek(fd,0,SEEK_SET);
        int count = atoi(choix);
        char ligne[255];memset(ligne,0,255);
        for (int i = 0; i < count; i++)
        {
            fgets(ligne,255,fd);
        }
        fseek(fd,-1,SEEK_CUR);
        // printf("la ligne : %s",ligne);
        char* fait=" ✅\n";
        // ligne[strlen(ligne)-1]=0;
        // strcat(ligne,fait);
        // printf("%s",ligne);
        fwrite(fait,1,strlen(fait),fd);

        fclose(fd);

    }
    
    return 0;

}
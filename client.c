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
    printf("Entrez votre nom\n");
    fgets(nom,TAILLE_NOM,stdin);
    nom[strlen(nom)-1]=0;

    printf("Entrez 1 pour voir vos taches\t\tEntrez 2 pour créer une tache\t\tEntrez 3 pour validé une tache\n");
    char choix[5];memset(choix,0,5);
    fgets(choix,5,stdin);
    choix[strlen(choix)-1]=0;

    if (strcmp(choix,"1")==0)
    {
        check_error = send(client_fd,choix,strlen(choix),0);perror("send (voir les taches)");
        if (check_error==-1)return EXIT_FAILURE;

        check_error = send(client_fd,nom,strlen(nom),0);perror("send (le nom)");
        if (check_error==-1)return EXIT_FAILURE;
        
        char fichier_tache[BUFSIZ];
        check_error = recv(client_fd,fichier_tache,BUFSIZ,0);perror("recv (voir les taches) ");
        if (check_error==-1)return EXIT_FAILURE;

        if (strcmp(fichier_tache,"Aucune tache n'est attribuée a votre nom\n")==0)
        {
            printf("\n%s",fichier_tache);
        }
        else
        {
            printf("\nVoici vos taches :\n\n%s",fichier_tache);

        }
        
    }
    else if(strcmp(choix,"2")==0)
    {
        check_error = send(client_fd,choix,strlen(choix),0);perror("send (voir les taches)");
        if (check_error==-1)return EXIT_FAILURE;
        
        char tache[TAILLE_MAX_TACHE-50];memset(tache,0,sizeof tache);
        printf("Entrez une tache à effectuer\n");
        fgets(tache,sizeof tache,stdin);
        tache[strlen(tache)-1]=' ';
        tache[strlen(tache)]=' ';


        char date_et_heure[TAILLE_MAX_TACHE];memset(date_et_heure,0,50);
        sprintf(date_et_heure,"[%s] : ",s_now);
        strcat(date_et_heure,tache);
        strcat(date_et_heure,"          \n");

        // envoi du nom
        check_error = send(client_fd,nom,TAILLE_NOM,0);perror("send");

        //envoi de la tache a effectuer avec l'heure et la date de l'envoi
        check_error = send(client_fd,date_et_heure,TAILLE_MAX_TACHE,0);perror("send");
        if(check_error==-1)return EXIT_FAILURE;
    }
    else
    {
        check_error = send(client_fd,choix,strlen(choix),0);perror("send (voir les taches)");
        if (check_error==-1)return EXIT_FAILURE;

        check_error = send(client_fd,nom,strlen(nom),0);perror("send (le nom)");
        if (check_error==-1)return EXIT_FAILURE;
        
        char fichier_tache[BUFSIZ];
        check_error = recv(client_fd,fichier_tache,BUFSIZ,0);perror("recv (voir les taches) ");
        if (check_error==-1)return EXIT_FAILURE;

        if(strcmp(fichier_tache,"Aucune tache n'est attribuée a votre nom\n")==0)
        {
            printf("%s",fichier_tache);
        }
        else
        {
            printf("%s",fichier_tache);
            printf("\nQuelle tache voulez-vous marquer comme faites ✅ ?\n");
            memset(choix,0,5);
            fgets(choix,5,stdin);
            choix[strlen(choix)-1]=0;
            send(client_fd,choix,5,0);
            printf("Tache n°%s mise a jour\n",choix);
        }

    }
    





    close(client_fd);
    

    


}
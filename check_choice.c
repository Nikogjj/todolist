#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

int ask_choice(char *choice){
    while (1)
    {
        printf("Entrez 1 pour voir vos taches\t\tEntrez 2 pour créer une tache\t\tEntrez 3 pour validé une tache\n");
        fgets(choice,5,stdin);
        choice[strlen(choice)-1]=0;

        if (strcmp(choice,"1")==0 || strcmp(choice,"2")==0 || strcmp(choice,"3")==0)
        {
            break;
        }
        else{
            printf("Veuillez rentrer un choix valide\n");
        }
           
    }
    
    
    return atoi(choice);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"

int ask_name(char *name){

    printf("Entrez votre nom (max %d caracteres)\n",TAILLE_NOM);
    fgets(name,TAILLE_NOM,stdin);
    name[strlen(name)-1]=0;   
    
    return 1;
}
#include "lib.h"

int getMode(){
    int mode=-1;
    while( mode != 2 && mode != 1 ){
        printf("\t\t --- 1 : 1 joueur --- \n");
        printf("\t\t --- 2 : 2 joueurs --- \n");
        scanf("%d",&mode);
    }
    return mode;
}

void getCode(char *chaineAleatoire){
    int i, longueurChaine = 0;
    char chaine[] = "abcdefghijklmnpqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
 
    longueurChaine = strlen(chaine);
 
    srand(time(NULL));
 
    for(i=0; i != 10; i++)
        {
            chaineAleatoire[i] = chaine[rand()%longueurChaine];
        }
    chaineAleatoire[10 - 1] = '\0';

}

int getDifficulty(){
    int mode=-1;
    while( mode < 1 || mode > 10 ){
        printf("\t\t --- 1 : Niveau 1 --- \n");
        printf("\t\t --- 2 : Niveau 2 --- \n");
        printf("\t\t --- 3 : Niveau 3 --- \n");
        printf("\t\t --- 4 : Niveau 4 --- \n");
        printf("\t\t --- 5 : Niveau 5 --- \n");
        printf("\t\t --- 6 : Niveau 5 --- \n");
        printf("\t\t --- 7 : Niveau 7 --- \n");
        printf("\t\t --- 8 : Niveau 8 --- \n");
        printf("\t\t --- 9 : Niveau 9 --- \n");
        printf("\t\t --- 10 : Niveau 10 --- \n");
        scanf("%d",&mode);
    }
    return mode;
}

void printInfoMessage(){
    printf("\n\n Erreur lors de l'execution du Programme !!! \n\n");
}
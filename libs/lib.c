#include "lib.h"

int writeScore(int score)
{
    char pseudo[TAILLE_MAX];
    printf("Quel est votre pseudo ?"); // amelioration : bloquer si plus de 30 caracteres 
    scanf("%s",pseudo);
    FILE* fichier = NULL;
    fichier=fopen("scores.txt","a");

    if (fichier != NULL)
    {
      fprintf(fichier, "Pseudo : %s ",pseudo);
      fprintf(fichier,"Score: %d \n",score);
      fclose(fichier);
    }
    return 0;
}
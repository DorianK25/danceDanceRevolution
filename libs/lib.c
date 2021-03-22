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
      fprintf(fichier, "Pseudo:%s;",pseudo);
      fprintf(fichier,"Score:%d\n",score);
      fclose(fichier);
    }
    return 0;
}

highScore triScore(char tab[10][TAILLE_MAX+20]){
  char* token; 
  token=strtok(tab[0],";");
  printf("%s",tab[0]);
  highScore topScore;

  while( token != NULL ) {
      printf( " %s\n", token );

      token = strtok(NULL,";");
   }
   return topScore;
}

highScore topScore(){
  FILE* fichier = NULL;
  fichier=fopen("scores.txt","r");
  char buff[TAILLE_MAX+20];
  char tab[10][TAILLE_MAX+20];
  int i=0;
  if(fichier != NULL){
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      //printf("%s\n",buff);
      strcpy(tab[i],buff);
    }
  }else{
    printf("\nFichier scores.txt non disponible\n");
  }
   return triScore(tab);
}
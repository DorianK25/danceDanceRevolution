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
      fprintf(fichier, "%s;",pseudo);
      fprintf(fichier,"%d\n",score);
      fclose(fichier);
    }
    return 0;
}

void triScore(int nb,char tab[nb][TAILLE_MAX+20]){
  char* pseudo[10];
  int score[10];
  char *ptr;
  char* tempoString;
  int tempoInt;
  char tri[nb][TAILLE_MAX+20];
  int i=0,j=0;
  highScore topScore;
  for(i=0;i<10;i++){
    pseudo[i]=strtok(tab[i],";");
    strcat(pseudo[i],"\0");
    tempoString=strtok(NULL,";");
    strcat(tempoString,"\0");
    score[i]=atoi(tempoString);
  }

  

  for(i=0;i<nb-1;i++)
      for(j=i+1;j<nb;j++)
          if ( score[i] < score[j] ) {
              tempoInt = score[i];
              score[i] = score[j];
              score[j] = tempoInt;
              tempoString = pseudo[i];
              pseudo[i] = pseudo[j];
              pseudo[j] = tempoString;
          }

  

  for(i=0;i<10;i++){
    topScore.top[i].pseudo=pseudo[i];
    topScore.top[i].score=score[i];
  }

  printf("\t\t Joueur : Score\n\n");
  for(i=0;i<10;i++){
    printf("\t\t %s : %d\n",topScore.top[i].pseudo,topScore.top[i].score);
  }

}

void topScore(){
  FILE* fichier = NULL;
  highScore null;
  fichier=fopen("scores.txt","r");
  char buff[TAILLE_MAX+20];
  int i=0;
  if(fichier != NULL){
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      i++;
    }
    char tab[i][TAILLE_MAX+20];
    fichier=fopen("scores.txt","r");
    i=0;
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      strcpy(tab[i],buff);
      i++;
    }
    triScore(i,tab);
  }else{
    printf("\nFichier scores.txt non disponible\n");
  }
}
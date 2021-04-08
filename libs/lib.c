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

// creer fonction qui va appeler 2 threads enfants
// 1 pour la lecture du clavier
// 1 pour afficher lettres à saisi
// pas appui entree -> entree automatique 

void afficherNiveau(int difficulte){
  int temp=1000000;
  char niveau[1024]="                          COUCOU MME LE GLAZ ON VOUS AIME";
  int i,longueur=strlen(niveau);
  char random[1024] = "\n\n\n\n\t\t\t_\n\t\t\t_";
  strcat(random,niveau);
  printf("%s\n\n\n",random);
  for(i=0;i<longueur;i++){
    decalerNiveau(niveau);
    strcpy(random,"\n\n\n\n\t\t\t_\n\t\t\t_");
    strcat(random,niveau);
    usleep(temp/difficulte);
    system("clear");
    printf("%s\n\n\n",random);
  }
}

void decalerNiveau(char niveau[1024]){
  int i=1;
  if(strlen(niveau)!=0){
    while(niveau[i-1] != '\0'){
    niveau[i-1] = niveau[i];
    i++;
    } 
  }
}

void getSaisie(){
  char c; 
  initscr();
  c= getch();
  endwin();
  printf("%c",c);
}
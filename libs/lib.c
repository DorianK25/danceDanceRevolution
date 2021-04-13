#include "lib.h"

/**
 * Fonction qui inverse une chaine de caractere
 * 
 * @param s 
 */
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }

int createSegment(int size){

    key_t key=IPC_PRIVATE;
    int right=0666 | IPC_CREAT | IPC_EXCL;
    int segment = shmget(key,sizeof(char)*size,right);

    if(segment==-1){
        fprintf(stderr,"%s","Une erreur s'est produite\n");
    }

    return segment;

}

char * attachSegment(int segment){

    char * attachement=shmat(segment,NULL,0);

    if(attachement==(char*)-1){
        fprintf(stderr,"%s","Une erreur s'est produite");
    }

    return attachement;

}

int detachSegment(char * attachement){

    int result = shmdt(attachement);

    if(result==-1){
        fprintf(stderr,"%s","Une erreur s'est produite");
    }

    return result;

}

int editSegment(int segment,int cmd,struct shmid_ds *buf){
    int result = shmctl(segment,cmd,buf);
    if(result==-1){
        fprintf(stderr,"%s","Une erreur s'est produite");
    }

    return result;
}

int deleteSegment(int segment,struct shmid_ds *buf){
    int result = shmctl(segment,IPC_RMID,buf);
    if(result==-1){
        fprintf(stderr,"%s","Une erreur s'est produite");
    }

    return result;
}





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

/**
 * Fonction qui trie les scores en fonction du plus fort
 * @param nb 
 * @param tab 
 */
void triScore(int nb,char tab[nb][TAILLE_MAX+20]){
  char* pseudo[10];
  int score[10];
  char *ptr;
  char* tempoString;
  int tempoInt;
  char tri[nb][TAILLE_MAX+20];
  int i=0,j=0;
  highScore topScore;
  for(i=0;i<nb;i++){
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

  
  if(nb>10)
    nb=10;
  for(i=0;i<nb;i++){
    topScore.top[i].pseudo=pseudo[i];
    topScore.top[i].score=score[i];
  }

  printf("\t\t Joueur : Score\n\n");
  for(i=0;i<nb;i++){
    printf("\t\t %s : %d\n",topScore.top[i].pseudo,topScore.top[i].score);
  }

}

/**
 * Fonction qui affiche le top des scores dans le fichier scores.txt
 * 
 */
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

int afficherNiveau(int difficulte){
  struct shmid_ds buf ;
  int idSegment=createSegment(100);
  editSegment(idSegment,IPC_STAT,&buf);
  
  char * partFils=attachSegment(idSegment);
  int temp=1000000;
  char random[1024] = "\n\n\n\n\t\t\t_\n\t\t\t_";
  char niveau[1024]="        coucou madame leglaz";
  int i,longueur=strlen(niveau);
  strcat(random,niveau);
  printf("fini");
  strcpy(partFils,niveau);

  int id=fork();
  if(id == 0){
    for(i=0;i<longueur;i++){
      decalerNiveau(niveau);
      strcpy(random,"\n\n\n\n\t\t\t_\n\t\t\t_");
      strcat(random,niveau);
      usleep(temp/difficulte);
      system("clear");
      printf("%s\n\n\n",random);
      strcpy(partFils,niveau);
    }
    system("clear");
    printf("\t\t appuyer sur Entree pour voir votre score");
    exit(1);
  }else{
    //pere
    int i=0;
    char c;
    char * partPere=attachSegment(idSegment);
  
    do{
      scanf("%c",&c);
    if(c==partPere[0])
      i+=difficulte;

      
    }while (strlen(partPere)!=0);
      return i;
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

/**
 * Fonction qui récupére la saisie clavier de l'utilisateur 
 * 
 * @return char 
 */
char getSaisie(){
  char c; 
  initscr();
  c= getch();
  endwin();
  return c;
}

/**
 * Fonction qui ecrit la salle dans le fichier room.txt
 * 
 * @param idSalle 
 * @param idProcessus 
 * @return int 
 */
int writeRoom(char* idSalle, int idProcessus)
{
    FILE* fichier = NULL;
    fichier=fopen("room.txt","a");

    if (fichier != NULL)
    {
      fprintf(fichier, "%s;",idSalle);
      fprintf(fichier,"%d\n",idProcessus);
      fclose(fichier);
    }
    return 0;
}

/**
 * Fonction qui lit la salle dans le fichier room.txt
 * 
 * @param idSalle 
 * @return int 
 */
int readRoom(char* idSalle){
  FILE* fichier = NULL;
  char* idRoom;
  fichier=fopen("room.txt","r");
  char buff[TAILLE_MAX+20];
  int i=0;
  if(fichier != NULL){
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      i++;
    }
    char tab[i][TAILLE_MAX+20];
    fichier=fopen("room.txt","r");
    i=0;
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      strcpy(tab[i],buff);
      idRoom=strtok(tab[i],";");

      if(!strcmp(idSalle,idRoom)){
        fclose(fichier);
        return atoi(strtok(NULL,";"));
      }
      i++;
    }
  }else{
    printf("\nFichier room.txt non disponible\n");
  }
  fclose(fichier);
  return -1;
}

/**
 * Fonction qui supprime 
 * 
 * @param idSalle 
 */
void deleteRoom(char* idSalle){
  FILE* fichier = NULL;
  FILE* fichier2 = NULL;
  char* idRoom;
  char* idProcessus = strtok(NULL,";");
  fichier=fopen("room.txt","r");
  fichier2 =fopen("temproom.txt","a");
  char buff[TAILLE_MAX+20];
  int i=0;
  if(fichier != NULL){
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      i++;
    }
    char tab[i][TAILLE_MAX+20];
    fichier=fopen("room.txt","r");
    i=0;
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      strcpy(tab[i],buff);
      idRoom=strtok(tab[i],";");
      idProcessus=strtok(NULL,";");
        if(strcmp(idSalle,idRoom)!=0){
          fprintf(fichier2, "%s;",idRoom);
          fprintf(fichier2,"%s\n",idProcessus);
        }
      i++;
    }
  }else{
    printf("\nFichier room.txt non disponible\n");
  }
  fclose(fichier2);
  rename("temproom.txt","room.txt");
  fclose(fichier);
}
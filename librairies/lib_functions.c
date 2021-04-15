#include "lib_functions.h"

/**
 * Fonction qui inverse une chaine de caractere
 * 
 * @param s : chaine de caractère à inverser
 */
 void reverse(char s[])
 {
     int i, j;
     char c;// variable pour la temporisation lors de l'échange de 2 caractères
    
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) { // on inverse toutes les lettres avec leur opposé jusqu'a la moitié
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

/**
 * Fonction qui transforme un int en chaine de caractere
 * 
 * @param s : chaine de caractère qui recevra l'int
 * @param n : int a transformer
 */
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

/**
 * Fonction qui cree un segment
 * 
 * @param size : taille du segment
 */
int createSegment(int size){

    key_t key=IPC_PRIVATE;// clé pour la création de notre segment
    int right=0666 | IPC_CREAT | IPC_EXCL;// droit du segment
    int segment = shmget(key,sizeof(char)*size,right);// creer notre segment et on recupère l'id

    if(segment==-1){ // si erreur 
        fprintf(stderr,"%s","Une erreur s'est produite\n");
    }

    return segment;

}

/**
 * Fonction qui attache un segment
 * 
 * @param segment : id du segment
 */
char * attachSegment(int segment){

    char * attachement=shmat(segment,NULL,0); // on attache le segment à une variable de type chaine de caractère

    if(attachement==(char*)-1){ // si erreur
        fprintf(stderr,"%s","Une erreur s'est produite");
    }

    return attachement;

}

/**
 * Fonction qui détache le segment
 * 
 * @param attchement : mémoire partagée
 */
int detachSegment(char * attachement){

    int result = shmdt(attachement);// on détache le segment 

    if(result==-1){ // si erreur
        fprintf(stderr,"%s","Une erreur s'est produite");
    }

    return result;

}

/**
 * Fonction qui modifie un segment
 * 
 * @param segment : id du segment
 * @param cmd : int de la commande
 * @param buf : structure accueillant les infos 
 */
int editSegment(int segment,int cmd,struct shmid_ds *buf){
    int result = shmctl(segment,cmd,buf); // on effectue une commande sur le segment
    if(result==-1){ // si erreur
        fprintf(stderr,"%s","Une erreur s'est produite");
    }

    return result;
}

/**
 * Fonction qui supprime le segment
 * 
 * @param segment : id du segment
 * @param buf : structure accueillant les infos 
 */
int deleteSegment(int segment,struct shmid_ds *buf){
    int result = shmctl(segment,IPC_RMID,buf); // on effectue une commande de suppression du segment
    if(result==-1){ // si erreur
        fprintf(stderr,"%s","Une erreur s'est produite");
    }

    return result;
}



/**
 * Fonction qui permet a l'utilisateur de choisir le mode
 */
int getMode(){
    int mode=-1; // on initialise la variable pou que l'on rentre dans le while
    while( mode != 2 && mode != 1 ){
        printf("\t\t --- 1 : 1 joueur --- \n");
        printf("\t\t --- 2 : 2 joueurs --- \n");
        while(scanf("%d",&mode) != 1) // demande à l'utilisateur de saisir le mode
        {
            printf("Entrez un ENTIER : ");
            while(getchar() != '\n');
        }
    }
    return mode;
}

/**
 * Fonction qui permet de donner le code
 */
void getCode(char *chaineAleatoire){
    int i, longueurChaine = 0; // on initialise les variables que l'on utilisera
    char chaine[] = "abcdefghijklmnpqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"; // toutes les variables possibles
 
    longueurChaine = strlen(chaine); // nombre de caractère différents
 
    srand(time(NULL));
 
    for(i=0; i != 10; i++)
        {
            chaineAleatoire[i] = chaine[rand()%longueurChaine];// on ajoute un caractère random de chaine
        }
    chaineAleatoire[10 - 1] = '\0';// on termine la chaine de caractère

}

/**
 * Fonction qui permet à l'utilisateur de choisir la difficulté
 */
int getDifficulty(){
    int code=-1; // on initialise la variable pour que l'on rentre dans le while
    while( code < 1 || code > 10 ){
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
        while(scanf("%d",&code) != 1) // demande à l'utilisateur de saisir le code
          {
              printf("Entrez un ENTIER : ");
              while(getchar() != '\n');
          }
    }
    return code;
}


/**
 * Fonction qui permet d'afficher le message d'infos
 */
void printInfoMessage(){
    printf("\n\n Erreur lors de l'execution du Programme !!! \n\n");
}


/**
 * Fonction qui permet d'écrire son score dans le fichier des scores
 */
int writeScore(int score)
{
    char pseudo[TAILLE_MAX]; // amelioration : bloquer si trop de caractère
    printf("Quel est votre pseudo ?");
    scanf("%s",pseudo);// on recupère le pseudo du joueur
    FILE* fichier = NULL;// initialisation du fichier
    fichier=fopen("scores.txt","a");// on ouvre le fichier de scores

    if (fichier != NULL)
    {
      fprintf(fichier, "%s;%d\n",pseudo,score);// on ecrit le pseudo puis un ; pour separer du score puis le score
      fclose(fichier);// on ferme le fichier
    }
    return 0;
}

/**
 * Fonction qui trie les scores en fonction dans l'ordre croissant
 * @param nb : nombre de personne en tête
 * @param tab : tableau des scores
 */
void triScore(int nb,char tab[nb][TAILLE_MAX+20]){
  
  // initialisation des variables
  char* pseudo[10];
  int score[10];
  char *ptr;
  char* tempoString;
  int tempoInt;
  char tri[nb][TAILLE_MAX+20];
  int i=0,j=0;
  highScore topScore;

  // on recupère le pseudo et le score sur notre tableau
  for(i=0;i<nb;i++){
    pseudo[i]=strtok(tab[i],";");
    strcat(pseudo[i],"\0");
    tempoString=strtok(NULL,";");
    strcat(tempoString,"\0");
    score[i]=atoi(tempoString);
  }

  // on tri le tableau
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

  
  if(nb>10)//s'il y a plus de 10 scores inscrit on s'arrete a 10
    nb=10;

  for(i=0;i<nb;i++){// on alimente la structure topScore
    topScore.top[i].pseudo=pseudo[i];
    topScore.top[i].score=score[i];
  }

  // on affiche le score
  printf("\t\t Joueur : Score\n\n");
  for(i=0;i<nb;i++){
    printf("\t\t %s : %d\n",topScore.top[i].pseudo,topScore.top[i].score);
  }

}

/**
 * Fonction qui affiche le top des scores dans le fichier scores.txt
 */
void topScore(){
  FILE* fichier = NULL;// on initialise le fichier
  highScore null;// on initialise la structure highscore
  fichier=fopen("scores.txt","r");// on ouvre le fichier texte des scores
  char buff[TAILLE_MAX+20];// initialisation du buffer
  int i=0;
  if(fichier != NULL){ // si on trouve le fichier

    // on compte le nombre de lignes
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      i++;
    }
    char tab[i][TAILLE_MAX+20];
    fichier=fopen("scores.txt","r");// on réouvre le fichier
    i=0;

    // on lit le fichier texte et on la place dans le tableau
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      strcpy(tab[i],buff);
      i++;
    }
    triScore(i,tab);// on appelle la fonction de tri
  }else{
    printf("\nFichier scores.txt non disponible\n");
  }
}
 
/**
 * Fonction principale qui permet d'afficher le niveau en fonction de la difficulté tout en recuperant l'entrée clavier et retourne le score
 * @param difficulte : difficulté du niveau
 */
int afficherNiveau(int difficulte){
  struct shmid_ds buf ;// on initialise la strucuture
  int idSegment=createSegment(100); // on cree le segment
  editSegment(idSegment,IPC_STAT,&buf); // on lui demande les infos
  
  char * partFils=attachSegment(idSegment);// on attache le segment
  int temp=1000000;// cela correspondra à 1 000 000 micros secondes soit 1 secondes
  char random[1024] = "\n\n\n\n\t\t\t_\n\t\t\t_";// entête du niveau
  char niveau[1024]="        coucou madame leglaz";// niveau

  int i,longueur=strlen(niveau);// longueur du niveau
  strcat(random,niveau);// on associe le niveau a l'entête
  strcpy(partFils,niveau);// on met le niveau dans notre mémoire partagée

  int id=fork(); // on cree un fils
  if(id == 0){
    // si fils 

    for(i=0;i<longueur;i++){// on decale le niveau jusqu'a la fin
      decalerNiveau(niveau);// on decale le niveau
      strcpy(random,"\n\n\n\n\t\t\t_\n\t\t\t_"); // on recree l'entête
      strcat(random,niveau); // on associe le niveau a l'entête
      usleep(temp/difficulte); // temporisation en fonction de la difficulté 
      system("clear");// on clear le terminal pour donner l'illusion d'un simple déplacement vers la droite (esthétique)
      printf("%s\n\n\n",random);// on affiche le niveau
      strcpy(partFils,niveau);// on copie de nouveau le niveau décalé dans la mémoire partagée
    }
    system("clear"); // on clear pour la fin
    printf("\t\t appuyer sur Entree pour voir votre score"); // instruction pour sortir du scanf chez le père
    exit(1);
  }else{
    // si pere
    int i=0;
    char c;
    char * partPere=attachSegment(idSegment);// on attache le segment
  
    do{
      scanf("%c",&c);// on demande à l'utilisateur le caractère
    if(c==partPere[0])// si le caractère correspond incrémente les points en fonction de la difficulté
      i+=difficulte;

      
    }while (strlen(partPere)!=0);// tant que le décalage de la chaine n'est pas fini
      return i;
  } 
}


/**
 * Fonction qui décale vers la gauche une chaine de caractère
 * 
 * @param niveau : chaine de caractère à décaler
 */
void decalerNiveau(char niveau[1024]){
  int i=1;
  if(strlen(niveau)!=0){
    while(niveau[i-1] != '\0'){// on décale tant que le caractère ne vaut pas \0
    niveau[i-1] = niveau[i];
    i++;
    } 
  }
}


/**
 * Fonction qui écrit la salle dans le fichier room.txt
 * 
 * @param idSalle : code de la salle
 * @param idProcessus : code du processus
 */
int writeRoom(char* idSalle, int idProcessus)
{
    FILE* fichier = NULL;// on initialise le fichier
    fichier=fopen("room.txt","a");// on ouvre le fichier des salles

    if (fichier != NULL)
    {
      fprintf(fichier, "%s;%d\n",idSalle,idProcessus);// on ecrit l'id de la salle puis notre séparateur ';' et pour finir l'id du processus qui a crée la salle
      fclose(fichier); // on ferme le fichier
    }
    return 0;
}

/**
 * Fonction qui lit la salle dans le fichier room.txt
 * 
 * @param idSalle : code de la salle
 */
int readRoom(char* idSalle){
  FILE* fichier = NULL; // on initialise le fichier
  char* idRoom;// on initialise l'id de la salle
  fichier=fopen("room.txt","r");// on ouvre le fichier texte des salles
  char buff[TAILLE_MAX+20];// on initialise le buffer
  int i=0;
  if(fichier != NULL){
    // si le fichier existe 

    //calul du nombre de ligne
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      i++;
    }
    char tab[i][TAILLE_MAX+20];// on initialise le tableau
    fichier=fopen("room.txt","r");// on réouvre le fichier pour redemarrer a la premiere ligne
    i=0;
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      strcpy(tab[i],buff);// on copie la ligne dans le tableau
      idRoom=strtok(tab[i],";");// on associe l'id de la salle 

      if(!strcmp(idSalle,idRoom)){// si l'id de la salle passé en param correspond à l'id de la salle du texte  
        fclose(fichier);
        return atoi(strtok(NULL,";"));// on retourne l'id du processus
      }
      i++;
    }
  }else{
    printf("\nFichier room.txt non disponible\n");
  }
  fclose(fichier);// on ferme le fichier
  return -1;// si pas de salle trouvée
}

/**
 * Fonction qui supprime la salle
 * 
 * @param idSalle : code de la salle
 */
void deleteRoom(char* idSalle){
  FILE* fichier = NULL; // on intialise le fichier
  FILE* fichier2 = NULL; // on intialise le fichier
  char* idRoom;// on intialise l'id de la salle
  char* idProcessus = strtok(NULL,";");// on intialise du processus
  fichier=fopen("room.txt","r");// on ouvre le fichier des salles
  fichier2 =fopen("temproom.txt","a");// on ouvre un fichier de temporiasation
  char buff[TAILLE_MAX+20];// on intialise le buffer
  int i=0;
  if(fichier != NULL){
    //si le fichier existe

    //on calcule le nombre de ligne
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      i++;
    }
    char tab[i][TAILLE_MAX+20];// on initialise le tableau en fonction du nombre de lignes
    fichier=fopen("room.txt","r");// on réouvre le fichier
    i=0;
    while (fscanf(fichier,"%s",buff) != EOF)
    {
      strcpy(tab[i],buff);// on copie le buffer dans le tableau
      idRoom=strtok(tab[i],";");// on stock l'id de la salle
      idProcessus=strtok(NULL,";");// on stock l'id du preocessus
        if(strcmp(idSalle,idRoom)!=0){ // si l'id de la salle est identique a l'id de salle passé en paramètre on n'écrit pas dans le fichier de temporisation
          fprintf(fichier2, "%s;%s\n",idRoom,idProcessus);// on ecrit dans le fichier de temporisation
        }
      i++;
    }
  }else{
    printf("\nFichier room.txt non disponible\n");
  }
  fclose(fichier2);// on ferme le fichier de temporisation
  rename("temproom.txt","room.txt");// on le renomme en fichier des salles pour écraser le précédent (recopie sauf si salle identique)
  fclose(fichier);// on ferme le fichier
}
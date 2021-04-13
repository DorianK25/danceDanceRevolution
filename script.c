#include "libs/lib.h"

int main(int argc, char *argv[]){

    int mode,difficulty;
    int tubeRecv;
    int tubeEnv;
    char code[11];
    char *name;
    char *pid;
    char buf[250];
    if(argc == 1){
        //création
        printf("Bonjour veuillez saisir votre Mode de jeu :\n\n");
        mode=getMode();
        difficulty=getDifficulty();
        getCode(code);
        

        //Creation des tubes

        if(mode == 2){
            writeRoom(code,getpid());
            printf("Votre code de salle d'attente est : %s\n\n",code);
            //itoa(getpid(),pid);
            strcpy(name,"./");
            strcat(name,pid);
           // mkfifo(name, 0666);
            //tubeRecv=open(name, O_RDWR);//on ouvre le tube1
            strcpy(name,"./");
            //read(tubeRecv,buf,sizeof(buf));
            strcat(name,buf);
           // tubeEnv=open(name, O_RDWR);
           // itoa(difficulty,buf);
           // write(tubeEnv, buf, sizeof(buf));//synchro
           // read(tubeRecv,buf,sizeof(buf));
        }
        
        
    }else if(argc == 2){
        mode=2;
        int id=readRoom(argv[1]);
        if(id==-1){
            printf("Salle non trouvée...\n\n");
            EXIT_FAILURE;
        }
        itoa(id,pid);
        strcpy(name,"./");
        strcat(name,pid);
        strcpy(code,argv[1]);
       // tubeEnv=open(name, O_RDWR);
        itoa(getpid(),buf);
        strcpy(name,"./");
        strcat(name,buf);
       // mkfifo(name, 0666);
       // tubeRecv=open(name, O_RDWR);
      //  write(tubeEnv, buf, sizeof(buf));
      //  read(tubeRecv,buf,sizeof(buf));
        difficulty=atoi(buf);
       // write(tubeEnv, buf, sizeof(buf));
    }else{
        printInfoMessage();
        return 0;
    }
    switch (mode)
    {
    case 1:
        printf("mode %d joueur, difficulté : %d\n",mode,difficulty);
        int score = afficherNiveau(difficulty);
        system("clear");
        printf("\t\t Votre score est de %d points\n\n",score);
        writeScore(score);
        topScore();
        break;
    case 2:
        printf("mode %d joueur, difficulté : %d\n",mode,difficulty);
        int scoreJ = afficherNiveau(difficulty);
        system("clear");
        printf("\t\t Votre score est de %d points\n\n",scoreJ);
        writeScore(scoreJ);
        topScore();
        break;
        /*printf("mode %d joueur, difficulté : %d, code : %s\n",mode,difficulty,code);
        int scoreJ = afficherNiveau(difficulty);
        printf("%d",scoreJ);
        itoa(scoreJ,buf);
        write(tubeEnv, buf, sizeof(buf));
        read(tubeRecv,buf,sizeof(buf));
        int adversaireScore=atoi(buf);
        if(score<adversaireScore){
            printf("L'adversaire a gagné \n\n");
        }else if(score>adversaireScore){
            printf("Vous avez gagné");
        }else
            printf("Egalité\n\n");

        close(tubeEnv);
        close(tubeRecv);
        break;*/
    default:
        break;
    }
    
    deleteRoom(code);
    
}
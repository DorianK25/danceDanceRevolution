#include "libs/lib.h"

int main(int argc, char *argv[]){

    int mode,difficulty;
    int tubeRecv;
    int tubeEnv;
    char code[11];
    char nomTube[100]="./";
    char idP[100];
    char buf[250];
    if(argc == 1){
        //création
        printf("Bonjour veuillez saisir votre Mode de jeu :\n\n");
        mode=getMode();
        difficulty=getDifficulty();
        
        

        //Creation des tubes

        if(mode == 2){
            getCode(code);
            writeRoom(code,getpid());
            printf("Votre code de salle d'attente est : %s\n\n",code);
            itoa(getpid(),idP);
            strcat(nomTube,idP);
            printf("%s",nomTube);
            mkfifo(idP, 0666);
            tubeRecv=open(nomTube, O_RDWR);//on ouvre le tube1
            read(tubeRecv,buf,sizeof(buf));
            tubeEnv=open(buf, O_RDWR);
            itoa(difficulty,buf);
            write(tubeEnv, buf, sizeof(buf));//synchro
            read(tubeRecv,buf,sizeof(buf));
        }
        
        
    int mode,difficulty; // on initialise des variables mode et difficulte correspondant au mode du jeu ainsi qu'à sa difficulte
    char code[11];// on initialise une variable code correspond au code de la salle de jeu
    if(argc == 1){
        //création
        printf("Bonjour veuillez saisir votre Mode de jeu :\n\n");
        mode=getMode();// on recupere le mode choisi
        difficulty=getDifficulty();//on recupere la difficulte choisie
        getCode(code);// on recupere le code de la salle
    }else if(argc == 2){
        mode=2;
        int id=readRoom(argv[1]);
        if(id==-1){
            printf("Salle non trouvée...\n\n");
            EXIT_FAILURE;
        }
        itoa(id,idP);
        strcat(nomTube,idP);
        strcpy(code,argv[1]);
        tubeEnv=open(idP, O_RDWR);
        itoa(getpid(),buf);
        strcpy(nomTube,"./");
        strcat(nomTube,buf);
        mkfifo(buf, 0666);
        tubeRecv=open(nomTube, O_RDWR);
        write(tubeEnv, buf, sizeof(buf));
        read(tubeRecv,buf,sizeof(buf));
        difficulty=atoi(buf);
        write(tubeEnv, buf, sizeof(buf));
    }else{
        printInfoMessage();
        return 0;
    }
    switch (mode)
    {
    // correspond au mode solo du jeu 
    case 1:
        printf("mode %d joueur, difficulté : %d\n",mode,difficulty);
        int score = afficherNiveau(difficulty);
        system("clear");
        printf("\t\t Votre score est de %d points\n\n",score);
        writeScore(score);
        topScore();
        break;
    // correspond au mode multijoueur(2 joueurs) du jeu 
    case 2:
        printf("mode %d joueur, difficulté : %d, code : %s\n",mode,difficulty,code);
        int scoreJ = afficherNiveau(difficulty);
        printf("Votre score est de : %d points \n\n",scoreJ);
        itoa(scoreJ,buf);
        write(tubeEnv, buf, sizeof(buf));
        read(tubeRecv,buf,sizeof(buf));
        int adversaireScore=atoi(buf);
        printf("Le score de l'adversaire est de : %d points \n\n",adversaireScore);
        if(scoreJ<adversaireScore){
            printf("L'adversaire a gagné \n\n");
        }else if(scoreJ>adversaireScore){
            printf("Vous avez gagné\n\n");
        }else
            printf("Egalité\n\n");
        close(tubeEnv);
        close(tubeRecv);
        break;
    default:
        break;
    }
    
    deleteRoom(code);
    
}
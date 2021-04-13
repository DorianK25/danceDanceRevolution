#include "libs/lib.h"

int main(int argc, char *argv[]){

    /* 
        INITIALISATION DES VARIABLES 
    */
    int mode,difficulty; // on initialise des variables mode et difficulte correspondant au mode du jeu ainsi qu'à sa difficulte
    int tubeReception;// on initialise une variable pour l'id du tube de recepetion
    int tubeEnvoi;// on initialise une variable pour l'id du tube d'envoi
    char code[11];// on initialise une variable code correspond au code de la salle de jeu
    char nomTube[100]="./";// on initialise une variable pour le nom des tubes
    char idProcessus[100];// on initialise une variable pour l'id du processus en chaine de caractere car getpid() renvoie un int
    char buf[250];// on initialise une variable pour le buffer
    
    /* 
        DETECTION SI CRÉATION D'UNE SALLE D'ATTENTE OU REJOINDRE UNE SALLE
    */
    if(argc == 1){
        /*
            CAS : CRÉATION
        */
        printf("Bonjour veuillez saisir votre Mode de jeu :\n\n");
        mode=getMode();// on recupere le mode choisi
        difficulty=getDifficulty();//on recupere la difficulte choisie
        
        /*
            CRÉATION DES TUBES SI MULTIJOUEURS (mode==2)
        */
        if(mode == 2){
            getCode(code);// on recupere le code de la salle
            writeRoom(code,getpid());// on écrit sur le fichier room.txt le code de la salle et le pid du processus
            printf("Votre code de salle d'attente est : %s\n\n",code);
            itoa(getpid(),idProcessus);// on transforme le pid en chaine de caractere
            strcat(nomTube,idProcessus);// on concatene le pid avec "./" afin de placer le tube nommé dans le répertoire courant
            mkfifo(idProcessus, 0666);// on crée le tube nommé
            tubeReception=open(nomTube, O_RDWR);//on ouvre le tube de reception 
            printf("Attente de la connexion du joueur adverse (./dance.exe <code de la salle>)");
            read(tubeReception,buf,sizeof(buf));// on lit le tube de reception (nous attendons la venue de l'autre joueur)
            tubeEnvoi=open(buf, O_RDWR);// on ouvre le tube d'envoi
            itoa(difficulty,buf);// on transforme la difficulte en chaine de caractere
            write(tubeEnvoi, buf, sizeof(buf));// on envoie la réponse de l'adversaire pour synchroniser
            read(tubeReception,buf,sizeof(buf));// on attend la réponse de l'adversaire pour synchroniser
        }
        
    }else if(argc == 2){
        mode=2;
        int id=readRoom(argv[1]);
        if(id==-1){
            printf("Salle non trouvée...\n\n");
            EXIT_FAILURE;
        }
        itoa(id,idProcessus);
        strcat(nomTube,idProcessus);
        strcpy(code,argv[1]);
        tubeEnvoi=open(idProcessus, O_RDWR);
        itoa(getpid(),buf);
        strcpy(nomTube,"./");
        strcat(nomTube,buf);
        mkfifo(buf, 0666);
        tubeReception=open(nomTube, O_RDWR);
        write(tubeEnvoi, buf, sizeof(buf));
        read(tubeReception,buf,sizeof(buf));
        difficulty=atoi(buf);
        write(tubeEnvoi, buf, sizeof(buf));
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
        write(tubeEnvoi, buf, sizeof(buf));
        read(tubeReception,buf,sizeof(buf));
        int adversaireScore=atoi(buf);
        printf("Le score de l'adversaire est de : %d points \n\n",adversaireScore);
        if(scoreJ<adversaireScore){
            printf("L'adversaire a gagné \n\n");
        }else if(scoreJ>adversaireScore){
            printf("Vous avez gagné\n\n");
        }else
            printf("Egalité\n\n");
        close(tubeEnvoi);
        snprintf(buf, sizeof(buf), "rm %d",getpid());
        printf("%s\n",buf);
        system(buf);
        close(tubeReception);
        break;
    default:
        break;
    }
    
    deleteRoom(code);
    
}
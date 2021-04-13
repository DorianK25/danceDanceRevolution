#include "librairies/lib_functions.h"

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
            write(tubeEnvoi, buf, sizeof(buf));// on envoie la difficulté a l'autre processus
            read(tubeReception,buf,sizeof(buf));// on attend la réponse de l'adversaire pour synchroniser
        }
        
    }else if(argc == 2){

        /*
            CAS : REJOINDRE
        */
        mode=2;// on precise que le mode est 2 joueurs 
        int id=readRoom(argv[1]);// on va lire le pid du processus lancé par l'adversaire
        if(id==-1){
            printf("Salle non trouvée...\n\n");
            EXIT_FAILURE;
        }

        /*
            CRÉATION DES TUBES
        */
        itoa(id,idProcessus);//on met le pid du processus de l'adverssaire en chaine de caractère
        strcat(nomTube,idProcessus);//on concatène pour place le tube nommé dans le repertoire courant
        strcpy(code,argv[1]);//on attribut le code à notre processus
        tubeEnvoi=open(idProcessus, O_RDWR);//ouverture du tube d'envoi
        itoa(getpid(),buf);//on met le pid de notre processus en chaine de caractère
        strcpy(nomTube,"./");//on attribut le nom du tube nommé à './' pour cibler le repertoire courant
        strcat(nomTube,buf);//on concatène pour donner un id unique a notre nom de tube
        mkfifo(buf, 0666);//on cree le tube nommé
        tubeReception=open(nomTube, O_RDWR);//on ouvre le tube d'envoi
        write(tubeEnvoi, buf, sizeof(buf));//on ecrit sur le tube d'envoie pour que le processus adverse reçoit le pid de notre processus
        read(tubeReception,buf,sizeof(buf));//on reçoit la difficulté par l'autre processus 
        difficulty=atoi(buf);//on le transforme en entier
        write(tubeEnvoi, buf, sizeof(buf));//on ecrit pour dire que l'on est prêt pour synchroniser les 2 processus
    }else{
        /*
            CAS : ERREURS
        */
        printInfoMessage();//on indique la norme pour lancer le programme
        return 0;
    }
    switch (mode)
    {
    /*
        CAS : 1 JOUEUR
    */ 
    case 1:
        printf("mode %d joueur, difficulté : %d\n",mode,difficulty);
        int score = afficherNiveau(difficulty);//on recupere le score du joueur
        system("clear");//on clear notre temrniale
        printf("\t\t Votre score est de %d points\n\n",score);//on ecrit le score
        writeScore(score);//on ecrit le score dans le fichier des scores
        topScore();//on affiche le top des Scores
        break;

    /*
        CAS : 2 JOUEURS
    */
    case 2:
        printf("mode %d joueur, difficulté : %d, code : %s\n",mode,difficulty,code);
        int scoreJoueur = afficherNiveau(difficulty);// recupère le scroe du joueur
        printf("Votre score est de : %d points \n\n",scoreJoueur);
        itoa(scoreJoueur,buf);// transforme le score en chaine de caractères
        write(tubeEnvoi, buf, sizeof(buf));// envoie le score à l'adversaire
        printf("Attente du score de l'adversaire\n\n");
        read(tubeReception,buf,sizeof(buf));// recupère le score de l'adversaire
        int adversaireScore=atoi(buf);//on change la chaine de caractère en entier
        printf("Le score de l'adversaire est de : %d points \n\n",adversaireScore);
        /*
            COMPARAISON DES SCORES
        */
        if(scoreJoueur<adversaireScore){
            printf("L'adversaire a gagné \n\n");
        }else if(scoreJoueur>adversaireScore){
            printf("Vous avez gagné\n\n");
        }else
            printf("Egalité\n\n");


        close(tubeEnvoi);// ferme le 1er tube
        snprintf(buf, sizeof(buf), "rm %d",getpid());//creer la commande pour supprimer le fichier du tube nommé
        system(buf);//execute la commande précédente
        close(tubeReception);// ferme le 2nd tube 

        break;
    default:
        break;
    }
    
    deleteRoom(code);//on supprime 
    
}
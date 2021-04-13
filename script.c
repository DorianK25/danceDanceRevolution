#include "libs/lib.h"

int main(int argc, char *argv[]){

    int mode,difficulty; // on initialise des variables mode et difficulte correspondant au mode du jeu ainsi qu'à sa difficulte
    char code[11];// on initialise une variable code correspond au code de la salle de jeu
    if(argc == 1){
        //création
        printf("Bonjour veuillez saisir votre Mode de jeu :\n\n");
        mode=getMode();// on recupere le mode choisi
        difficulty=getDifficulty();//on recupere la difficulte choisie
        getCode(code);// on recupere le code de la salle
    }else if(argc == 2){
        strcpy(code,argv[1]);
        mode=2;
    }else{
        printInfoMessage();
        return 0;
    }

    
    switch (mode)
    {
    // correspond au mode solo du jeu 
    case 1:
        printf("mode %d joueur, difficulté : %d\n",mode,difficulty);
        afficherNiveau(difficulty);
        break;
    // correspond au mode multijoueur(2 joueurs) du jeu 
    case 2:
        printf("mode %d joueur, difficulté : %d, code : %s\n",mode,difficulty,code);
        break;
    default:
        break;
    }
}
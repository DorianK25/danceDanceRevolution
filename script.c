#include "libs/lib.h"

int main(int argc, char *argv[]){

    int mode,difficulty;
    char code[11];
    if(argc == 1){
        //création
        printf("Bonjour veuillez saisir votre Mode de jeu :\n\n");
        mode=getMode();
        difficulty=getDifficulty();
        getCode(code);
    }else if(argc == 2){
        strcpy(code,argv[1]);
        mode=2;
    }else{
        printInfoMessage();
        return 0;
    }

    
    switch (mode)
    {
    case 1:
        printf("mode %d joueur, difficulté : %d\n",mode,difficulty);
        afficherNiveau(difficulty);
        break;
    case 2:
        printf("mode %d joueur, difficulté : %d, code : %s\n",mode,difficulty,code);
        break;
    default:
        break;
    }
}
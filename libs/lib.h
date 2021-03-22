#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 256

typedef struct 
{
    char pseudo[TAILLE_MAX];
    int score;
}score;
typedef struct{
    score top[10];
}highScore; 


int writeScore(int score);
highScore triScore(char tab[10][TAILLE_MAX+20]);
highScore topScore();


// ecrire pseudo et score user dans un scores.txt
// afficher top des scores










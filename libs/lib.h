#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TAILLE_MAX 256

typedef struct 
{
    char* pseudo;
    int score;
}score;
typedef struct{
    score top[10];
}highScore; 


int writeScore(int score);
void triScore(int nb,char tab[nb][TAILLE_MAX+20]);
void topScore();
void afficherScore(highScore);
void afficherNiveau(int difficulte);
void decalerNiveau(char niveau[1024]);











#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#define TAILLE_MAX 256

int getMode();

int getDifficulty();

void getCode(char*);

void printInfoMessage();


typedef struct 
{
    char* pseudo;
    int score;
}score;
typedef struct{
    score top[10];
}highScore; 

int createSegment();
int editSegment(int,int,struct shmid_ds *);
int detachSegment(char * );
char * attachSegment(int);
int deleteSegment(int,struct shmid_ds *);
int writeScore(int score);
void triScore(int nb,char tab[nb][TAILLE_MAX+20]);
void topScore();
void afficherScore(highScore);
void afficherNiveau(int difficulte);
void decalerNiveau(char niveau[1024]);
char getSaisie();
 void itoa(int n, char s[]);
 void reverse(char s[]);











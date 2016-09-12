#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define STRSIZE 10
#define POPSIZE 2048
#define MUTRATE128 16

char objective[STRSIZE] = {'H','e','l','l','o','W','o','r','l','d'};


class Dude{
public:
    Dude(){
        for(int i=0; i<STRSIZE; i++){
            value[i]=rand();
        }
        calculateFitness();
    }
    Dude(const Dude* mother, const Dude* father){
        for(int i=0; i<STRSIZE; i++){
            int temp = rand()%128;
            if(temp<MUTRATE128){
                value[i]=rand();
            } else {
                temp = rand()%2;
                if(temp){
                    value[i]=mother->value[i];
                } else {
                    value[i]=father->value[i];
                }
            }
        }
        calculateFitness();
    }
    char value[STRSIZE];
    int fitness;
private:
    void calculateFitness(){
        fitness = 0;
        for(int i=0; i<STRSIZE; i++){
            fitness += abs(objective[i]-value[i]);
        }
    }
};

int compareDudes(const void * a, const void * b){
  if ( ((Dude*)a)->fitness <  ((Dude*)b)->fitness ) return -1;
  if ( ((Dude*)a)->fitness == ((Dude*)b)->fitness ) return 0;
  if ( ((Dude*)a)->fitness >  ((Dude*)b)->fitness ) return 1;
}

Dude dudes[POPSIZE];

int main(){
    srand(time(NULL));
    for(int i=0; i<POPSIZE; i++){
        dudes[i]=Dude();
    }
    int counter=0;
    int averageFit;
    while(true){
        counter++;
        qsort(dudes,POPSIZE,sizeof(Dude),compareDudes);
        averageFit=0;
        for(int i=0; i<POPSIZE; i++){
            averageFit+=dudes[i].fitness;
        }
        averageFit/=POPSIZE;

        printf("best:  \"");
        for(int i=0; i<STRSIZE; i++){
            if(dudes[0].value[i]<33)
                printf(" ");
            else
                printf("%c", dudes[0].value[i]);
        }
        printf("\"  fit: %d", dudes[0].fitness);
        printf("\tavgFit: %d", averageFit);
        printf("\n");

        if(dudes[0].fitness==0)
            break;

        for(int i=POPSIZE/2; i<POPSIZE-1; i++){
            dudes[i]=Dude(&(dudes[i-POPSIZE/2]),&(dudes[i+1-POPSIZE/2]));
        }
        dudes[POPSIZE-1]=Dude(&(dudes[POPSIZE/2-1]),&(dudes[0]));
    }
    printf("\n%f mutation rate, %d individuals, 1/2 exchanges per loop\n%d loops, %d fecundations, a lot of incest\nDeveloped by MyK_00L\n\n", (float)MUTRATE128/(float)128, POPSIZE, counter, counter*(POPSIZE/2));
    printf("press enter to exit...");
    getchar();
    return 0;
}

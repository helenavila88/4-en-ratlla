#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funcions.h"


void SetColor(int ForgC){
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
      }
}

void inicialitzacio(Node *arrel){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            arrel->tauler[i][j]=0;
        }
    }
}

void mostraTauler(Node *arrel) {
    printf("\n");
    for (int i=0; i<N; i++){
        printf("----------------------------------------\n");
        for (int j=0; j<N; j++){
            if (arrel->tauler[i][j]==0){
                printf("|   |");
            }
            else if (arrel->tauler[i][j] == 1){ //jugador
                printf("| ");
                SetColor(5);
                printf("X");
                SetColor(15);
                printf(" |");
            }
            else{ //ordinador
                printf("| ");
                SetColor(3);
                printf("O");
                SetColor(15);
                printf(" |");
            }
        }
        printf("\n");
        if (i==N-1){
            printf("----------------------------------------\n");
            printf("----------------------------------------\n");
            for (int j=0; j<N; j++){
            printf("| %d |", j+1);
            }
            printf("\n");
        }

    }
}

void PosarFitxa(Node *arrel, int columna, int torn){
    if ((arrel->comp)<=N-1){
        if (arrel->tauler[N-1-(arrel->comp)][columna]==0){
            if (torn % 2== 0) {
                arrel->tauler[N-1- (arrel->comp)][columna]=1; //Jugador
            }
            else {
                arrel->tauler[N-1- (arrel->comp)][columna]=2; //Ordinador
            }
            (arrel->comp)=0;
        }
        else{
            arrel->comp = (arrel->comp)+1; //veiem si una col te la posicio ocupada (començant per abaix)
            PosarFitxa(arrel, columna, torn);
        }
    }
    else {
        return;
    }
}

int main() {
    int mode;
    printf("::::::::::::::::::::::::::::::::\n");
    printf("  BENVINGUDA AL 4 EN RATLLA!!!\n");
    printf("::::::::::::::::::::::::::::::::\n");
    printf("----ESCULL EL MODE DE JOC----\n");
    printf("1) JUGADOR vs JUGADOR \n");
    printf("2) JUGADOR vs ORDINADOR\n");
    printf("(qualsevol altre numero --> EXIT)\n");

    scanf("%d", &mode);

    if (mode == 1){
        jugador_jugador();
    }
    else if (mode == 2){
        jugador_ordinador();
    }
    else {
        printf("EXIT");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funcions.h"


int ult_fila_compl(Node *arrel){
    int compl = 0;
    for (int j=0; j<N; j++){
        if (arrel->tauler[0][j]!=0){
            compl=compl+1;
        }
    }
    if (compl == 8){
        return 1;
    }
    else{
        return 0;
    }
}

int horitzontal(Node *arrel, int jugador){
        for(int i=N-1; i>-1; i--){ //files
            for(int j=0; j<5; j++){ //columnes
                if(arrel->tauler[i][j] == jugador){
                    if (arrel->tauler[i][j]==arrel->tauler[i][j+1] && arrel->tauler[i][j]==arrel->tauler[i][j+2] && arrel->tauler[i][j]==arrel->tauler[i][j+3]){
                    return 1; // quan s'ha fet 4 en ratlla, retorna un 1
                    }
                }

                }
            }
            return 0;
}

int vertical(Node *arrel, int jugador){
    for (int j=0; j<N; j++){ //col
        for (int i=N-1; i>2; i--){
            if(arrel->tauler[i][j] == jugador){
                if (arrel->tauler[i][j]==arrel->tauler[i-1][j] && arrel->tauler[i][j]==arrel->tauler[i-2][j] && arrel->tauler[i][j]==arrel->tauler[i-3][j]) {
                       return 1;
                }
            }
        }
    }
    return 0;

}

int diagonalasc(Node *arrel, int jugador){
    for (int i=N-1; i>2; i--){
            for (int j=0; j<5; j++){
                if(arrel->tauler[i][j] == jugador){
                    if(arrel->tauler[i][j]==arrel->tauler[i-1][j+1] && arrel->tauler[i][j]==arrel->tauler[i-2][j+2] && arrel->tauler[i][j] == arrel->tauler[i-3][j+3]){
                        return 1;
                    }
                }
            }
        }
    return 0;
}

int diagonaldesc(Node *arrel, int jugador){
    for (int i=0; i<5; i++){
            for (int j=0; j<5; j++){
                if(arrel->tauler[i][j] == jugador){
                    if(arrel->tauler[i][j]==arrel->tauler[i+1][j+1] && arrel->tauler[i][j]==arrel->tauler[i+2][j+2] && arrel->tauler[i][j] == arrel->tauler[i+3][j+3]){
                        return 1;
                    }
                }
            }
        }
    return 0;
}

int guanyar(Node *arrel, int jugador){
    if (horitzontal(arrel, jugador)==1 || vertical(arrel, jugador)==1 || diagonalasc(arrel, jugador)==1 || diagonaldesc(arrel, jugador)==1){
        if (jugador==1){ //jugador
             return 1;
        }
        else{
            return 2; //ordinador
        }

    }
    else{
        return 0;
    }
}

int tirada_ordinador(Node *arrel){
    arrel->n_fills = cols_disp(arrel);
    crearArbre(arrel, 0);

    miniMax(arrel,0);
    //recorreArbreRec(arrel,0);

    int col = escollir_columna_ordinador(arrel);
    return col;
}

int tirada_jugador(Node *arrel){
    int col;
        printf("A quina columna vols tirar? (1-8)\n");
        scanf("%d", &col);
        while(col>8 || col<0 || arrel->tauler[0][col-1]!=0){
            printf("torna a escollir columna (out of range)\n");
            printf("A quina columna vols tirar? (1-8)\n");
            scanf("%d", &col);
        }
        col=col-1;
    return col;
}

void jugador_jugador(){
    Node *arrel=malloc(sizeof(Node)); //arrel es un apuntador
    inicialitzacio(arrel);
    printf("Has escollit: JUGADOR VS JUGADOR\n");
    int torn = 0;
    int col = 0;
    int jugador = 1;
    char nomJ1[15];
    char nomJ2[15];
    printf("JUGADOR 1 INTRODUEIX EL TEU NOM: \n");
    scanf(" %14s", &nomJ1);
    printf("JUGADOR 2 INTRODUEIX EL TEU NOM: \n");
    scanf(" %14s", &nomJ2);
    mostraTauler(arrel);
    while(ult_fila_compl(arrel)==0 && guanyar(arrel, jugador)==0){
        if (torn % 2 == 0){
            jugador = 1;

            printf("%s, es el teu torn (X)\n", nomJ1);
            col = tirada_jugador(arrel);
        }
        else{
            jugador = 2;

            printf("%s, es el teu torn (O)\n", nomJ2);
            col = tirada_jugador(arrel);
        }
        PosarFitxa(arrel, col, torn);
        mostraTauler(arrel);
        torn = torn + 1;

    }
    printf("S'ha acabat el joc\n");
    if (ult_fila_compl(arrel)==1 && guanyar(arrel, jugador)==0){
        printf("NO HA GUANYAT NINGU\n");
    }
    else{
        if (torn % 2 == 1 ){ //quan guanyar retorna 1
            printf("FELICITATS %s, HAS GUANYAT!", nomJ1);
        }
        else {
            printf("FELICITATS %s, HAS GUANYAT!", nomJ2);
        }
    }
}


void jugador_ordinador(){
    Node *arrel=malloc(sizeof(Node)); //arrel es un apuntador
    arrel->n_fills=N;
    arrel->fills=malloc(arrel->n_fills * sizeof(Node *));
    arrel->valor=0;
    //inicialitzacio
    inicialitzacio(arrel);
    printf("Has escollit: JUGADOR VS ORDINADOR\n");

    int torn = 0;
    int col = 0;
    int jugador = 1;
    char nom[15];
    printf("INTRODUEIX EL TEU NOM: \n");
    scanf(" %14s", &nom);
    int niv;
    printf("----ESCULL LA DIFICULTAT---- \n");
    printf("1) Easy\n");
    printf("2) Medium\n");
    printf("3) Hard\n");
    scanf("%d", &niv);
    if (niv == 1){
        LEVEL = 3;
    }
    else if (niv == 2){
        LEVEL = 4;
    }
    else if (niv == 3){
        LEVEL = 5;
    }

    mostraTauler(arrel);
    while(ult_fila_compl(arrel)==0 && guanyar(arrel, jugador)==0){
        if (torn % 2 == 0){
            jugador = 1;

            printf("%s, es el teu torn\n", nom);
            col = tirada_jugador(arrel);
        }
        else{
            jugador=2;
            col = tirada_ordinador(arrel);
        }
        PosarFitxa(arrel, col, torn);
        mostraTauler(arrel);
        torn = torn + 1;

    }
    printf("S'ha acabat el joc\n");
    //torn hauria de ser 0 pero hem sumat 1
    if (ult_fila_compl(arrel)==1 && guanyar(arrel, jugador)==0){
        printf("NO HA GUANYAT NINGU\n");
    }
    else{
        if (torn % 2 == 1 ){ //quan guanyar retorna 1
        printf("FELICITATS %s, HAS GUANYAT!", nom);;
        }
        else {
            printf("HAS PERDUT, HA GUANYAT L'ORDINADOR");
        }
    }
    //recorreArbreRec(arrel,0);
}




#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funcions.h"

void mostraNode(Node *node, int nivell){
    for(int i=1;i<=nivell;i++)
        printf("\t");
    printf("- %d (%d)\n", node->valor, node->n_fills);
}

void recorreArbreRec(Node *arrel, int nivell){
    mostraNode(arrel,nivell);
    if (arrel->n_fills>0){
        for (int i=0; i<arrel->n_fills;i++)
            recorreArbreRec(arrel->fills[i], nivell+1);
    }
}

void miniMax(Node *arrel, int nivell){ //primer entra nivell 0
    int aux = arrel->valor;
    for (int i=0; i<arrel->n_fills; i++){
        miniMax(arrel->fills[i], nivell+1);
    }
    if (arrel->n_fills != 0){
        int aux2;
        if (nivell % 2){ //jugador
            aux = 100;
            for (int i=0; i< arrel->n_fills; i++){
                aux2 = arrel->fills[i]->valor;
                if (aux2<aux){
                    aux=aux2;
                }
            }
        }
        else{ //ordinador
            aux = -100;
            for (int i=0; i<arrel->n_fills; i++){
                aux2= arrel->fills[i]->valor;
                if (aux2>aux){
                    aux=aux2;
                }
            }
        }
    }
    arrel->valor=aux;
}

void copiarTauler(Node *pare, Node *p){
    for (int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            p->tauler[i][j] = pare->tauler[i][j];
        }
    }
}

void puntuacio(Node *node, int nivell){
    int aux = 0;
    for (int i=1; i<3; i++){
        aux=guanyar(node, i);
        if (aux != 0 ){
            break;
        }
    }
        if (aux==1){
            //si guanya el jugador
                node->valor = -100;
        }
        else if (aux==2){ //si guanya ordinador
                node->valor = 100;
            }

        else{ //si no guanya ningu

            node->valor = rand()%50;

        }
}

int col_plena(Node *node, int columna){
    if (node->tauler[0][columna]==0){
        return 0; //no esta plena
        }
    return 1;
}

int col_fill(Node *pare, int numDeFill){  //funcio on tirara el fill
    int col_disp=0;
    for (int i=0; i<N; i++){
        if(col_plena(pare, i)==0){
                if(numDeFill==col_disp){
                    return i;
                }
            col_disp++;
        }

    }
    return -1;
}

Node *crearNode(Node *pare, int numDecol, int nivell){
    Node *p=malloc(sizeof(Node));
    copiarTauler(pare, p);

    puntuacio(p, nivell);
    PosarFitxa(p, numDecol, nivell+1);

    if(nivell<LEVEL){
            p->n_fills = cols_disp(p);
            p->fills=malloc(p->n_fills * sizeof(Node *));


    }else{
        p->n_fills=0;
    }

    return p;
}

void crearNivell(Node *pare, int nivell){
    int col;
    for (int i=0; i<pare->n_fills;i++){
        col=col_fill(pare, i);
        pare -> fills[i]=crearNode(pare,col,nivell);
    }
}

void crearArbre(Node *arrel,int nivell){
    crearNivell(arrel,nivell);

    for (int i=0; i<arrel->n_fills;i++)
        crearArbre(arrel -> fills[i],nivell+1);
}

int cols_disp(Node *arrel){
    int disp=0;
    for (int i=0; i<N; i++){
        if (arrel->tauler[0][i]==0){
            disp=disp+1;
        }
    }
    return disp;
}

void esborrar_arbre(Node *pare){
    for (int i=0; i<pare->n_fills; i++){
        esborrar_arbre(pare->fills[i]);
    }
    free(pare->fills);
}

int escollir_columna_ordinador(Node *node){
    for (int i=0; i< node->n_fills; i++){
        if (node->valor == node->fills[i]->valor){
            return col_fill(node, i);
        }
    }
}

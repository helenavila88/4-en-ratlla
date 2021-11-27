#define N 8
int LEVEL;

typedef struct node{
    char tauler [N][N];
    struct node* *fills; // fills es un camp, es un apuntador que te node
    int n_fills;
    int valor;
    int comp; //fila completa
} Node;

void SetColor(int ForgC);
void inicialitzacio(Node *arrel);
void mostraTauler(Node *arrel);
void PosarFitxa(Node *arrel, int columna, int torn);
int ult_fila_compl(Node *arrel);
int horitzontal(Node *arrel, int jugador);
int vertical(Node *arrel, int jugador);
int diagonalasc(Node *arrel, int jugador);
int diagonaldesc(Node *arrel, int jugador);
int guanyar(Node *arrel, int jugador);
int tirada_ordinador(Node *arrel);
int tirada_jugador(Node *arrel);
void jugador_ordinador();
void jugador_jugador();
void mostraNode(Node *node, int nivell);
void recorreArbreRec(Node *arrel, int nivell);
void miniMax(Node *arrel, int nivell);
void copiarTauler(Node *pare, Node *p);
void puntuacio(Node *node, int nivell);
int col_plena(Node *node, int columna);
int col_fill(Node *pare, int numDeFill);
Node *crearNode(Node *pare, int numDecol, int nivell);
void crearNivell(Node *pare, int nivell);
void crearArbre(Node *arrel,int nivell);
int cols_disp(Node *arrel);
void esborrar_arbre(Node *pare);
int escollir_columna_ordinador(Node *node);


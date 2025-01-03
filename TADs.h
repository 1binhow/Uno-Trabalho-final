#ifndef _TADS_
#define _TADS_


#define TAM_NOME 40
#define TAM_EMAIL 25

// /////////////////////////////////////////////

typedef enum {
    AZUL = 0,
    VERDE,
    VERMELHO,
    AMARELO,
    PRETA
} CorCarta;

typedef struct {
    int num;
    CorCarta cor;
} Info;

typedef struct NodoLEnc2{
    Info info;
    Carta* prox;
    Carta* ant;
} Carta;

typedef struct ListaEnc2{
    int n_cartas;
    Carta* prim;
} Mao;

////////////////////////////////////////////////////////

typedef struct nodoLEnc{
    int pontos;
    char nome[20];
    Mao* mao;
    Jogador *prox;
    Jogador *ant;
} Jogador;

typedef struct{
    Jogador *prim;
}  ListaJogadores;

//////////////////////////////////////////////////////////

typedef struct pilhaEnc{
    CartaPilha *topo;
} PilhaCartas;

typedef struct {
    Info info;
    CartaPilha* prox;
} CartaPilha;


#endif

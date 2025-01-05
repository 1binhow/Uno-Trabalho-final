#ifndef _TADS_
#define _TADS_

#define TAM_NOME 40
#define TAM_EMAIL 25

typedef enum {
    AMARELO = 0,
    VERDE,
    VERMELHO,
    AZUL,
    PRETA,
} CorCarta;

typedef struct {
    int num;
    CorCarta cor;
} Info;

typedef struct Carta {
    Info info;
    struct Carta* prox;
    struct Carta* ant;
} Carta;

typedef struct {
    int n_cartas;
    Carta* prim;
} Mao;

typedef struct Jogador {
    int pontos;
    char nome[TAM_NOME];
    Mao* mao;
    struct Jogador* prox;
    struct Jogador* ant;
} Jogador;

typedef struct {
    Jogador* prim;
} ListaJogadores;

typedef struct CartaPilha {
    Info info;
    struct CartaPilha* prox;
} CartaPilha;

typedef struct {
    CartaPilha* topo;
} PilhaCartas;

Mao* criaMao();
int insereInicioMao(Mao* mao, Info info);
Info removeCartaMao(Mao* mao, Carta* carta);

PilhaCartas* criaPilhaCartas();
void empilhaPilhaCartas(PilhaCartas* pilha, Info info);
Info desempilhaPilhaCartas(PilhaCartas* pilha);

#endif

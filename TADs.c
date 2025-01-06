#include "TADs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que cria uma mão
Mao* criaMao() {
    Mao* mao = (Mao*)malloc(sizeof(Mao));
    if (mao != NULL)
        mao->prim = NULL;  // Representação de lista vazia
        mao->n_cartas = 0;
    return mao;
}

// Função que insere uma carta no início da mão
int insereInicioMao(Mao* mao, Info info) {
    Carta* novaCarta = (Carta*)malloc(sizeof(Carta));
    if (novaCarta == NULL)
        return 0;  // Falha ao alocar memória
    novaCarta->info = info;
    novaCarta->prox = mao->prim;
    if (mao->prim != NULL)
        mao->prim->ant = novaCarta;
    mao->prim = novaCarta;
    mao->n_cartas++;
    return 1;  // Sucesso
}

// Função que remove uma carta da mão
Info removeCartaMao(Mao* mao, Carta* carta) {
    Info info;
    if (carta == NULL || mao->prim == NULL)
        return info;

    info = carta->info;
    if (carta->ant != NULL)
        carta->ant->prox = carta->prox;
    if (carta->prox != NULL)
        carta->prox->ant = carta->ant;
    if (mao->prim == carta)
        mao->prim = carta->prox;

    free(carta);
    mao->n_cartas--;
    return info;
}

// Função que cria uma pilha de cartas
PilhaCartas* criaPilhaCartas() {
    PilhaCartas* pilha = (PilhaCartas*)malloc(sizeof(PilhaCartas));
    pilha->topo = NULL;
    return pilha;
}

// Função que empilha uma carta na pilha
void empilhaPilhaCartas(PilhaCartas* pilha, Info info) {
    CartaPilha* novaCarta = (CartaPilha*)malloc(sizeof(CartaPilha));
    novaCarta->info = info;
    novaCarta->prox = pilha->topo;
    pilha->topo = novaCarta;
}

// Função que desempilha uma carta da pilha
Info desempilhaPilhaCartas(PilhaCartas* pilha) {
    Info info = {0};  // Retorno de valor padrão
    if (pilha->topo != NULL) {
        CartaPilha* carta = pilha->topo;
        info = carta->info;
        pilha->topo = carta->prox;
        free(carta);
    }
    return info;
}

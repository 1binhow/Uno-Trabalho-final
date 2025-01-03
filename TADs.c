#include "TADs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fun��o que cria uma m�o
Mao* criaMao() {
    Mao* mao = (Mao*)malloc(sizeof(Mao));
    if (mao != NULL)
        mao->prim = NULL;  // Representa��o de lista vazia
    return mao;
}

// Fun��o que insere uma carta no in�cio da m�o
int insereInicioMao(Mao* mao, Info info) {
    Carta* novaCarta = (Carta*)malloc(sizeof(Carta));
    if (novaCarta == NULL)
        return 0;  // Falha ao alocar mem�ria
    novaCarta->info = info;
    novaCarta->prox = mao->prim;
    if (mao->prim != NULL)
        mao->prim->ant = novaCarta;
    mao->prim = novaCarta;
    mao->n_cartas++;
    return 1;  // Sucesso
}

// Fun��o que remove uma carta da m�o
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

// Fun��o que cria uma pilha de cartas
PilhaCartas* criaPilhaCartas() {
    PilhaCartas* pilha = (PilhaCartas*)malloc(sizeof(PilhaCartas));
    pilha->topo = NULL;
    return pilha;
}

// Fun��o que empilha uma carta na pilha
void empilhaPilhaCartas(PilhaCartas* pilha, Info info) {
    CartaPilha* novaCarta = (CartaPilha*)malloc(sizeof(CartaPilha));
    novaCarta->info = info;
    novaCarta->prox = pilha->topo;
    pilha->topo = novaCarta;
}

// Fun��o que desempilha uma carta da pilha
Info desempilhaPilhaCartas(PilhaCartas* pilha) {
    Info info = {0};  // Retorno de valor padr�o
    if (pilha->topo != NULL) {
        CartaPilha* carta = pilha->topo;
        info = carta->info;
        pilha->topo = carta->prox;
        free(carta);
    }
    return info;
}

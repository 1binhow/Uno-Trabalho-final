#include "TADs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao que cria um jogador
Jogador* criaJogador(int npc, Mao* mao){
    Jogador* novo = (Jogador*)malloc(sizeof(Jogador));
    if (novo == NULL) {
        return NULL;
    }

    novo->ant = NULL;
    novo->prox = NULL;
    novo->mao = mao;
    novo->npc = npc;
    novo->pontos = 0;

    return novo;
}

// Funcao que cria uma lista de jogadores
ListaJogadores* criaListaJogadores(){
    ListaJogadores* lista = (ListaJogadores*)malloc(sizeof(ListaJogadores));

    return lista;
}

// Funcao que insere um jogador na lista de jogadores
int insereInicioListaCircEnc(ListaJogadores *lista, Jogador *novo){
    Jogador *aux;
    if (novo == NULL)
        return 0;
    if (lista->prim == NULL){
        lista->prim = novo;
        novo->ant = lista->prim;
        novo->prox = lista->prim;
    }else{
        aux = lista->prim;
        while(aux->prox != lista->prim){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
        novo->prox = lista->prim;
        lista->prim->ant = novo;
        lista->prim = novo;
    }
    return 1;
}

// Funcao que remove um jogador da lista de jogadores
void removeJogador (ListaJogadores* lista, Jogador* jogador){
    (jogador->ant)->prox = jogador->prox;
    (jogador->prox)->ant = jogador->ant;
    free(jogador);
}

// Funcao que checa se a lista de jogadores tem so um jogador
int ultimoJogador(ListaJogadores* lista) {
    if (lista == NULL || lista->prim == NULL) {
        // Lista vazia ou não inicializada
        return 0;
    }
    return ((lista->prim)->prox == lista->prim);
}



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

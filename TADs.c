#include "TADs.h"
#include <stdio.h>
#include <stdlib.h>

/* //////////////////////////////////////////////////////
FUNCOES RELACIONADAS COM O MANUSEIO DA LISTA DE JOGADORES
////////////////////////////////////////////////////// */

// Funcao que cria uma lista de jogadores


// Funcao que insere um jogador na lista de jogadores
int insereInicioListaCircEnc(ListaJogadores *lista, Jogador *novo){
    Jogador *aux;
    if (novo == NULL)
        return 0;
    if (lista->prim == NULL){
        lista->prim = novo;
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
char removeJogador (ListaJogadores* lista, Jogador* jogador){
    char nome[20];
    strcpy(jogador->nome, nome);
    (jogador->ant)->prox = jogador->prox;
    (jogador->prox)->ant = jogador->ant;
    free(jogador);

    return nome;
}

// Funcao que checa se a lista de jogadores tem so um jogador


/* ////////////////////////////////////////////////////////////////
FUNCOES RELACIONADAS COM O MANUSEIO DAS CARTAS DA MAO DE UM JOGADOR
//////////////////////////////////////////////////////////////// */

// Funcao que cria uma mao
Mao* criaMao(){
    Mao *mao = (Mao*)malloc(sizeof(Mao));
    if (mao!= NULL) // Idealmente, sempre checar!
        mao->prim = NULL; // Representacao de lista vazia
    return mao;
}

// Funcao que insere uma nova carta na mao do jogador
int insereInicioMao(Mao *mao, Info info){
    Carta *novo = (Carta*)malloc(sizeof(Carta));
    if (novo == NULL) {
        return 0;
    }
    novo->info = info;
    novo->ant = NULL;
    novo->prox = mao->prim;
    if (mao->prim != NULL){
        (mao->prim)->ant = novo;
    }
    mao->prim = novo;
    return 1;
}

// Funcao que remove um carta da mao do jogador (retorna a informacao da carta)
Info removeCartaMao(Mao* mao, Carta* carta){
    Carta* aux = carta;
    if (carta->ant == NULL){
        mao->prim = carta->prox;
        (carta->prox)->ant = NULL;
        free(carta);
    }
    if (carta->prox == NULL){
        (carta->ant)->prox == NULL;
        free(carta);
    }
    else {
        (carta->ant)->prox = carta->prox;
        (carta->prox)->ant = carta->ant;
    }
}


/* ////////////////////////////////////////////////////////////////
FUNCOES RELACIONADAS COM O MANUSEIO DA PILHA DA MESA E DO BARALHO
//////////////////////////////////////////////////////////////// */

// Funcao que cria uma pilha de cartas
PilhaCartas* criaPilhaCartas(){
    PilhaCartas *pilha = (PilhaCartas*)malloc(sizeof(PilhaCartas));
    if (pilha != NULL)
        pilha->topo = NULL;
    return pilha;
}

// Funcao que adiciona um carta no baralho/pilha de cartas da mesa
void empilhaPilhaCartas(PilhaCartas *pilha, Info info){
    CartaPilha *nova = (CartaPilha*)malloc(sizeof(CartaPilha));
    if (nova != NULL){
        nova->info = info;
        nova->prox = pilha->topo;
        pilha->topo = nova;
    }
}

// Funcao que remove uma carta do baralho
Info desempilhaPilhaCartas(PilhaCartas* pilha){
    CartaPilha *aux = pilha->topo;
    /* Aqui assumimos que desempilha eh
    chamada apenas se a pilha nao eh vazia */
    Info info = aux->info;
    pilha->topo = aux->prox;
    free(aux);
    return info;
}

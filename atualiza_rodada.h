#ifndef _UP_RODADA_
#define _UP_RODADA_

#include "TADs.h"


void atualizaRodada(PilhaCartas* pilha, PilhaCartas* baralho, Jogador* jogador);
void compraCarta(CartasPilha* baralho, Mao* mao, int n);
void inputsJogador(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho);
void jogadaNPC(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho, int* cartaJogada, int* pulaVez);
int jogadaValida(Carta* carta, PilhaCartas* pilha);

#endif

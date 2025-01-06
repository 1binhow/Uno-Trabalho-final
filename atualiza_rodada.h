#ifndef _UP_RODADA_
#define _UP_RODADA_

#include "TADs.h"


void compraCarta(PilhaCartas* baralho, Mao* mao, int n);
void inputsJogador(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho, int* cartaJogada, int* pulaVez);
int verificarCliqueCarta(Vector2 mousePos, Vector2 posicaoCarta);
void jogadaNPC(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho, int* cartaJogada, int* pulaVez);
int jogadaValida(Carta* carta, PilhaCartas* pilha);
void alteraCor(CartaPilha* carta);
void atualizaRodada(PilhaCartas* pilha, PilhaCartas* baralho, Jogador** jogador, ListaJogadores* ls_jogadores, int* inversao, int* cartaJogada, int* winner, int* uno);

#endif


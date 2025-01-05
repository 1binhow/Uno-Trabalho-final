#ifndef JOGO_H
#define JOGO_H

#include "raylib.h"
#include "cartas.h"
#include "TADs.h"

// Fun��o para verificar se a carta foi clicada
int verificarCliqueCarta(Vector2 mousePos, Vector2 posicaoCarta);

// Fun��o para obter o nome da cor da carta
const char* obterNomeCor(CorCarta cor);

// Fun��o para verificar se a carta � v�lida para jogar
int cartaValida(Info carta, Info topoDescarte);

// Fun��o para realizar a jogada da m�quina
void jogadaMaquina(Jogador* maquina, PilhaCartas* descarte, CartaPilha baralho[], int* topoBaralho);

// Fun��o para gerenciar o jogo com v�rias m�quinas
void gerenciarJogo(Jogador* jogador, Jogador* maquina1, Jogador* maquina2, PilhaCartas* descarte, CartaPilha baralho[], int* topoBaralho, Texture2D cartasTextura);

#endif

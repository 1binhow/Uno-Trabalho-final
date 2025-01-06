#include "TADs.h"
#include "stdio.h"
#include "raylib.h"
#include "desenho.h"

void compraCarta(PilhaCartas* baralho, Mao* mao, int n);
void inputsJogador(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho, int* cartaJogada, int* pulaVez);
int verificarCliqueCarta(Vector2 mousePos, Vector2 posicaoCarta);
void jogadaNPC(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho, int* cartaJogada, int* pulaVez);
int jogadaValida(Carta* carta, PilhaCartas* pilha);
void alteraCor(CartaPilha* carta, Jogador* jogador);

void atualizaRodada(PilhaCartas* pilha, PilhaCartas* baralho, Jogador** jogador, ListaJogadores* ls_jogadores, int* inversao, int* cartaJogada, int* winner, int* uno){
    CartaPilha* topo = pilha->topo;
    int pulaVez = 0;

    // caso o baralho seja vazio
    if (baralho->topo == NULL){
        // botar aqui funcao de embaralhar a pilha e inserir novamente no baralho

    }

    // Eventos da última carta jogada
    if (*cartaJogada == 1) {
        if (topo->info.num == 12) { // +2
            compraCarta(baralho, (*jogador)->mao, 2);
        } else if (topo->info.num == 13) { // +4
            compraCarta(baralho, (*jogador)->mao, 4);
        }
        *cartaJogada = 0;
    }

    // Secao de escolhas do jogador
    while (cartaJogada == 0 && pulaVez == 0){
        if ((*jogador)->npc == 0){
            inputsJogador((*jogador)->mao, pilha, baralho, cartaJogada, &pulaVez);
        }
        else {
            jogadaNPC((*jogador)->mao, pilha, baralho, cartaJogada, &pulaVez);
        }
    }


    // caso uma carta tenha sido jogada
    if (cartaJogada){
        // se o jogador atual nao tem mais cartas, winner = 1
        if (((*jogador)->mao)->n_cartas == 0){
            *winner = 1;
        }
        // se o jogador atual so tem uma carta
        if (((*jogador)->mao)->n_cartas == 1){
            *uno = 1;
        }

        // eventos da carta jogada na rodada atual
        topo = pilha->topo;
        // efeito de inversao
        if (topo->info.num == 11){
            *inversao = !(*inversao);
            *cartaJogada = 0;
        }

        // efeito alteracao da cor
        if (topo->info.num == 13 || topo->info.num == 14){
            alteraCor(topo, (*jogador));
            *cartaJogada = 0;
            //******** chamar aqui tambem a funcao que desenha o menu de escolha de cor ******************
        }
        // efeito block
        if (topo->info.num == 10){
            if (inversao == 0){
                (*jogador) = ((*jogador)->prox)->prox;
            }
            else {
                (*jogador) = ((*jogador)->ant)->ant;
            }
            *cartaJogada = 0;
        }
    }
    // efeito inversao
    else if (*inversao == 1){
        (*jogador) = (*jogador)->ant;
    }
    else {
        (*jogador) = (*jogador)->prox;
    }
}


/* ////////////////////////////////////////////
             FUNCOES AUXILIARES
//////////////////////////////////////////// */

// funcao que compra uma carta (tira do baralho e bota na mao do jogador atual)
void compraCarta(PilhaCartas* baralho, Mao* mao, int n){
    Info info_aux;
    for (int i = 0; i < n; i++){
        info_aux = desempilhaPilhaCartas(baralho);
        insereInicioMao(mao, info_aux);
    }
}


// Funcao que contempla as acoes possiveis do jogador
void inputsJogador(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho, int* cartaJogada, int* pulaVez){
    Vector2 mousePos = GetMousePosition();
    Vector2 posicaobaralho = {100, 200};
    Texture2D baralhoimagem = LoadTexture("baralho.png");
    int cartaComprada = 0;
    Info cartaInfoClicada;

    // Jogada do jogador
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    // Verificar se o clique foi dentro da área do baralho
        if (mousePos.x >= posicaobaralho.x && mousePos.x <= posicaobaralho.x + baralhoimagem.width &&
            mousePos.y >= posicaobaralho.y && mousePos.y <= posicaobaralho.y + baralhoimagem.height &&
            cartaComprada == 0) {
            // Tira uma carta da pilha e bota na mao do jogador
            Info info_aux = desempilhaPilhaCartas(baralho);
            insereInicioMao(mao, info_aux);
            cartaComprada = 1;
        }

        if (cartaComprada == 1 &&
            mousePos.x >= posicaoBotaoPular.x && mousePos.x <= posicaoBotaoPular.x + botaoPularImagem.width &&
            mousePos.y >= posicaoBotaoPular.y && mousePos.y <= posicaoBotaoPular.y + botaoPularImagem.height) {
            // funcao com botao para pular a vez
            *pulaVez = 1;
            //******** chamar funcao que desenha o botao de pular **************
            return;
        }

        else{
            Carta* cartaAtual = mao->prim;
            for (int i = 0; cartaAtual != NULL; i++) {
                Vector2 posicao = {6 + i * (LARGURA_CARTA + 30), 560};
                if (verificarCliqueCarta(mousePos, posicao)) {
                    if (jogadaValida(cartaAtual, pilha)) {
                        // remove a carta da mao e insere na pilha da mesa
                        cartaInfoClicada = removeCartaMao(mao, cartaAtual);
                        empilhaPilhaCartas(pilha, cartaInfoClicada);
                        *cartaJogada = 1;
                        return;
                    }
                }
                cartaAtual = cartaAtual->prox;
            }
        }
    }
}

// Função para verificar se a carta foi clicada
int verificarCliqueCarta(Vector2 mousePos, Vector2 posicaoCarta) {
    return (mousePos.x >= posicaoCarta.x && mousePos.x <= posicaoCarta.x + LARGURA_CARTA &&
            mousePos.y >= posicaoCarta.y && mousePos.y <= posicaoCarta.y + ALTURA_CARTA);
}

void jogadaNPC(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho, int* cartaJogada, int* pulaVez){
    Carta* aux;
    Info info_aux;


    for (aux = mao->prim; aux != NULL; aux = aux->prox){
        if (jogadaValida(aux, pilha)){
            info_aux = removeCartaMao(mao, aux);
            empilhaPilhaCartas(pilha, info_aux);
            *cartaJogada = 1;
            return;
        }
    }

    if (*cartaJogada == 0) {
        info_aux = desempilhaPilhaCartas(baralho);
        insereInicioMao(mao, info_aux);
        if (jogadaValida(mao->prim, pilha)){
            info_aux = removeCartaMao(mao, mao->prim);
            empilhaPilhaCartas(pilha, info_aux);
            *cartaJogada = 1;
        }
    }
    else if (cartaJogada == 0){
        *pulaVez = 1;
    }
}


// Funcao que determina se uma jogada eh valida
int jogadaValida(Carta* carta, PilhaCartas* pilha){
    CorCarta cor_mesa = (pilha->topo)->info.cor;
    int num_mesa = (pilha->topo)->info.num;

    if (carta->info.cor == PRETA){
        return 1;
    }
    else {
        return (carta->info.cor == cor_mesa || carta->info.num == num_mesa);
    }
}
// Funcao que altera a cor de uma carta conforme a escolha do usuario
void alteraCor(CartaPilha* carta, Jogador* jogador){
    // *********** nao esquecer caso em que o jogador eh um npc ******************
    // pra mim, se for npc ele pode escolher sempre a cor da primeira carta da mao (caso nao seja preta)
    // percorre a mao ate encontrar uma carta que nao eh preta e joga ela
    // se so houver cartas pretas escolher vermelho (ou qualquer outra cor)


}


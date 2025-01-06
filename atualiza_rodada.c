#include "TADs.h"
#include "stdio.h"

void compraCarta(CartasPilha* baralho, Mao* mao, int n);
void inputsJogador(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho);
void jogadaNPC(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho, int* cartaJogada, int* pulaVez);
int jogadaValida(Carta* carta, PilhaCartas* pilha);

void atualizaRodada(CartasPilha* pilha, CartasPilha* baralho, Jogador** jogador, ListaJogadores* ls_jogadores, int* inversao, int* cartaJogada){
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

    while (cartaJogada == 0 && pulaVez == 0){
        if ((*jogador)->npc == 0){
            inputsJogador((*jogador)->mao, pilha, baralho);
        }
        else {
            jogadaNPC()
        }
    }


    // caso uma carta tenha sido jogada
    if (cartaJogada){
        topo = pilha->topo;
        if (topo->info.num == 11){
            *inversao = !(*inversao);
            *cartaJogada = 0;
        }

        // efeito alteracao da cor
        if (topo->info.num == 13 || topo->info.num == 14){
            alteraCor(topo);
            *cartaJogada = 0;
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
void compraCarta(CartasPilha* baralho, Mao* mao, int n){
    Info info_aux;
    for (int i = 0; i < n; i++){
        info_aux = desempilhaPilhaCartas(baralho);
        insereInicioMao(mao, info_aux);
    }


// Funcao que contempla as acoes possiveis do jogador
void inputsJogador(Mao* mao, PilhaCartas* pilha, PilhaCartas* baralho, int* cartaJogada, int* pulaVez){
    Vector2 mousePos = GetMousePosition();
    int cartaComprada = 0;

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
            return;
        }

        else{
            Carta* cartaAtual = jogador.mao->prim;
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
    int cartaComprada = 0;

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
        cartaComprada = 1;
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

    if (carta->cor == PRETA){
        return 1;
    }
    else {
        return (carta->info.cor == cor_mesa || carta->info.num == num_mesa);
    }
}

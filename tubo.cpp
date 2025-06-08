#include "tubo.hpp"
#include "constants.h"
#include <allegro5/allegro_image.h>
#include <cstdlib>
#include <cstdio>

ALLEGRO_BITMAP* Tubo::imagem_cima = nullptr;
ALLEGRO_BITMAP* Tubo::imagem_baixo = nullptr;

void carregar_imagens_tubo() {
    Tubo::imagem_cima = al_load_bitmap("output/cimaori.png");
    Tubo::imagem_baixo = al_load_bitmap("output/baixoori.png");
}

void destruir_imagens_tubo() {
    al_destroy_bitmap(Tubo::imagem_cima);
    al_destroy_bitmap(Tubo::imagem_baixo);
}

Tubo::Tubo(int posicao_x) {
    this->x = posicao_x;
    this->altura_abertura = rand() % (ALTURA_TELA - ESPACO_ENTRE_TUBOS - 150) + 75;
}

void Tubo::atualizar() {
    this->x -= VELOCIDADE_TUBO;
    if (this->x + LARGURA_TUBO < 0) {
        this->x = LARGURA_TELA;
        this->altura_abertura = rand() % (ALTURA_TELA - ESPACO_ENTRE_TUBOS - 150) + 75;
    }
}

void Tubo::desenhar() {
        al_draw_bitmap(imagem_cima, this->x, this->altura_abertura - ALTURA_TUBO, 0);
        al_draw_bitmap(imagem_baixo, this->x, this->altura_abertura + ESPACO_ENTRE_TUBOS, 0);
}


bool Tubo::colide(int jogador_x, int jogador_y, int jogador_largura, int jogador_altura) {
    
    if ((jogador_x + jogador_largura > this->x) &&                                       // O lado direito do jogador passou o lado esquerdo do tubo E
        (jogador_x < this->x + LARGURA_TUBO) &&                                           // O lado esquerdo do jogador ainda não passou o lado direito do tubo E
        (jogador_y + jogador_altura > this->altura_abertura - ALTURA_TUBO) &&             // A base do jogador está abaixo do topo do sprite do tubo E
        (jogador_y < this->altura_abertura)) {                                            // O topo do jogador está acima da base do tubo
        return true;
    }

    if ((jogador_x + jogador_largura > this->x) &&                                       // O lado direito do jogador passou o lado esquerdo do tubo E
        (jogador_x < this->x + LARGURA_TUBO) &&                                           // O lado esquerdo do jogador ainda não passou o lado direito do tubo E
        (jogador_y + jogador_altura > this->altura_abertura + ESPACO_ENTRE_TUBOS) &&      // a base do jogador está abaixo do topo do tubo de baixo E
        (jogador_y < this->altura_abertura + ESPACO_ENTRE_TUBOS + ALTURA_TUBO)) {          // o topo do jogador está acima da base do tubo de baixo
        return true;
    }

    return false;
}
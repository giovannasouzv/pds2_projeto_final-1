#include "jogador.hpp"
#include "constants.h"
#include <allegro5/allegro_image.h>

Jogador::Jogador() { // construtor
    x = 100;
    y = ALTURA_TELA / 2;
    velocidade_y = 0;

    imagem = al_load_bitmap("assets/flapyk.png");
    frame_atual = 0;
    tempo_frame = 0;
}

Jogador::~Jogador() {
    al_destroy_bitmap(imagem);
}

void Jogador::atualizar() {
    velocidade_y += GRAVIDADE;
    y += velocidade_y; // altera a posição de acordo com a velocidade (gravidade)

    tempo_frame++; // troca os frames da animação
    if (tempo_frame > 5) {
        frame_atual = (frame_atual + 1) % 3;
        tempo_frame = 0;
    }
}

void Jogador::pular() { // quando chamar esse método a velocidade vai ser alterada pra verlocidade do pulo e não da gravidade
    velocidade_y = FORCA_PULO;
}

void Jogador::desenhar() {
    al_draw_bitmap_region(imagem, frame_atual * 51, 0, 51, 38, x, y, 0); // sx e xy é onde vai cortar NA imagem; sh e sw altura e largura da parte com corte 
} // dx e dy a posição da imagem por isso está em x e y
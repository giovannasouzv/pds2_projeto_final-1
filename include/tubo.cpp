#ifndef TUBO_HPP
#define TUBO_HPP

#include <allegro5/allegro.h>

class Tubo {
public:
    int x;
    int altura_abertura;

    static ALLEGRO_BITMAP* imagem_cima;
    static ALLEGRO_BITMAP* imagem_baixo;

    Tubo(int posicao_x);
    void atualizar();
    void desenhar();
    bool colide(int jogador_x, int jogador_y, int jogador_largura, int jogador_altura);
};

void carregar_imagens_tubo();
void destruir_imagens_tubo();

#endif
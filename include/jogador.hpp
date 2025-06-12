#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <allegro5/allegro.h>

class Jogador {
public:
    int x, y;
    int velocidade_y;

    ALLEGRO_BITMAP* imagem;
    int frame_atual;
    int tempo_frame;

    Jogador(); // construtor do jogador
    ~Jogador(); // destrutor
    void atualizar();
    void pular();
    void desenhar();
};

#endifs
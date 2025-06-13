#ifndef FUNDO_HPP
#define FUNDO_HPP

#include <allegro5/allegro.h>

class Fundo {
private:
    ALLEGRO_BITMAP* imagem;
    int posicao_x;

public:
    Fundo();
    ~Fundo();
    void atualizar();
    void desenhar();
};

#endif
#ifndef CADASTRO_H
#define CADASTRO_H

#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

using namespace std;

struct Jogador {
    string apelido_unico;
    string nome;

    int pontuacao;
    int numero_de_jogos;
    int melhor_pontuacao;

    int cor_r, cor_g, cor_b;
    string caminho_avatar;

    ALLEGRO_COLOR cor;
    ALLEGRO_BITMAP* avatar;
};

class Cadastro {
private:
    vector<Jogador> jogadores;
    ALLEGRO_FONT* fonte;

    bool apelido_existe(const string& apelido) const;
    void ordenar_por_pontuacao();

public:
    Cadastro(ALLEGRO_FONT* fonte = nullptr);
    ~Cadastro();

    bool cadastrar_jogador(const string& apelido_unico, const string& nome = "",
                           ALLEGRO_COLOR cor = al_map_rgb(255, 255, 255));
    bool trocar_apelido(const string& apelido_antigo, const string& apelido_novo);
    bool remover_jogador(const string& apelido_unico);
    bool carregar_avatar(const string& apelido_unico, const string& caminho_imagem);

    bool incrementar_pontuacao(const string& apelido_unico, int pontuacao);
    void resetar_estatisticas(const string& apelido_unico);

    const Jogador* buscar_jogador(const string& apelido_unico) const;
    const vector<Jogador>& obter_ranking() const;
    const Jogador* jogador_com_maior_pontuacao() const;
    void exibir_jogadores(int x, int y, ALLEGRO_DISPLAY* display) const;

    bool salvar_jogadores(const string& arquivo) const;
    bool carregar_jogadores(const string& arquivo);

    void definir_fonte(ALLEGRO_FONT* nova_fonte);
};

#endif

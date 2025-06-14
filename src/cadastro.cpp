#include "cadastro.hpp"
#include <fstream>
#include <iostream>

Cadastro::Cadastro(ALLEGRO_FONT* fonte) : fonte(fonte) {}
Cadastro::~Cadastro() {
    for (auto& jogador : jogadores) {
        if (jogador.avatar) {
            al_destroy_bitmap(jogador.avatar);
        }
    }
}

bool Cadastro::apelido_existe(const string& apelido) const {
    for (const auto& j : jogadores) {
        if (j.apelido_unico == apelido)
            return true;
    }
    return false;
}

bool Cadastro::cadastrar_jogador(const string& apelido_unico, const string& nome, ALLEGRO_COLOR cor) {
    if (apelido_existe(apelido_unico)) return false;
    Jogador novo;
    novo.apelido_unico = apelido_unico;
    novo.nome = nome;
    novo.pontuacao = 0;
    novo.numero_de_jogos = 0;
    novo.melhor_pontuacao = 0;
    novo.cor = cor;
    novo.cor_r = (int)(cor.r * 255);
    novo.cor_g = (int)(cor.g * 255);
    novo.cor_b = (int)(cor.b * 255);
    novo.avatar = nullptr;
    jogadores.push_back(novo);
    return true;
}

bool Cadastro::trocar_apelido(const string& antigo, const string& novo) {
    if (apelido_existe(novo)) return false;
    for (auto& j : jogadores) {
        if (j.apelido_unico == antigo) {
            j.apelido_unico = novo;
            return true;
        }
    }
    return false;
}

bool Cadastro::remover_jogador(const string& apelido) {
    for (auto it = jogadores.begin(); it != jogadores.end(); ++it) {
        if (it->apelido_unico == apelido) {
            if (it->avatar) al_destroy_bitmap(it->avatar);
            jogadores.erase(it);
            return true;
        }
    }
    return false;
}

bool Cadastro::carregar_avatar(const string& apelido, const string& caminho) {
    for (auto& j : jogadores) {
        if (j.apelido_unico == apelido) {
            if (j.avatar) al_destroy_bitmap(j.avatar);
            j.avatar = al_load_bitmap(caminho.c_str());
            if (j.avatar) {
                j.caminho_avatar = caminho;
                return true;
            }
        }
    }
    return false;
}

bool Cadastro::incrementar_pontuacao(const string& apelido, int pontos) {
    for (auto& j : jogadores) {
        if (j.apelido_unico == apelido) {
            j.pontuacao += pontos;
            j.numero_de_jogos++;
            if (j.pontuacao > j.melhor_pontuacao)
                j.melhor_pontuacao = j.pontuacao;
            return true;
        }
    }
    return false;
}

void Cadastro::resetar_estatisticas(const string& apelido) {
    for (auto& j : jogadores) {
        if (j.apelido_unico == apelido) {
            j.pontuacao = 0;
            j.numero_de_jogos = 0;
            j.melhor_pontuacao = 0;
        }
    }
}

const Jogador* Cadastro::buscar_jogador(const string& apelido) const {
    for (const auto& j : jogadores) {
        if (j.apelido_unico == apelido)
            return &j;
    }
    return nullptr;
}

const vector<Jogador>& Cadastro::obter_ranking() const {
    return jogadores;
}

const Jogador* Cadastro::jogador_com_maior_pontuacao() const {
    if (jogadores.empty()) return nullptr;
    return &*max_element(jogadores.begin(), jogadores.end(), [](const Jogador& a, const Jogador& b) {
        return a.pontuacao < b.pontuacao;
    });
}

void Cadastro::exibir_jogadores(int x, int y, ALLEGRO_DISPLAY* display) const {
    if (!fonte) return;
    int offset = 0;
    for (const auto& j : jogadores) {
        al_draw_textf(fonte, j.cor, x, y + offset, 0, "%s (%s) - %d pontos", j.nome.c_str(), j.apelido_unico.c_str(), j.pontuacao);
        offset += 30;
    }
}

void Cadastro::ordenar_por_pontuacao() {
    sort(jogadores.begin(), jogadores.end(), [](const Jogador& a, const Jogador& b) {
        return a.pontuacao > b.pontuacao;
    });
}

bool Cadastro::salvar_jogadores(const string& arquivo) const {
    ofstream out(arquivo);
    if (!out) return false;
    for (const auto& j : jogadores) {
        out << j.apelido_unico << ";" << j.nome << ";" << j.pontuacao << ";"
            << j.numero_de_jogos << ";" << j.melhor_pontuacao << ";"
            << j.cor_r << ";" << j.cor_g << ";" << j.cor_b << ";"
            << j.caminho_avatar << "\n";
    }
    return true;
}

bool Cadastro::carregar_jogadores(const string& arquivo) {
    ifstream in(arquivo);
    if (!in) return false;
    jogadores.clear();
    string linha;
    while (getline(in, linha)) {
        Jogador j;
        replace(linha.begin(), linha.end(), ';', ' ');
        istringstream iss(linha);
        iss >> j.apelido_unico >> j.nome >> j.pontuacao >> j.numero_de_jogos >> j.melhor_pontuacao
            >> j.cor_r >> j.cor_g >> j.cor_b >> j.caminho_avatar;
        j.cor = al_map_rgb(j.cor_r, j.cor_g, j.cor_b);
        j.avatar = j.caminho_avatar.empty() ? nullptr : al_load_bitmap(j.caminho_avatar.c_str());
        jogadores.push_back(j);
    }
    return true;
}

void Cadastro::definir_fonte(ALLEGRO_FONT* nova_fonte) {
    fonte = nova_fonte;
}
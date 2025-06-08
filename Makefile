all: main

src/fundo.o: include/fundo.hpp include/constants.h src/fundo.cpp
	g++ -o src/fundo.o -c src/fundo.cpp -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

src/jogador.o: include/jogador.hpp include/constants.h src/jogador.cpp
	g++ -o src/jogador.o -c src/jogador.cpp -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

src/tubo.o: include/tubo.hpp include/constants.h src/tubo.cpp
	g++ -o src/tubo.o -c src/tubo.cpp -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

src/main.o: src/main.cpp include/constants.h
	g++ -o src/main.o -c src/main.cpp -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

main: src/main.o src/fundo.o src/jogador.o src/tubo.o
	g++ src/main.o src/fundo.o src/jogador.o src/tubo.o -o main `pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5`

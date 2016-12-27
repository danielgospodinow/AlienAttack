CC = g++
CFLAGS = -c -Wall
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lpthread

all: alienAttack clean_o

alienAttack: main.o game.o sdl_components.o game_utilities.o main_menu_scene.o 
			$(CC) main.o game.o sdl_components.o game_utilities.o main_menu_scene.o  -o AlienAttack $(LINKER_FLAGS)


main.o: main.cpp
			$(CC) $(CFLAGS) main.cpp
game.o:	game.cpp
			$(CC) $(CFLAGS) game.cpp
sdl_components.o: sdl_components.cpp
			$(CC) $(CFLAGS) sdl_components.cpp
game_utilities.o: game_utilities.cpp
			$(CC) $(CFLAGS) game_utilities.cpp
main_menu_scene.o: main_menu_scene.cpp
			$(CC) $(CFLAGS) main_menu_scene.cpp


clean:
			rm -rf *.o AlienAttack
clean_o:
			rm -rf *.o
CC = g++
CFLAGS = -c -Wall
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lpthread

all: alienAttack clean_o

alienAttack: main.o game.o sdl_components.o game_utilities.o main_menu_scene.o button.o label.o play_sp_scene.o sprite.o player.o bullet.o enemy.o enemy_horde.o special_monster.o health_bar.o
			$(CC) main.o game.o sdl_components.o game_utilities.o main_menu_scene.o button.o label.o play_sp_scene.o sprite.o player.o bullet.o enemy.o enemy_horde.o special_monster.o health_bar.o -o AlienAttack $(LINKER_FLAGS)


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
button.o:	button.cpp
			$(CC) $(CFLAGS) button.cpp
label.o:	label.cpp
			$(CC) $(CFLAGS) label.cpp
play_sp_scene.o:	play_sp_scene.cpp
			$(CC) $(CFLAGS) play_sp_scene.cpp
sprite.o:	sprite.cpp
			$(CC) $(CFLAGS) sprite.cpp
player.o:	player.cpp
			$(CC) $(CFLAGS) player.cpp
bullet.o:	bullet.cpp
			$(CC) $(CFLAGS) bullet.cpp
enemy.o:	enemy.cpp
			$(CC) $(CFLAGS) enemy.cpp
enemy_horde.o:	enemy_horde.cpp
			$(CC) $(CFLAGS) enemy_horde.cpp
special_monster.o:	special_monster.cpp
			$(CC) $(CFLAGS) special_monster.cpp
health_bar.o:	health_bar.cpp
			$(CC) $(CFLAGS) health_bar.cpp


clean:
			rm -rf *.o AlienAttack
clean_o:
			rm -rf *.o

CC = g++
CFLAGS = -c -Wall
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lpthread

all: alienAttack clean_o

alienAttack: main.o game.o sdl_components.o game_utilities.o main_menu_scene.o button.o label.o play_sp_scene.o sprite.o player.o bullet.o enemy.o enemy_horde.o special_monster.o health_bar.o play_mp_scene.o barricades.o ui.o
			$(CC) main.o game.o sdl_components.o game_utilities.o main_menu_scene.o button.o label.o play_sp_scene.o sprite.o player.o bullet.o enemy.o enemy_horde.o special_monster.o health_bar.o play_mp_scene.o barricades.o ui.o -o AlienAttack $(LINKER_FLAGS)


main.o: src/main.cpp
			$(CC) $(CFLAGS) src/main.cpp
game.o:	src/game.cpp
			$(CC) $(CFLAGS) src/game.cpp
sdl_components.o: src/sdl_components.cpp
			$(CC) $(CFLAGS) src/sdl_components.cpp
game_utilities.o: src/game_utilities.cpp
			$(CC) $(CFLAGS) src/game_utilities.cpp
main_menu_scene.o: src/main_menu_scene.cpp
			$(CC) $(CFLAGS) src/main_menu_scene.cpp
button.o:	src/button.cpp
			$(CC) $(CFLAGS) src/button.cpp
label.o:	src/label.cpp
			$(CC) $(CFLAGS) src/label.cpp
play_sp_scene.o:	src/play_sp_scene.cpp
			$(CC) $(CFLAGS) src/play_sp_scene.cpp
play_mp_scene.o:	src/play_mp_scene.cpp
			$(CC) $(CFLAGS) src/play_mp_scene.cpp
sprite.o:	src/sprite.cpp
			$(CC) $(CFLAGS) src/sprite.cpp
player.o:	src/player.cpp
			$(CC) $(CFLAGS) src/player.cpp
bullet.o:	src/bullet.cpp
			$(CC) $(CFLAGS) src/bullet.cpp
enemy.o:	src/enemy.cpp
			$(CC) $(CFLAGS) src/enemy.cpp
enemy_horde.o:	src/enemy_horde.cpp
			$(CC) $(CFLAGS) src/enemy_horde.cpp
special_monster.o:	src/special_monster.cpp
			$(CC) $(CFLAGS) src/special_monster.cpp
health_bar.o:	src/health_bar.cpp
			$(CC) $(CFLAGS) src/health_bar.cpp
barricades.o:	src/barricades.cpp
			$(CC) $(CFLAGS) src/barricades.cpp
ui.o:	src/ui.cpp
			$(CC) $(CFLAGS) src/ui.cpp


clean:
			rm -rf *.o AlienAttack
clean_o:
			rm -rf *.o

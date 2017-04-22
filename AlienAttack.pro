TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/bullet.cpp \
  src/button.cpp \
  src/enemy.cpp \
  src/enemy_horde.cpp \
  src/game.cpp \
  src/game_utilities.cpp \
  src/health_bar.cpp \
  src/label.cpp \
  src/main.cpp \
  src/main_menu_scene.cpp \
  src/player.cpp \
  src/play_mp_scene.cpp \
  src/play_sp_scene.cpp \
  src/sdl_components.cpp \
  src/special_monster.cpp \
  src/sprite.cpp \
  src/barricades.cpp \
  src/ui.cpp \


HEADERS += src/bullet.hpp \
  src/button.hpp \
  src/enemy.hpp \
  src/enemy_horde.hpp \
  src/game.hpp \
  src/game_utilities.hpp \
  src/globals.hpp \
  src/health_bar.hpp \
  src/label.hpp \
  src/main_menu_scene.hpp \
  src/player.hpp \
  src/play_mp_scene.hpp \
  src/play_sp_scene.hpp \
  src/scene.hpp \
  src/sdl_components.hpp \
  src/special_monster.hpp \
  src/sprite.hpp \
  src/vec2.hpp \
  src/barricades.hpp \
  src/ui.hpp

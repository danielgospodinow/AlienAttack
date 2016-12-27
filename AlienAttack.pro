TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game.cpp \
    sdl_components.cpp \
    main_menu_scene.cpp \
    game_utilities.cpp
HEADERS += globals.hpp \
    game.hpp \
    sdl_components.hpp \
    vec2.hpp \
    scene.hpp \
    main_menu_scene.hpp \
    game_utilities.hpp

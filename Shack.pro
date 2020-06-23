TEMPLATE = app
CONFIG += c++17
CONFIG += console
CONFIG += static
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Background.cpp \
        Boom.cpp \
        Button.cpp \
        Corridor.cpp \
        Entity.cpp \
        Globals.cpp \
        Map.cpp \
        Menu.cpp \
        Monsters.cpp \
        Player.cpp \
        Robot.cpp \
        Room.cpp \
        Tile.cpp \
        main.cpp
INCLUDEPATH += "C:\Program Files (x86)\SFML-2.5.1\include"
LIBS += -L"C:\Program Files (x86)\SFML-2.5.1\lib"
CONFIG(debug, release){
    LIBS += -lsfml-audio-s -lsfml-graphics-s -lsfml-network-s -lsfml-system-s -lsfml-window-s
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    Background.hpp \
    Boom.hpp \
    Button.hpp \
    Corridor.hpp \
    Entity.hpp \
    Globals.hpp \
    Map.hpp \
    Menu.hpp \
    Monsters.hpp \
    Player.hpp \
    Robot.hpp \
    Room.hpp \
    Tile.hpp

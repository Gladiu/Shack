TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Corridor.cpp \
        Entity.cpp \
        Globals.cpp \
        Map.cpp \
        Player.cpp \
        Room.cpp \
        Tile.cpp \
        main.cpp
INCLUDEPATH += "C:\Program Files (x86)\SFML-2.5.1\include"
LIBS += -L"C:\Program Files (x86)\SFML-2.5.1\lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    Corridor.hpp \
    Entity.hpp \
    Globals.hpp \
    Map.hpp \
    Player.hpp \
    Room.hpp \
    Tile.hpp

QT += network
SOURCES += main.cpp \
    controller/keyboardhandler.cpp \
    view/window.cpp \
    model/shot.cpp \
    model/weapon.cpp \
    model/handgun.cpp \
    model/shotgun.cpp \
    model/machinegun.cpp \
    model/mapobject.cpp \
    model/player.cpp \
    model/shootableblock.cpp \
    model/unshootableblock.cpp \
    model/weaponpackage.cpp \
    controller/game.cpp \
    view/dialogs/creategame.cpp \
    view/dialogs/joingame.cpp \
    controller/network.cpp \
    controller/networkinterface.cpp \
    controller/client.cpp \
    controller/server.cpp \
    controller/gamefacade.cpp \
    view/scenepanel.cpp \
    view/pixmapitem.cpp
TRANSLATIONS += snowman-battle_cs.ts
OTHER_FILES += 
HEADERS += controller/keyboardhandler.h \
    view/window.h \
    model/shot.h \
    model/weapon.h \
    model/handgun.h \
    model/shotgun.h \
    model/machinegun.h \
    model/mapobject.h \
    model/player.h \
    model/shootableblock.h \
    model/unshootableblock.h \
    model/weaponpackage.h \
    controller/game.h \
    view/dialogs/creategame.h \
    view/dialogs/joingame.h \
    controller/network.h \
    controller/networkinterface.h \
    controller/client.h \
    controller/server.h \
    controller/gamefacade.h \
    view/scenepanel.h \
    view/pixmapitem.h
RESOURCES += images.qrc

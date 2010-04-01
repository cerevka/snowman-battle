QT += network
SOURCES += main.cpp \
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
    view/dialogs/creategame.cpp \
    view/dialogs/joingame.cpp \
    view/scenepanel.cpp \
    view/pixmapitem.cpp \
    ../snowman-battle \
    (copy)/controller/client.cpp \
    controller/game/game.cpp \
    controller/game/gamefacade.cpp \
    controller/game/game.cpp \
    controller/gui/keyboardhandler.cpp \
    controller/network/server.cpp \
    controller/network/networkinterface.cpp \
    controller/network/network.cpp \
    controller/network/client.cpp
TRANSLATIONS += snowman-battle_cs.ts
OTHER_FILES += 
HEADERS += view/window.h \
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
    view/dialogs/creategame.h \
    view/dialogs/joingame.h \
    view/scenepanel.h \
    view/pixmapitem.h \
    controller/game/gamefacade.h \
    controller/game/game.h \
    controller/gui/keyboardhandler.h \
    controller/network/server.h \
    controller/network/networkinterface.h \
    controller/network/network.h \
    controller/network/client.h
RESOURCES += images.qrc

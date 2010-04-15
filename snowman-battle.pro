QT += network
HEADERS += controller/game/gamefacade.h \
    controller/game/game.h \
    controller/gui/keyboardhandler.h \
    controller/network/server.h \
    controller/network/network.h \
    controller/network/client.h \
    model/weaponpackage.h \
    model/weapon.h \
    model/unshootableblock.h \
    model/shotgun.h \
    model/shot.h \
    model/shootableblock.h \
    model/player.h \
    model/mapobject.h \
    model/machinegun.h \
    model/handgun.h \
    view/window.h \
    view/scenepanel.h \
    view/pixmapitem.h \
    view/dialogs/joingame.h \
    view/dialogs/creategame.h \
    view/statusbar.h \
    view/chatpanel.h \
    controller/network/packetparser.h \
    controller/network/networkinterface.h \
    controller/network/clientthread.h \
    globals.h \
    controller/network/packetcreator.h \
    view/dialogs/connecteddialog.h \
    view/dialogs/connectjoindialog.h \
    view/dialogs/endgamedialog.h
SOURCES += controller/game/gamefacade.cpp \
    controller/game/game.cpp \
    controller/gui/keyboardhandler.cpp \
    controller/network/server.cpp \
    controller/network/network.cpp \
    controller/network/client.cpp \
    model/weaponpackage.cpp \
    model/weapon.cpp \
    model/unshootableblock.cpp \
    model/shotgun.cpp \
    model/shot.cpp \
    model/shootableblock.cpp \
    model/player.cpp \
    model/mapobject.cpp \
    model/machinegun.cpp \
    model/handgun.cpp \
    view/window.cpp \
    view/scenepanel.cpp \
    view/pixmapitem.cpp \
    view/dialogs/joingame.cpp \
    view/dialogs/creategame.cpp \
    main.cpp \
    view/statusbar.cpp \
    controller/network/packetparser.cpp \
    view/chatpanel.cpp \
    controller/network/networkinterface.cpp \
    controller/network/clientthread.cpp \
    controller/network/packetcreator.cpp \
    view/dialogs/connecteddialog.cpp \
    view/dialogs/connectjoindialog.cpp \
    view/dialogs/endgamedialog.cpp
RESOURCES += images.qrc
TRANSLATIONS += snowman-battle_cs.ts
DEFINES += _DEBUG_

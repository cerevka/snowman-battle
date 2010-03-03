
#include <QtCore>
#include <QtGui>

/**
 * Funkce main = vstupní bod programu
 */
int main(int argc, char * argv[])
{

    int returnValue = 0;

    // Inicializace Qt
    QApplication app(argc, argv);

    // Inicializace českého překladu
    QTranslator translator;
    translator.load("snowman-battle_cs.qm");
    app.installTranslator(&translator);

    // TODO zde bude alokace proměnných pro vlastní program (např. hlavní okno programu)
    // ...

    // Spouštim Qt
    returnValue = app.exec();

    // TODO zde bude dealokace dynamicky alokovanýh proměných
    // ...

    return returnValue;

}

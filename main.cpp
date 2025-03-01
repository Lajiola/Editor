#include <QApplication>
#include "hexbinchareditor.h"

// Hauptfunktion: Erstellt die Anwendung und startet die Hauptoberfläche
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    HexBinCharEditor editor;
    editor.show();
    return app.exec();
}

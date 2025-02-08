#include "src/delegate/maincontroller.h"
#include <QFontDatabase>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Mise en place de la police
    int fontId = QFontDatabase::addApplicationFont(":/fonts/Bubblegum.otf");
    if (fontId == -1) {
        qWarning() << "Failed to load font!";
    } else {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(fontFamily,25);
        QApplication::setFont(font);
    }

    MainController mainController;
    return a.exec();
}

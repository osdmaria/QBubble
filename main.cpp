#include "src/delegate/maincontroller.h"
#include <QFontDatabase>
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //icone du jeu
    a.setWindowIcon(QIcon("://images/window_icon.png"));

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
    QTimer::singleShot(1000, []() {
        QWidget *mainWin = QApplication::activeWindow();
        if (mainWin) {
            qDebug() << "Active window size after startup: " << mainWin->size();
        }
    });
    return a.exec();
}

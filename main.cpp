#include "Menu/menu.h"

#include <QApplication>
#include <QFontDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load the custom font from the resources
    int fontId = QFontDatabase::addApplicationFont(":/font/Bubblegum.otf");
    if (fontId == -1) {
        qWarning() << "Failed to load font!";
    } else {
        // Get the font family name
        qDebug() << "Loaded!";
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

        // Set the font as the default application font
        QFont font(fontFamily, 12);  // 12 is the default size, adjust as needed
        QApplication::setFont(font);
    }



    Menu menu;
    menu.show();
    return a.exec();
}

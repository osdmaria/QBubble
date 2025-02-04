#include "menumultijoueur.h"
#include "menu.h"

MenuMultijoueur::MenuMultijoueur(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    setFont(QApplication::font());
    applyFontToChildren(this);
}

void MenuMultijoueur::applyFontToChildren(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (child->isWidgetType()) {
            QWidget *childWidget = qobject_cast<QWidget *>(child);
            childWidget->setFont(QApplication::font());
            applyFontToChildren(childWidget);  // Recursively apply to grandchildren
        }
    }
}

void MenuMultijoueur::on_pushButton_3_clicked()
{
    Menu *mainmenu = qobject_cast<Menu*>(parentWidget()); // Ensure correct type
    if (mainmenu) {
        qDebug() << "MainMenu found, showing it again!";
        mainmenu->show(); // Show MainWindow
    } else {
        qDebug() << "MainMenu not found!";
    }
    close();
}

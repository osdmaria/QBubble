#include "menuregles.h"
#include "menu.h"
#include <QFontDatabase>

MenuRegles::MenuRegles(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    setFont(QApplication::font());
    applyFontToChildren(this);
}

void MenuRegles::applyFontToChildren(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (child->isWidgetType()) {
            QWidget *childWidget = qobject_cast<QWidget *>(child);
            childWidget->setFont(QApplication::font());
            applyFontToChildren(childWidget);  // Recursively apply to grandchildren
        }
    }
}

void MenuRegles::on_pushButton_3_clicked()
{

    Menu *mainmenu = qobject_cast<Menu*>(parentWidget()); // Ensure correct type
    if (mainmenu) {
        qDebug() << "MainWindow found, showing it again!";
        mainmenu->show(); // Show MainWindow
    } else {
        qDebug() << "MainWindow not found!";
    }
    close();
}

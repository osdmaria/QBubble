#include "menu.h"
#include "menumultijoueur.h"
#include "game_main_window.h"
#include "menuregles.h"

Menu::Menu(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    setFont(QApplication::font());
    applyFontToChildren(this);
}

Menu::~Menu() {}

void Menu::applyFontToChildren(QWidget *widget)
{
    for (QObject *child : widget->children()) {
        if (child->isWidgetType()) {
            QWidget *childWidget = qobject_cast<QWidget *>(child);
            childWidget->setFont(QApplication::font());
            applyFontToChildren(childWidget);  // Recursively apply to grandchildren
        }
    }
}

//Les Regles button
void Menu::on_pushButton_4_clicked()
{
    hide(); // Hide MainWindow
    MenuRegles *CJ = new MenuRegles(this); // Pass MainWindow as parent
    CJ->setModal(true);
    CJ->exec(); // Show modal dialog
    delete CJ;
}

//quitter button
void Menu::on_pushButton_3_clicked()
{
    delete this;
}

//multi joueur button

void Menu::on_pushButton_2_clicked()
{
    hide();
    MenuMultijoueur *MJ = new MenuMultijoueur(this);
    MJ->setModal(true);
    MJ->exec();
    delete MJ;

}

// Jouer Solo

void Menu::on_pushButton_1_clicked()
{
    hide();
    MenuMultijoueur *MJ = new MenuMultijoueur(this);
    MJ->setModal(true);
    MJ->exec();
    delete MJ;

}

void Menu::on_pushButton_clicked()
{
    hide();
    MainWindow *w = new MainWindow(this);
    w->show();
}


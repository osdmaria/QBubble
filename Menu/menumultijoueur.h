#ifndef MENUMULTIJOUEUR_H
#define MENUMULTIJOUEUR_H

#include "ui_menumultijoueur.h"

class MenuMultijoueur : public QDialog, private Ui::MenuMultijoueur
{
    Q_OBJECT

public:
    explicit MenuMultijoueur(QWidget *parent = nullptr);

private slots:
    void on_pushButton_3_clicked();
    void applyFontToChildren(QWidget *widget);
};

#endif // MENUMULTIJOUEUR_H

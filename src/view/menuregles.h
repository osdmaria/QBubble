#ifndef MENUREGLES_H
#define MENUREGLES_H

#include "ui_menuregles.h"

class MenuRegles : public QDialog, private Ui::MenuRegles
{
    Q_OBJECT

public:
    explicit MenuRegles(QWidget *parent = nullptr);
private slots:
    void on_pushButton_3_clicked();
    void applyFontToChildren(QWidget *widget);
};

#endif // MENUREGLES_H

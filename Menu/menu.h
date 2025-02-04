#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_menu.h"


#include <QWidget>
class Menu : public QWidget, private Ui::Menu
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_1_clicked();

    void on_pushButton_clicked();

    void applyFontToChildren(QWidget *widget);

private :
    Ui::Menu *ui;

};
#endif // MAINWINDOW_H



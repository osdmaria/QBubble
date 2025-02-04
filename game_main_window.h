#ifndef GAME_MAIN_WINDOW_H
#define GAME_MAIN_WINDOW_H

#include "ui_game_main_window.h"


#include <QDebug>
#include <QMainWindow>
#include <QPointF>
#include <QPainter>
#include <QtQml/QQmlContext>


class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected slots: // Definition des slots (methodes invoquables via le gestionnaire des événements)
    void onFireBubble(QPointF start, QPointF end);


};
#endif // GAME_MAIN_WINDOW_H

#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H

#include "ui_pausewindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QPainter>

class pausewindow : public QDialog, private Ui::pausewindow
{
    Q_OBJECT

public:
    explicit pausewindow(QWidget *parent = nullptr);
    ~pausewindow();
    QPushButton *m_reprendreButton;
    QPushButton *m_menuPrincipalButton;


signals:
    void reprendreClicked();
    //void resumeGame();

private:

    void setupUi();
    void connectSignals();
    void paintEvent(QPaintEvent *event) ;
};

#endif // PAUSEWINDOW_H




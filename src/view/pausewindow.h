#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QDialog>

#include "src/view/music.h"

class pausewindow : public QDialog
{
    Q_OBJECT

public:
    explicit pausewindow(QWidget *parent = nullptr);
    ~pausewindow();
    QPushButton *m_reprendreButton;
    QPushButton *m_nouvellePartieButton;


signals:
    void reprendreClicked();
    //void resumeGame();

private:
    Music *m_music;

    void setupUi();
    void connectSignals();
    void paintEvent(QPaintEvent *event) ;

};

#endif // PAUSEWINDOW_H

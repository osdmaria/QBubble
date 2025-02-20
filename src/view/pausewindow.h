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
#include <QSpacerItem>

#include "src/view/music.h"

class PauseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PauseWindow(QWidget *parent = nullptr);
    ~PauseWindow();
    QPushButton *m_reprendreButton;
    QPushButton *m_saveGameButton;
    QPushButton *m_retryButton;


signals:
    void reprendreClicked();
    void retryClicked();

private:
    Music *m_music;

    void setupUi();
    void connectSignals();
    void paintEvent(QPaintEvent *event) ;

};

#endif // PAUSEWINDOW_H

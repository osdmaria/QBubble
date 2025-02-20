#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include "ui_gameoverwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QDialog>

class gameOverWindow : public QDialog, private Ui::gameOverWindow
{
    Q_OBJECT

public:
    explicit gameOverWindow(QWidget *parent = nullptr);
    ~gameOverWindow();
    QPushButton *m_rejouerButton;
    QPushButton *m_menuPrincipalButton;

signals:
    void replayClicked();
    void backMenuClicked();
private:

    void setupUi();
    void connectSignals();
};


#endif // GAMEOVERWINDOW_H

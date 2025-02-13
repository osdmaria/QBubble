#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H


#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QPixmap>
#include <QLabel>

#include "Music.h"

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();

    QPushButton *m_soloButton;
    QPushButton *m_multiplayerButton;
    QPushButton *m_howToPlayButton;
    QPushButton *m_quitButton;

signals:
    void onSoloClicked();
    void onMultiplayerClicked();
    void onHowToPlayClicked();
    void onQuitClicked();

private:
    void setupUi();
    void connectSignals();
    void paintEvent(QPaintEvent *event);
    QLabel* createTitle();
    Music *m_music;
};
#endif // MAINMENUWINDOW_H

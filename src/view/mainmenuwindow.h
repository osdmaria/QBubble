#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H


#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QPixmap>
#include <QLabel>

#include "src/view/music.h"

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
    QPushButton *m_imageButton;
    bool m_isImageOne;

signals:
    void onSoloClicked();
    void onMultiplayerClicked();
    void onHowToPlayClicked();
    void onQuitClicked();
public slots:
    void onImageButtonClicked();
private:
    void setupUi();
    void connectSignals();
    void paintEvent(QPaintEvent *event);
    QLabel* createTitle();
    Music *m_music;
};
#endif // MAINMENUWINDOW_H

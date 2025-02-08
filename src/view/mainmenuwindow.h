#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H


#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>

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
};
#endif // MAINMENUWINDOW_H

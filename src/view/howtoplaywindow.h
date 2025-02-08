#ifndef HOWTOPLAYWINDOW_H
#define HOWTOPLAYWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QApplication>
#include <QScrollArea>


class HowToPlayWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HowToPlayWindow(QWidget *parent = nullptr);
    ~HowToPlayWindow();

    QPushButton *m_mainMenuButton;

signals:
    void onMainMenuClicked();

private:
    void setupUi();
    void connectSignals();
    QLabel* createTitleHowToPlayLabel();
    QLabel* createGameRulesLabel();
    QLabel* createGameControlsLabel();
};

#endif // HOWTOPLAYWINDOW_H

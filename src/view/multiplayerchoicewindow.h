#ifndef MULTIPLAYERCHOICEWINDOW_H
#define MULTIPLAYERCHOICEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QPainter>

class MultiplayerChoiceWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MultiplayerChoiceWindow(QWidget *parent = nullptr);
    ~MultiplayerChoiceWindow();

    QPushButton *m_alliesButton;
    QPushButton *m_enemiesButton;
    QPushButton *m_mainMenuButton;
signals:
    void onAlliesClicked();
    void onEnemiesClicked();
    void onMainMenuClicked();
private:
    void setupUi();
    void connectSignals();
    void paintEvent(QPaintEvent *event);
};

#endif // MULTIPLAYERCHOICEWINDOW_H

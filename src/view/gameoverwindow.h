#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QDialog>

class gameOverWindow : public QDialog
{
    Q_OBJECT

public:
    explicit gameOverWindow(QWidget *parent = nullptr);
    ~gameOverWindow();
    QPushButton *m_rejouerButton;
    QPushButton *m_menuPrincipalButton;
    void setScore(int score);

signals:
    void replayClicked();
    void backMenuClicked();
private:

    void setupUi();
    void connectSignals();
    QLabel *m_scoreLabel;
};


#endif // GAMEOVERWINDOW_H

#ifndef SOLOGAMEWINDOW_H
#define SOLOGAMEWINDOW_H

#include <QMainWindow>
#include <QPointF>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>

#include "src/view/scorewidget.h"
#include "src/view/gridscene.h"
#include "src/view/bubbleview.h"
#include "src/view/canonwidget.h"
#include "src/view/containerwidget.h"
#include "src/view/music.h"
#include "src/view/pausewindow.h"
#include "src/view/gameoverwindow.h"

class SoloGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SoloGameWindow(int widthSize, int heightSize, QWidget *parent = nullptr);
    ~SoloGameWindow();
    ScoreWidget *scoreWidget(){return m_scoreWidget;}
    GridScene *gridScene(){return m_gridScene;}
    CanonWidget *canonWidget(){return m_canonWidget;}
    ContainerWidget *containerWidget(){return m_containerWidget;}
    //pause
    PauseWindow *pauseWindow(){return m_pauseWindow;}
    void pauseWindow(PauseWindow *pause){m_pauseWindow = pause;}
    //game over
    gameOverWindow *gameOver(){return m_gameOverWindow;}
    //music
    Music *music(){return m_music;}
    void music(Music *m){m_music=m;}
    //retour
    QPushButton *retour(){return m_retour;}
    //pause
    QPushButton *pause(){return m_pause;}
    void shootBubble(int angle);

signals:
    void onRetourClicked();
    void onPauseClicked();

private:
    ScoreWidget *m_scoreWidget;
    GridScene *m_gridScene;
    CanonWidget *m_canonWidget;
    ContainerWidget *m_containerWidget;
    Music *m_music;
    QPushButton *m_retour;
    QPushButton *m_pause;
    PauseWindow *m_pauseWindow;
    gameOverWindow *m_gameOverWindow;
    void connectSignals();
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void setupUi();
    void keyPressEvent(QKeyEvent *event);

};

#endif // SOLOGAMEWINDOW_H

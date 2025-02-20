#ifndef ENEMIESGAMEWINDOW_H
#define ENEMIESGAMEWINDOW_H

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

class EnemiesGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EnemiesGameWindow(int widthSize, int heightSize, QWidget *parent = nullptr);
    ~EnemiesGameWindow();
    ScoreWidget *scoreWidget(){return m_scoreWidget;}
    ScoreWidget *scoreWidget2(){return m_scoreWidget2;}
    GridScene *gridScene(){return m_gridScene;}
    CanonWidget *canonWidget(){return m_canonWidget;}
    CanonWidget *canonWidget2(){return m_canonWidget2;}
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



signals:
    void onRetourClicked1();
    void onPauseClicked1();


private:
    ScoreWidget *m_scoreWidget;
    ScoreWidget *m_scoreWidget2;

    GridScene *m_gridScene;
    CanonWidget *m_canonWidget;
    CanonWidget *m_canonWidget2;
    ContainerWidget *m_containerWidget;
    ContainerWidget *m_containerWidget2;
    QPushButton *m_retour;
    QPushButton *m_pause;
    PauseWindow *m_pauseWindow;
    gameOverWindow *m_gameOverWindow;
    Music *m_music;
    void connectSignals();
    void paintEvent(QPaintEvent *event);
    void setupUi();
    void keyPressEvent(QKeyEvent *event);
};

#endif // ENEMIESGAMEWINDOW_H

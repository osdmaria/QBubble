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

class EnemiesGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EnemiesGameWindow(int widthSize, int heightSize, QWidget *parent = nullptr);
    ~EnemiesGameWindow();
    ScoreWidget *scoreWidget(){return m_scoreWidget;}
    ScoreWidget *scoreWidget2(){return m_scoreWidget2;}
    GridScene *gridScene(){return m_gridScene;}
    CanonModel *cannonModel(){return m_canonModel;}
    CanonModel *cannonModel2(){return m_canonModel2;}
    CanonWidget *canonWidget(){return m_canonWidget;}
    CanonWidget *canonWidget2(){return m_canonWidget2;}
    ContainerWidget *containerWidget(){return m_containerWidget;}
    QPushButton *m_retour;
    QPushButton *m_pause;
    void shootBubble(int angle);

private:
    void setupUi();
    void keyPressEvent(QKeyEvent *event);

signals:
    void onRetourClicked1();
    void onPauseClicked1();


private:
    ScoreWidget *m_scoreWidget;
    ScoreWidget *m_scoreWidget2;

    GridScene *m_gridScene;
    CanonModel *m_canonModel;
    CanonModel *m_canonModel2;
    CanonWidget *m_canonWidget;
    CanonWidget *m_canonWidget2;
    ContainerWidget *m_containerWidget;
    ContainerWidget *m_containerWidget2;
    Music *m_music;
    void connectSignals();
    void paintEvent(QPaintEvent *event);
};

#endif // ENEMIESGAMEWINDOW_H

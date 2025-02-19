#ifndef ALLIESGAMEWINDOW_H
#define ALLIESGAMEWINDOW_H

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


class AlliesGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlliesGameWindow(int widthSize, int heightSize, QWidget *parent = nullptr);
    ~AlliesGameWindow();
    ScoreWidget *scoreWidget(){return m_scoreWidget;}

    GridScene *gridScene(){return m_gridScene;}
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
    GridScene *m_gridScene;

    //CanonModel *m_canonModel;
    //CanonModel *m_canonModel2;
    CanonWidget *m_canonWidget;
    CanonWidget *m_canonWidget2;
    ContainerWidget *m_containerWidget;
    ContainerWidget *m_containerWidget2;
    Music *m_music;
    void connectSignals();
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // ALLIESGAMEWINDOW_H

#ifndef ENEMIESGAMEWINDOW_H
#define ENEMIESGAMEWINDOW_H

#include <QMainWindow>
#include <QPointF>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QLabel>

#include "src/view/scorewidget.h"
#include "src/view/gridscene.h"
#include "src/view/bubbleview.h"
#include "src/view/cannonwidget.h"
#include "src/view/containerwidget.h"

class EnemiesGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EnemiesGameWindow(QWidget *parent = nullptr);
    ~EnemiesGameWindow();
    ScoreWidget *scoreWidget(){return m_scoreWidget;}
    ScoreWidget *scoreWidget2(){return m_scoreWidget2;}
    GridScene *gridScene(){return m_gridScene;}
    CannonWidget *cannonWidget(){return m_cannonWidget;}
    CannonWidget *cannonWidget2(){return m_cannonWidget2;}
    ContainerWidget *containerWidget(){return m_containerWidget;}

private:
    void setupUi();

signals:


private:
    ScoreWidget *m_scoreWidget;
    ScoreWidget *m_scoreWidget2;
    GridScene *m_gridScene;
    CannonWidget *m_cannonWidget;
    CannonWidget *m_cannonWidget2;
    QHBoxLayout *cannonLayout;
    ContainerWidget *m_containerWidget;
};

#endif // ENEMIESGAMEWINDOW_H

#ifndef ALLIESGAMEWINDOW_H
#define ALLIESGAMEWINDOW_H

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
//#include "src/view/cannonwidget.h"
#include "src/view/containerwidget.h"


class AlliesGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlliesGameWindow(int widthSize, int heightSize, QWidget *parent = nullptr);
    ~AlliesGameWindow();
    ScoreWidget *scoreWidget(){return m_scoreWidget;}
    GridScene *gridScene(){return m_gridScene;}
    //CannonWidget *cannonWidget(){return m_cannonWidget;}
    //CannonWidget *cannonWidget2(){return m_cannonWidget2;}
    ContainerWidget *containerWidget(){return m_containerWidget;}

private:
    void setupUi();

signals:


private:
    ScoreWidget *m_scoreWidget;
    //GridModel *m_gridModel;
    GridScene *m_gridScene;
    //CannonWidget *m_cannonWidget;
    //CannonWidget *m_cannonWidget2;
    ContainerWidget *m_containerWidget;
};

#endif // ALLIESGAMEWINDOW_H

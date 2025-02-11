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

#include "src/view/scorewidget.h"
#include "src/view/gridscene.h"
#include "src/view/bubbleview.h"
#include "src/view/cannonwidget.h"
#include "src/view/containerwidget.h"

class SoloGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SoloGameWindow(QWidget *parent = nullptr);
    ~SoloGameWindow();
    ScoreWidget *scoreWidget(){return m_scoreWidget;}
    GridScene *gridScene(){return m_gridScene;}
    CannonWidget *cannonWidget(){return m_cannonWidget;}
    ContainerWidget *containerWidget(){return m_containerWidget;}
    QPushButton *m_retour;
    QPushButton *m_pause;

private:
    void setupUi();

signals:
    void onRetourClicked();
    void onPauseClicked();

private:
    ScoreWidget *m_scoreWidget;
    GridModel *m_gridModel;
    GridScene *m_gridScene;
    CannonWidget *m_cannonWidget;
    ContainerWidget *m_containerWidget;
    void connectSignals();
};

#endif // SOLOGAMEWINDOW_H

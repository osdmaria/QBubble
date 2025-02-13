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
#include "src/view/canonwidget.h"
#include "src/view/containerwidget.h"

class SoloGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SoloGameWindow(QWidget *parent = nullptr);
    ~SoloGameWindow();
    ScoreWidget *scoreWidget(){return m_scoreWidget;}
    GridScene *gridScene(){return m_gridScene;}
    CanonWidget *CannonWidget(){return m_cannonWidget;}
    ContainerWidget *containerWidget(){return m_containerWidget;}
    QPushButton *m_retour;
    QPushButton *m_pause;

private:
    void setupUi();
    void keyPressEvent(QKeyEvent *event);

signals:
    void onRetourClicked();
    void onPauseClicked();

private:
    ScoreWidget *m_scoreWidget;
    GridModel *m_gridModel;
    CanonModel *m_canonModel;
    GridScene *m_gridScene;
    ContainerWidget *m_containerWidget;
    CanonWidget *m_cannonWidget;
    void connectSignals();
};

#endif // SOLOGAMEWINDOW_H

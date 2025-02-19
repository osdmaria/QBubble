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
    QPushButton *m_retour;
    QPushButton *m_pause;
    void shootBubble(int angle);

private:
    void setupUi();
    void keyPressEvent(QKeyEvent *event);

signals:
    void onRetourClicked();
    void onPauseClicked();


private:
    ScoreWidget *m_scoreWidget;
    GridScene *m_gridScene;
    CanonWidget *m_canonWidget;
    ContainerWidget *m_containerWidget;
    Music *m_music;
    void connectSignals();
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);

};

#endif // SOLOGAMEWINDOW_H

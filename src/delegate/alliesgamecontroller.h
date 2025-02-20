#ifndef ALLIESGAMECONTROLLER_H
#define ALLIESGAMECONTROLLER_H

#include <QObject>

#include "src/view/alliesgamewindow.h"

#include "src/model/scoremodel.h"
#include "src/model/scoremodel.h"
#include "src/model/containermodel.h"
#include "src/model/hexgridmodel.h"
#include "src/model/canonmodel.h"
#include "src/model/generatormodel.h"
#include "src/model/gridinitializer.h"
#include "src/model/burstcalculator.h"
#include "src/view/levelmenu.h"
#include "src/view/mainmenuwindow.h"
#include "src/view/pausewindow.h"

#include <QApplication>
#include <QPushButton>
#include <QScreen>
#include <QGuiApplication>

class AlliesGameController : public QObject
{
    Q_OBJECT
public:
    explicit AlliesGameController(AlliesGameWindow *alliesGameView,QObject *parent = nullptr);
    ~AlliesGameController();
    AlliesGameWindow *alliesGameView(){return m_alliesGameView;}
    ScoreModel *scoreModel(){return m_scoreModel;}
    ContainerModel *containerModel(){return m_containerModel;}
    ContainerModel *containerModel2(){return m_containerModel2;}
    GeneratorModel *bubbleGeneratorModel(){return m_bubbleGeneratorModel;}
    HexGridModel *hexGridModel(){return m_hexGridModel;}
    CanonModel *canonModel(){return m_canonModel;}
    CanonModel *canonModel2(){return m_canonModel2;}
    GridInitializer *gridInitializer(){return m_gridInitializer;}
    LevelMenu *levelMenu(){return m_levelMenu;}

    void connectGenerator();
    void connectContainer();
    void connectCannon();
    void connectHexGrid();
    void connectBurstCalculator();
    void connectGridScene();
    void connectScore();


    void start(int level);
    void gameOver();
    void gameWon();

    void initContainer();
    void loadLevel(int level);
    void startLevelSelection();
signals:
    void menuLauched();
    void generateSingleBubble();
    void generateBubblesRow(int size);

    void shotOrder();
    void burstFromColoredBubble(int row, int col);
    void burstFromExplosiveBubble(int row, int col);
    void burstDisconnectedBubbles();
    void burst(QVector<Bubble*> vec);

    void showGameOver();

public slots:
    void handleLastRow();
    void handleShot();
    void handleContainer();
    void handleLoadCannon();
    void handleBubblesBurst(Bubble *b);
    void handleAmountDestroyedBubbles(int amount);

private:
    AlliesGameWindow *m_alliesGameView;
    ScoreModel *m_scoreModel;
    ContainerModel *m_containerModel;
    ContainerModel *m_containerModel2;
    GeneratorModel *m_bubbleGeneratorModel;
    HexGridModel *m_hexGridModel;
    GridInitializer *m_gridInitializer;
    CanonModel *m_canonModel;
    CanonModel *m_canonModel2;
    BurstCalculator *m_burstCalculator;
    LevelMenu *m_levelMenu;

    bool m_running = false;
    bool m_gameOver = false;
    bool m_gameWon = false;
    int m_failedShots = 0;
};

#endif // ALLIESGAMECONTROLLER_H

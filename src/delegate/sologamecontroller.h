#ifndef SOLOGAMECONTROLLER_H
#define SOLOGAMECONTROLLER_H

#include <QObject>

#include "src/view/sologamewindow.h"
#include "src/model/scoremodel.h"
#include "src/model/containermodel.h"
#include "src/model/hexgridmodel.h"
#include "src/model/canonmodel.h"
#include "src/model/generatormodel.h"
#include "src/model/gridinitializer.h"
#include "src/model/burstcalculator.h"
#include "src/view/levelmenu.h"
#include "src/view/gameoverwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QScreen>
#include <QGuiApplication>

class SoloGameController : public QObject
{
    Q_OBJECT
public:
    explicit SoloGameController(SoloGameWindow *soloGameView, QObject *parent = nullptr);
    ~SoloGameController();
    SoloGameWindow *soloGameView(){return m_soloGameView;}
    ScoreModel *scoreModel(){return m_scoreModel;}
    ContainerModel *containerModel(){return m_containerModel;}
    GeneratorModel *bubbleGeneratorModel(){return m_bubbleGeneratorModel;}
    HexGridModel *hexGridModel(){return m_hexGridModel;}
    CanonModel *canonModel(){return m_canonModel;}
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
    SoloGameWindow *m_soloGameView;
    ScoreModel *m_scoreModel;
    ContainerModel *m_containerModel;
    GeneratorModel *m_bubbleGeneratorModel;
    HexGridModel *m_hexGridModel;
    GridInitializer *m_gridInitializer;
    CanonModel *m_canonModel;
    BurstCalculator *m_burstCalculator;
    LevelMenu *m_levelMenu;

    bool m_running = false;
    bool m_gameOver = false;
    bool m_gameWon = false;
    int m_failedShots = 0;
};

#endif // SOLOGAMECONTROLLER_H

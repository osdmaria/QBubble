#ifndef ENEMIESGAMECONTROLLER_H
#define ENEMIESGAMECONTROLLER_H

#include <QObject>

#include "src/view/enemiesgamewindow.h"
#include "src/model/scoremodel.h"
#include "src/model/containermodel.h"
#include "src/model/hexgridmodel.h"
#include "src/model/canonmodel.h"
#include "src/model/generatormodel.h"
#include "src/model/gridinitializer.h"
#include "src/model/burstcalculator.h"
#include "src/view/levelmenu.h"

#include <QApplication>
#include <QPushButton>
#include <QScreen>
#include <QGuiApplication>

class EnemiesGameController : public QObject
{
    Q_OBJECT
public:
    explicit EnemiesGameController(EnemiesGameWindow *enemiesGameView, QObject *parent = nullptr);
    ~EnemiesGameController();
    EnemiesGameWindow *enemiesGameView(){return m_enemiesGameView;}
    ScoreModel *scoreModel(){return m_scoreModel;}
    ScoreModel *scoreModel2(){return m_scoreModel2;}
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
    EnemiesGameWindow *m_enemiesGameView;
    ScoreModel *m_scoreModel;
    ScoreModel *m_scoreModel2;
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

#endif // ENEMIESGAMECONTROLLER_H

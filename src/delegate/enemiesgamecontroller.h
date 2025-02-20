#ifndef ENEMIESGAMECONTROLLER_H
#define ENEMIESGAMECONTROLLER_H

#include <QObject>

#include "src/view/enemiesgamewindow.h"

#include "src/model/scoremodel.h"
#include "src/model/containermodel.h"
#include "src/view/mainmenuwindow.h"
#include "src/model/hexgridmodel.h"
#include "src/model/canonmodel.h"
#include "src/model/generatormodel.h"
#include "src/view/pausewindow.h"
#include "src/model/gridinitializer.h"
#include "src/model/burstcalculator.h"

#include <QApplication>
#include <QPushButton>
#include <QScreen>
#include <QGuiApplication>

class EnemiesGameController : public QObject
{
    Q_OBJECT
public:
    explicit EnemiesGameController(EnemiesGameWindow *enemiesGameView,MainMenuWindow *mainMenuView, QObject *parent = nullptr);
    ~EnemiesGameController();
    EnemiesGameWindow *enemiesGameView(){return m_enemiesGameView;}
    ScoreModel *scoreModel(){return m_scoreModel;}
    MainMenuWindow *mainMenuWindow(){return m_mainMenuView;}
    ContainerModel *containerModel(){return m_containerModel;}
    GeneratorModel *bubbleGeneratorModel(){return m_bubbleGeneratorModel;}
    HexGridModel *hexGridModel(){return m_hexGridModel;}
    CanonModel *canonModel(){return m_canonModel;}
    GridInitializer *gridInitializer(){return m_gridInitializer;}

    void connectGenerator();
    void connectContainer();
    void connectCannon();
    void connectHexGrid();
    void connectBurstCalculator();
    void connectGridScene();
    void connectScore();


    void start();
    void gameOver();
    void gameWon();

    void initContainer();
    void loadLevel(int level);

signals:
    void menuLauched();
    void generateSingleBubble();
    void generateBubblesRow(int size);
    void openMainMenuFromPause();

    void shotOrder();
    void burstFromColoredBubble(int row, int col);
    void burstFromExplosiveBubble(int row, int col);
    void burstDisconnectedBubbles();

    void burst(QVector<Bubble*> vec);

public slots:
    void openMainMenu();
    void showPauseWindow();
    void handleLastRow();
    void handleShot();
    void handleContainer();
    void handleLoadCannon();
    void handleBubblesBurst(Bubble *b);
    void handleAmountDestroyedBubbles(int amount);


private:
    void connectSignalsButttons1();
    EnemiesGameWindow *m_enemiesGameView;
    ScoreModel *m_scoreModel;
    ContainerModel *m_containerModel;
    MainMenuWindow *m_mainMenuView;
    GeneratorModel *m_bubbleGeneratorModel;
    HexGridModel *m_hexGridModel;
    GridInitializer *m_gridInitializer;
    CanonModel *m_canonModel;
    PauseWindow *m_pauseWindow;
    BurstCalculator *m_burstCalculator;

    bool m_running = false;
    bool m_gameOver = false;
    bool m_gameWon = false;
    int m_failedShots = 0;
};

#endif // ENEMIESGAMECONTROLLER_H

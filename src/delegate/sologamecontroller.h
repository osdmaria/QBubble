#ifndef SOLOGAMECONTROLLER_H
#define SOLOGAMECONTROLLER_H

#include <QObject>

#include "src/view/sologamewindow.h"

#include "src/model/scoremodel.h"
#include <QApplication>
#include "src/model/containermodel.h"
#include "src/view/mainmenuwindow.h"
#include "src/model/hexgridmodel.h"
#include "src/model/canonmodel.h"
#include "src/model/generatormodel.h"
#include "src/view/pausewindow.h"

#include <QPushButton>
#include <QScreen>
#include <QGuiApplication>

class SoloGameController : public QObject
{
    Q_OBJECT
public:
    explicit SoloGameController(SoloGameWindow *soloGameView,MainMenuWindow *mainMenuView, QObject *parent = nullptr);
    ~SoloGameController();
    SoloGameWindow *soloGameView(){return m_soloGameView;}
    ScoreModel *scoreModel(){return m_scoreModel;}
    MainMenuWindow *mainMenuWindow(){return m_mainMenuView;}
    ContainerModel *containerModel(){return m_containerModel;}
    GeneratorModel *bubbleGeneratorModel(){return m_bubbleGeneratorModel;}
    HexGridModel *hexGridModel(){return m_hexGridModel;}
    CanonModel *canonModel(){return m_canonModel;}

    void connectGenerator();
    void connectContainer();
    void connectCannon();
    void connectHexGrid();
    void connectBurstCalculator();
    void connectGridScene();

    void start();

signals:
    void menuLauched();
    void generateSingleBubble();
    void generateBubblesRow(int size);
    void openMainMenuFromPause();

private slots:
    void updateScore(int x);
public slots:
    void openMainMenu();
    void showPauseWindow();

private:
    void connectSignalsButttons();
    SoloGameWindow *m_soloGameView;
    ScoreModel *m_scoreModel;
    ContainerModel *m_containerModel;
    MainMenuWindow *m_mainMenuView;
    GeneratorModel *m_bubbleGeneratorModel;
    HexGridModel *m_hexGridModel;
    CanonModel *m_canonModel;
    pausewindow *m_pauseWindow;
};

#endif // SOLOGAMECONTROLLER_H

#ifndef SOLOGAMECONTROLLER_H
#define SOLOGAMECONTROLLER_H

#include <QObject>

#include "src/view/sologamewindow.h"

#include "src/model/scoremodel.h"
#include <QApplication>
#include "src/model/containermodel.h"
#include "src/view/mainmenuwindow.h"

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
signals:
    void menuLauched();

private slots:
    void updateScore(int x);
public slots:
    void openMainMenu();

private:
    SoloGameWindow *m_soloGameView;
    ScoreModel *m_scoreModel;
    ContainerModel *m_containerModel;
    void connectSignalsButttons();
    MainMenuWindow *m_mainMenuView;
};

#endif // SOLOGAMECONTROLLER_H

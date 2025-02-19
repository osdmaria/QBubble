#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "src/delegate/windowscontroller.h"
#include "src/delegate/sologamecontroller.h"
#include "src/delegate/enemiesgamecontroller.h"
#include "src/delegate/alliesgamecontroller.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();

private slots:
    void soloLaunched();
    void soloEnded();
    void enemieLaunched();
    void enemieEnded();
    void allieLaunched();
    void allieEnded();

private:
    WindowsController *m_windowsController;
    SoloGameController *m_soloGameController;
    EnemiesGameController *m_enemieGameController;
    AlliesGameController *m_alliesGameController;
};

#endif // MAINCONTROLLER_H

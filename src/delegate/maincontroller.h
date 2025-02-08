#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "src/delegate/windowscontroller.h"
#include "src/delegate/sologamecontroller.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();

private slots:
    void soloLaunched();
    void soloEnded();

private:
    WindowsController *m_windowsController;
    SoloGameController *m_soloGameController;
};

#endif // MAINCONTROLLER_H

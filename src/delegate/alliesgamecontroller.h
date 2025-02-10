#ifndef ALLIESGAMECONTROLLER_H
#define ALLIESGAMECONTROLLER_H

#include <QObject>

#include "src/view/alliesgamewindow.h"

#include "src/model/scoremodel.h"
#include "src/model/containermodel.h"

class AlliesGameController : public QObject
{
    Q_OBJECT
public:
    explicit AlliesGameController(AlliesGameWindow *alliesGameView, QObject *parent = nullptr);
    ~AlliesGameController();
    AlliesGameWindow *alliesGameView(){return m_alliesGameView;}
    ScoreModel *scoreModel(){return m_scoreModel;}

private slots:
    void updateScore(int x);

private:
    AlliesGameWindow *m_alliesGameView;
    ScoreModel *m_scoreModel;
    ContainerModel *m_containerModel;




};

#endif // ALLIESGAMECONTROLLER_H

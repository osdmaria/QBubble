#ifndef ENEMIESGAMECONTROLLER_H
#define ENEMIESGAMECONTROLLER_H

#include <QObject>

#include "src/view/enemiesgamewindow.h"

#include "src/model/scoremodel.h"
#include "src/model/containermodel.h"

class EnemiesGameController : public QObject
{
    Q_OBJECT
public:
    explicit EnemiesGameController(EnemiesGameWindow *enemiesGameView, QObject *parent = nullptr);
    ~EnemiesGameController();
    EnemiesGameWindow *enemiesGameView(){return m_enemiesGameView;}
    ScoreModel *scoreModel(){return m_scoreModel;}


private slots:
    void updateScore(int x);

private:
    EnemiesGameWindow *m_enemiesGameView;
    ScoreModel *m_scoreModel;
    ContainerModel *m_containerModel;


};

#endif // ENEMIESGAMECONTROLLER_H

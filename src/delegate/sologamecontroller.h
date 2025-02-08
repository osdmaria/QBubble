#ifndef SOLOGAMECONTROLLER_H
#define SOLOGAMECONTROLLER_H

#include <QObject>

#include "src/view/sologamewindow.h"

#include "src/model/scoremodel.h"
#include "src/model/containermodel.h"


class SoloGameController : public QObject
{
    Q_OBJECT
public:
    explicit SoloGameController(SoloGameWindow *soloGameView, QObject *parent = nullptr);
    ~SoloGameController();
    SoloGameWindow *soloGameView(){return m_soloGameView;}
    ScoreModel *scoreModel(){return m_scoreModel;}


private slots:
    void updateScore(int x);

private:
    SoloGameWindow *m_soloGameView;
    ScoreModel *m_scoreModel;
    ContainerModel *m_containerModel;



};

#endif // SOLOGAMECONTROLLER_H

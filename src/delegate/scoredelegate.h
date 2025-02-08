#ifndef SCOREDELEGATE_H
#define SCOREDELEGATE_H

#include <QObject>

#include "src/view/scorewidget.h"
#include "src/model/scoremodel.h"

class ScoreDelegate : public QObject
{
    Q_OBJECT
public:
    explicit ScoreDelegate(ScoreWidget *scoreWidget, ScoreModel *scoreModel, QObject *parent = nullptr);

private slots:
    void updateScore(int x);

private:
    ScoreWidget *m_scoreWidget;
    ScoreModel *m_scoreModel;
};

#endif // SCOREDELEGATE_H

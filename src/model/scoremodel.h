#ifndef SCOREMODEL_H
#define SCOREMODEL_H

#include <QObject>
#include "bubble.h"

class ScoreModel : public QObject
{
    Q_OBJECT
public:
    explicit ScoreModel(QObject *parent = nullptr);
    void addPoints(int x);
    void resetScore();

signals:
    void scoreChanged(int x);
    void calculScoreHandled(QVector<Bubble*> vec);

public slots:
    void calculScore(QVector<Bubble*> vec);

private:
    int m_score;
};

#endif // SCOREMODEL_H

#ifndef SCOREMODEL_H
#define SCOREMODEL_H

#include <QObject>

class ScoreModel : public QObject
{
    Q_OBJECT
public:
    explicit ScoreModel(QObject *parent = nullptr);
    void addPoints(int x);
    void resetScore();

signals:
    void scoreChanged(int x);

private:
    int m_score;
};

#endif // SCOREMODEL_H

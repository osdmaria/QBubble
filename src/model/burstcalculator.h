#ifndef BURSTCALCULATOR_H
#define BURSTCALCULATOR_H

#include <QObject>
#include <QSet>
#include <QQueue>

#include "src/model/hexgridmodel.h"

class BurstCalculator : public QObject
{
    Q_OBJECT

public:
    BurstCalculator(HexGridModel *hexGrid, QObject *parent = nullptr);
    QVector<Bubble*> getConnectedBubblesColor(int row, int col);
    QVector<Bubble*> getConnectedBubblesExplosion(int row, int col);
    QVector<Bubble*> getDisconnectedBubbles();

signals:
    void bubblesToBurst(QVector<Bubble*> vec);
    void bubblesDisconnected(QVector<Bubble*> vec);
    void amountDestroyedBubbles(int amount);

public slots:
    void burstFromColoredBubble(int row, int col);
    void burstFromExplosiveBubble(int row, int col);
    void burstDisconnectedBubbles();

private:
    HexGridModel *m_hexGrid = nullptr;
    int m_destroyedBubbles = 0;
};

#endif // BURSTCALCULATOR_H

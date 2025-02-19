#ifndef CANONMODEL_H
#define CANONMODEL_H

#include <QObject>
#include <QDebug>
#include "src/model/coloredbubble.h"
#include "src/model/explosivebubble.h"
#include "src/model/indestructiblebubble.h"
#include "src/model/hexgridmodel.h"

class CanonModel : public QObject
{
    Q_OBJECT

public:
    explicit CanonModel(QObject *parent = nullptr);
    ~CanonModel();
    qreal getAngle() const;
    void currentBubble(Bubble *bubble) {m_currentBubble = bubble;}
    Bubble *currentBubble(){return m_currentBubble;}


public slots:
    void updateAngle(int direction);
    void loadBubble(Bubble *b);
    void fire();

signals:
    void angleChanged(qreal newAngle);
    void cannonLoaded();
    void cannonFired(int angle, Bubble *b);

private:
    qreal angle;
    Bubble *m_currentBubble = nullptr;
    HexGridModel *m_hexGrid;

};

#endif // CANONMODEL_H

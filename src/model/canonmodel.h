#ifndef CANONMODEL_H
#define CANONMODEL_H

#include <QObject>
#include <QDebug>
#include "src/model/coloredbubble.h"
#include "src/model/explosivebubble.h"
#include "src/model/indestructiblebubble.h"

class CanonModel : public QObject
{
    Q_OBJECT

public:
    explicit CanonModel(QObject *parent = nullptr);
    ~CanonModel();
    qreal getAngle() const;
    void updateAngle(int direction);

    void currentBubble(Bubble *bubble) {m_currentBubble = bubble;}
    Bubble *currentBubble(){return m_currentBubble;}
    void fire();

public slots:
    void loadBubble(Bubble *b);

signals:
    void angleChanged(qreal newAngle); // Emitted when the angle changes
    void BubbleShoot(int angle);        // Emitted when the bubble is shot
    void cannonFired(Bubble *b);

private:
    qreal angle;
    Bubble *m_currentBubble;
};

#endif // CANONMODEL_H

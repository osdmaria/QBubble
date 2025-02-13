#ifndef CANONMODEL_H
#define CANONMODEL_H

#include <QObject>
#include <QDebug>

class CanonModel : public QObject
{
    Q_OBJECT

public:
    explicit CanonModel(QObject *parent = nullptr);

    qreal getAngle() const;
    void updateAngle(int direction);

signals:
    void angleChanged(qreal newAngle); // Emitted when the angle changes
    void BubbleShoot(int angle);        // Emitted when the bubble is shot

private:
    qreal angle;
};

#endif // CANONMODEL_H

#include "canonmodel.h"

CanonModel::CanonModel(QObject *parent) : QObject(parent), angle(90) {}

qreal CanonModel::getAngle() const {
    return angle;
}

void CanonModel::updateAngle(int direction) {
    if (direction == 1 && angle > 25) {
        angle -= 6; // Left arrow -> decrease angle
    } else if (direction == -1 && angle < 155) {
        angle += 6; // Right arrow -> increase angle
    }

    // Emit the new angle
    emit angleChanged(angle);
}

#ifndef INDESTRUCTIBLEBUBBLE_H
#define INDESTRUCTIBLEBUBBLE_H

#include "src/model/bubble.h"

class IndestructibleBubble : public Bubble
{
public:
    IndestructibleBubble(QObject *parent = nullptr);

    void printType() override;
    QString type() const override {return "indestructible";}

    bool isColored() override;
    bool isDestructible() override;
    bool isExplosive() override;
};

#endif // INDESTRUCTIBLEBUBBLE_H

#ifndef EXPLOSIVEBUBBLE_H
#define EXPLOSIVEBUBBLE_H

#include "src/model/bubble.h"

class ExplosiveBubble : public Bubble
{
public:
    ExplosiveBubble(int radiusExplosion=1, QObject *parent = nullptr);

    void printType() override;
    QString type() const override {return "explosive";}

    bool isColored() override;
    bool isDestructible() override;
    bool isExplosive() override;

    int explosionRadius() const {return m_explosionRadius;}
    void explosionRadius(int r){m_explosionRadius = r;}
    int explosionRadius() {return m_explosionRadius;}

private:
    int m_explosionRadius ;
};

#endif // EXPLOSIVEBUBBLE_H

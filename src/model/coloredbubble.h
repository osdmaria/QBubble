#ifndef COLOREDBUBBLE_H
#define COLOREDBUBBLE_H

#include "src/model/bubble.h"


class ColoredBubble : public Bubble
{
    Q_OBJECT

public:
    explicit ColoredBubble(const QString &color, QObject *parent = nullptr);

    void printType() override;
    QString type() const override {return m_color;}

    bool isColored() override;
    bool isDestructible() override;
    bool isExplosive() override;

    QString color() const { return m_color; }
    void setColor(const QString &c) { m_color = c; }

    bool sameColor(ColoredBubble *b){return m_color.compare(b->color())==0;}

signals:

private:
    QString m_color;
};

#endif // COLOREDBUBBLE_H

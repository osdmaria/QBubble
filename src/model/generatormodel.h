#ifndef GENERATORMODEL_H
#define GENERATORMODEL_H

#include <QObject>
#include <vector>
#include <memory>
#include <random>
#include "src/model/coloredbubble.h"
#include "src/model/explosivebubble.h"
#include "src/model/indestructiblebubble.h"

class GeneratorModel: public QObject
{
    Q_OBJECT
public:
    explicit GeneratorModel(QObject *parent = nullptr);
    Bubble *genTest();

public slots:
    void genSingleBubble();
    void genBubblesRow(int size);

signals:
    void bubbleGenerated(Bubble *b);
    void bubblesRowGenerated(QVector<Bubble*> *bubbleLine);

private:
    Bubble *genRandomBubble();
    Bubble *genRandomOnlyColoredBubble();
};

#endif // GENERATORMODEL_H

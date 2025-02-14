#include "generatormodel.h"

GeneratorModel::GeneratorModel(QObject *parent) :
    QObject{parent}
{}


void GeneratorModel::genSingleBubble(){
    Bubble *b = genRandomBubble();
    qDebug() << "Une bulle est générée";
    emit bubbleGenerated(b);
}

void GeneratorModel::genBubblesRow(int size) {
    QVector<Bubble*> *bubblesRow = new QVector<Bubble*>;
    for (int i = 0; i < size; i++) {
        bubblesRow->push_back(genRandomOnlyColoredBubble());
    }
    emit bubblesRowGenerated(bubblesRow);
}

Bubble *GeneratorModel::genRandomBubble() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist1(0, 9);
    std::uniform_int_distribution<> dist2(0, 3);

    int rand1 = dist1(gen);

    if (rand1 < 8) {
        int rand2 = dist2(gen);
        switch (rand2) {
        case 0: return new ColoredBubble("bordeaux");
        case 1: return new ColoredBubble("green");
        case 2: return new ColoredBubble("lightblue");
        case 3: return new ColoredBubble("brown");
        }
    } else if (rand1 < 9) {
        return new IndestructibleBubble();
    }
    return new ExplosiveBubble(2);
}

Bubble *GeneratorModel::genRandomOnlyColoredBubble() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 3);

    int rand = dist(gen);
    switch (rand) {
    case 0: return new ColoredBubble("bordeaux");
    case 1: return new ColoredBubble("green");
    case 2: return new ColoredBubble("lightblue");
    case 3: return new ColoredBubble("brown");
    default: return nullptr;
    }
}

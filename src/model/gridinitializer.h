#ifndef GRIDINITIALIZER_H
#define GRIDINITIALIZER_H

#include <QObject>
#include "hexgridmodel.h"
#include "coloredbubble.h"

class GridInitializer : public QObject
{
public:
    GridInitializer(HexGridModel *hexGrid, QObject *parent = nullptr);
    void initLevel1();
    void initLevel2();
    void initLevel3();

    int levels(){return m_nLevels;}

private:
    HexGridModel *m_hexGridModel;
    int m_nLevels = 1;

};

#endif // GRIDINITIALIZER_H

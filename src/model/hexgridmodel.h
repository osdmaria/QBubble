#ifndef HEXGRIDMODEL_H
#define HEXGRIDMODEL_H

#include <QObject>
#include <QVector>
#include "src/model/coloredbubble.h"
#include "src/model/explosivebubble.h"
#include "src/model/indestructiblebubble.h"

class HexGridModel : public QObject
{
    Q_OBJECT
public:
    explicit HexGridModel(int width, int height, int radius, QPointF gridSceneOrigin, QObject *parent = nullptr);
    ~HexGridModel();
    QVector<int> cartesianToMatrix2D(qreal x, qreal y);
    QPoint matrix2DToCartesian(int row, int col);
    bool isEmpty(int row, int col);
    void addBubbleCartesian(qreal x, qreal y, Bubble *b);
    void addBubbleMatrix(int row, int col, Bubble *b);
    void removeBubbleMatrix(int row, int col);
    void removeBubblesMatrix(QVector<Bubble*> vec);
    void normalizeCoordinatesIntoLocal(qreal &x, qreal &y);
    void normalizeCoordinatesIntoGlobal(qreal &x, qreal &y);
    QVector<Bubble*> getNeighbors(int row, int col);
    QVector<Bubble*> getNeighborsDestructible(int row, int col);
    QVector<Bubble*> getNeighborsSameColor(int row, int col);
    bool isOutOfGrid(int row, int col);
    void gripWithOffset(int &row, int &col);
    bool lastRowEmpty();
    bool rowEmpty(int r);
    void moveBubbleDown(int row, int col);
    bool isValid(int row, int col);


    Bubble *bubble(int row, int col){return m_matrix2D[row][col];}
    qreal hexRadius()const {return m_hexRadius;}
    int width()const {return m_width;}
    int height()const {return m_height;}
    int ncols()const {return m_ncols;}
    int nrows()const {return m_nrows;}
    QVector<QVector<Bubble*>> matrix2D() {return m_matrix2D;}
    void printGridConsole();

    public slots:
        void addRow(QVector<Bubble*> *bubbleLine);

    signals:
        void bubblesPositionsUpdated();
        void bubbleDestroyed(Bubble *b);
        void bubbleAdded(Bubble *b);
        void bubbleMoved(int prevRow, int prevCol, Bubble *b);

private:
    QVector<QVector<Bubble*>> m_matrix2D;
    int m_width;
    int m_height;
    int m_nrows, m_ncols;
    QPointF m_gridSceneOrigin;
    int m_hexRadius;
};

#endif // HEXGRIDMODEL_H





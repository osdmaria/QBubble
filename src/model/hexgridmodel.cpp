#include "hexgridmodel.h"
#include <QDebug>

HexGridModel::HexGridModel(int width, int height, int radius, QPointF gridSceneOrigin, QObject *parent)
    : QObject{parent}, m_width{width}, m_height{height}, m_gridSceneOrigin{gridSceneOrigin}
{
    m_hexRadius = radius;
    //m_hexRadius = 30;
    m_ncols = m_width/(2*m_hexRadius) +1;
    m_nrows = qRound(m_height/(std::sqrt(3)*m_hexRadius));
    qDebug()<<"rows:"<<m_nrows<<"cols:"<<m_ncols<<"bubbles/row:"<<m_ncols-1;
    m_matrix2D = QVector<QVector<Bubble*>>(m_nrows, QVector<Bubble*>(m_ncols, nullptr));

}

HexGridModel::~HexGridModel(){
    for (auto& row : m_matrix2D) {
        for (auto& bubble : row)
            delete bubble;
        row.clear();
    }
    m_matrix2D.clear();
}

void HexGridModel::printGridConsole() {
    const int cellWidth = 10;

    for (int i = 0; i < m_matrix2D.size(); i++) {
        QString line;
        for (int j = 0; j < m_matrix2D[0].size(); j++) {
            QString cellContent;
            if (isEmpty(i, j))
                cellContent = "NULL";
            else
                cellContent = bubble(i, j)->type();

            line += cellContent.leftJustified(cellWidth, ' ');
        }
        qDebug().noquote() << line;
    }
}



void HexGridModel::normalizeCoordinatesIntoLocal(qreal &x, qreal &y){
    x = x - m_gridSceneOrigin.x();
    y = y - m_gridSceneOrigin.y();
}

void HexGridModel::normalizeCoordinatesIntoGlobal(qreal &x, qreal &y){
    x = x + m_gridSceneOrigin.x();
    y = y + m_gridSceneOrigin.y();
}

QPoint HexGridModel::matrix2DToCartesian(int row, int col) {
    int x = m_hexRadius * 2 * col;
    if (row % 2 != 0) {
        x -= m_hexRadius; // Décalage horizontal pour les lignes impaires
    }
    int y = std::sqrt(3) * m_hexRadius * row;
    return QPoint(x, y);
}


QVector<int> HexGridModel::cartesianToMatrix2D(qreal x, qreal y){
    qreal q = x / (2 * m_hexRadius);
    qreal r = y / (std::sqrt(3) * m_hexRadius);
    int col = qRound(q);
    int row = qRound(r);
    gripWithOffset(row,col);
    if(isValid(row,col))
        return {row,col};
    else
        return {-1,-1};
}

void HexGridModel::gripWithOffset(int &row, int &col){
    if(row<m_matrix2D.size()-1){
        if(row % 2 == 0 && col==m_matrix2D[0].size()-1){
            row++;
        }
        if(row % 2 == 1 && col==0){
            row++;
        }
    }
}

bool HexGridModel::isValid(int row, int col){
    if(row % 2 == 0 && col==m_matrix2D[0].size()-1)
        return false;
    if(row % 2 == 1 && col==0)
        return false;
    return true;
}

bool HexGridModel::isOutOfGrid(int row, int col){
    return !(row>=0 && row<m_nrows && col>=0 && col <m_ncols);
}

bool HexGridModel::isEmpty(int row, int col){
    return m_matrix2D[row][col] == nullptr;
}

void HexGridModel::addBubbleMatrix(int row, int col, Bubble *b){
    if(!isOutOfGrid(row,col) && isEmpty(row,col) && isValid(row,col)){
        b->gridPosition({row,col});
        QPoint p = matrix2DToCartesian(row,col);
        b->position(p);
        m_matrix2D[row][col] = b;
        //qDebug()<<"La grille ajoute une bulle (matrix)";
        emit bubbleAdded(b);
    }
}

void HexGridModel::addBubbleCartesian(qreal x, qreal y, Bubble *b){
    QVector p = cartesianToMatrix2D(x,y);
    if(!isOutOfGrid(p[0],p[1]) && isEmpty(p[0],p[1])){
        b->gridPosition(p);
        b->position(matrix2DToCartesian(p[0],p[1]));
        m_matrix2D[p[0]][p[1]] = b;
        //qDebug()<<"La grille ajoute une bulle (cartesian)";
        emit bubbleAdded(b);
    }

}

void HexGridModel::removeBubbleMatrix(int row, int col){
    delete m_matrix2D[row][col];
    m_matrix2D[row][col] = nullptr;
}

QVector<Bubble*> HexGridModel::getNeighbors(int row, int col){
    QVector<Bubble*> vec ;
    bool evenLine = row%2==0;

    //ligne du haut
    if(row-1 >= 0){
        if(m_matrix2D[row-1][col]!=nullptr)
            vec.push_back(m_matrix2D[row-1][col]);
        if(evenLine && col+1<m_matrix2D[0].size() && m_matrix2D[row-1][col+1]!=nullptr)
            vec.push_back(m_matrix2D[row-1][col+1]);
        if(!evenLine && col-1>=0 && m_matrix2D[row-1][col-1]!=nullptr)
            vec.push_back(m_matrix2D[row-1][col-1]);
    }
    //ligne centrale
    if(col-1 >= 0 && m_matrix2D[row][col-1]!=nullptr)
        vec.push_back(m_matrix2D[row][col-1]);
    if(col+1 <m_matrix2D[0].size() && m_matrix2D[row][col+1]!=nullptr)
        vec.push_back(m_matrix2D[row][col+1]);

    //ligne du bas
    if(row+1 < m_matrix2D.size()){
        if(m_matrix2D[row+1][col]!=nullptr)
            vec.push_back(m_matrix2D[row+1][col]);
        if(evenLine && col+1<m_matrix2D[0].size() && m_matrix2D[row+1][col+1]!=nullptr)
            vec.push_back(m_matrix2D[row+1][col+1]);
        if(!evenLine && col-1>=0 && m_matrix2D[row+1][col-1]!=nullptr)
            vec.push_back(m_matrix2D[row+1][col-1]);
    }
    return vec;
}

QVector<Bubble*> HexGridModel::getNeighborsDestructible(int row, int col){
    QVector<Bubble*> vec = getNeighbors(row,col);
    int cpt = 0;

    int i=0;
    int size = vec.size();
    while(i<size){
        if(!vec[i-cpt]->isDestructible()){
            vec.remove(i-cpt);
            cpt++;
        }
        i++;
    }

    return vec;
}

QVector<Bubble*> HexGridModel::getNeighborsSameColor(int row, int col){
    QVector<Bubble*> vec = getNeighborsDestructible(row,col);
    int cpt = 0;
    Bubble* current = bubble(row, col);
    ColoredBubble* currentBubble = dynamic_cast<ColoredBubble*>(current);

    int i=0;
    int size = vec.size();
    while(i<size){
        ColoredBubble *neighbor = dynamic_cast<ColoredBubble*>(vec[i-cpt]);

        if(neighbor->isColored()){
            if(!currentBubble->sameColor(neighbor)){
                vec.remove(i-cpt);
                cpt++;
            }
        }
        i++;
    }
    return vec;
}

void HexGridModel::removeBubblesMatrix(QVector<Bubble*> vec){
    for(int i=0; i<vec.size();i++){
        QVector<int> vPos = vec[i]->gridPosition();
        //qDebug()<<"La grille détruit une bulle";
        emit bubbleDestroyed(vec[i]);
        removeBubbleMatrix(vPos[0],vPos[1]);
    }
}

bool HexGridModel::lastRowEmpty(){
    for(int i=0; i<m_matrix2D[0].size();i++){
        if(!isEmpty(m_nrows-1,i))
            return false;
    }
    return true;
}

void HexGridModel::moveBubbleDown(int row, int col){
    int offset = (row % 2==0 ? 1 : -1);
    int rowDest = row + 1, colDest = col+offset;
    if(!isOutOfGrid(rowDest,colDest) && isEmpty(rowDest, colDest)){
        addBubbleMatrix(rowDest,colDest,bubble(row,col));
        m_matrix2D[row][col] = nullptr;
        //qDebug()<<"La grille déplace un bulle vers le bas";
        emit bubbleMoved(row,col,bubble(rowDest,colDest));
    }
}

void HexGridModel::addRow(QVector<Bubble*> *bubbleLine){
    if(lastRowEmpty()){
        for(int row=m_nrows-2; row>=0; row--){
            for(int col=0; col < m_ncols; col++){
                if(!isEmpty(row,col)){
                    moveBubbleDown(row,col);
                }
            }
        }
    }

    //qDebug()<<"La grille reçoit une ligne";
    for(int i=0; i<m_ncols;i++){
        addBubbleMatrix(0,i,bubbleLine->at(i));
    }




    //signal grille pleine
}

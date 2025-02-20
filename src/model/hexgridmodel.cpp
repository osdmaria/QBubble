#include "hexgridmodel.h"
#include <QDebug>

HexGridModel::HexGridModel(int width, int height, int radius, QPointF gridSceneOrigin, QPoint cannonPosition, QObject *parent)
    : QObject{parent}, m_width{width}, m_height{height}, m_gridSceneOrigin{gridSceneOrigin}, m_cannonPosition{cannonPosition}
{
    //qDebug()<<"canon"<<m_cannonPosition;
    m_cannonPosition = QPoint(550,450);
    m_hexRadius = radius;
    //m_ncols = m_width/(2*m_hexRadius) +1;
    m_ncols = 12;
    m_nrows = std::min(qRound(m_height/(std::sqrt(3)*m_hexRadius)),7);
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
    if(isOutOfGrid(row,col))
        return {-1,-1};
    return {row,col};
}

//convertit les coordonnées en paramètre en tenant compte des décallages valides
void HexGridModel::setPositionWithOffset(int &row, int &col){
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
    if(row==-1 || col==-1)
        return false;
    if(isOutOfGrid(row,col))
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
    auto p = cartesianToMatrix2D(x,y);
    setPositionWithOffset(p[0],p[1]);
    if(!isOutOfGrid(p[0],p[1]) && isEmpty(p[0],p[1])){
        b->gridPosition(p);
        b->position(matrix2DToCartesian(p[0],p[1]));
        m_matrix2D[p[0]][p[1]] = b;
        //qDebug()<<"La grille ajoute une bulle (cartesian)";
        emit bubbleAdded(b);
    }

}

void HexGridModel::removeBubbleMatrix(int row, int col){
    if(!isEmpty(row,col) && !isOutOfGrid(row,col)){
        delete m_matrix2D[row][col];
        m_matrix2D[row][col] = nullptr;
    }

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


bool HexGridModel::isRightObstacle(int row, int col){
    if(col+1 <m_matrix2D[0].size() && m_matrix2D[row][col+1]!=nullptr){
        if(!isEmpty(row,col+1))
            return true;
    }

    return false;
}

bool HexGridModel::isLeftObstacle(int row, int col){
    if(col-1 >= 0){
        if(!isEmpty(row,col-1))
            return true;
    }
    return false;
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

bool HexGridModel::isGridEmpty(){
    for(int row=0; row<m_nrows;row++){
        for(int col=0; col<m_ncols;col++){
            if(!isEmpty(row,col))
                return false;
        }
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

    if(!lastRowEmpty()){
        //qDebug()<<"ligne de trop";
        emit lastRowReached();
    }
}

bool HexGridModel::isInMiddle(int posX, int row, int col){
    QPoint middle = matrix2DToCartesian(row,col);
    int distance = abs(middle.x()-posX);
    return distance<m_hexRadius*0.6;
}



bool HexGridModel::isRightSide(int posX, int row, int col){
    QPoint middle = matrix2DToCartesian(row,col);
    if(posX < middle.x())
        return false;
    int distance = abs(middle.x()-posX);
    return distance > m_hexRadius*0.6 ;
}

//intersection du tir entre la trajectoire du tir provenant de srcPos et la ligne donnée en paramètre
QPoint HexGridModel::intersectRowAndNormalize(int angle, int srcRow) {
    QPoint rowToIntersect = matrix2DToCartesian(srcRow, 0);
    qreal x = rowToIntersect.x();
    qreal y = rowToIntersect.y();
    normalizeCoordinatesIntoGlobal(x, y);
    double angleRadians = angle * M_PI / 180.0;
    if (sin(angleRadians) == 0) {return QPoint(m_cannonPosition.x(), y);}
    int distance = (abs(y - m_cannonPosition.y())) / sin(angleRadians);
    qreal intersectX = m_cannonPosition.x() + distance * cos(angleRadians);
    normalizeCoordinatesIntoLocal(intersectX,y);
    return QPoint(intersectX, y);
}

//vérifie si il y a des bulles périphériques à la target
bool HexGridModel::isGripPossible(int row, int col){
    if(row==0)
        return true;
    if(row<0 || col<0)
        return false;
    bool evenLine = row%2==0;
    //ligne du haut
    if(row-1 >= 0){
        if(m_matrix2D[row-1][col]!=nullptr)
            return true;
        if(evenLine && col+1<m_matrix2D[0].size() && m_matrix2D[row-1][col+1]!=nullptr)
            return true;
        if(!evenLine && col-1>=0 && m_matrix2D[row-1][col-1]!=nullptr)
            return true;
    }
    //ligne centrale
    if(col-1 >= 0 && m_matrix2D[row][col-1]!=nullptr)
        return true;
    if(col+1 <m_matrix2D[0].size() && m_matrix2D[row][col+1]!=nullptr)
        return true;

    return false;
}


bool HexGridModel::validTrajectory(int intersectX, int currentRow, int currentCol, int angle){
    //Si la case est occupée la position n'est pas valide
    if(!isEmpty(currentRow,currentCol))
        return false;

    if(isRightSide(intersectX,currentRow,currentCol)){//si je suis plus sur la droite il ne doit pas y avoir de collision à droite
        if(isRightObstacle(currentRow,currentCol))
            return false;
    } else if(isInMiddle(intersectX,currentRow,currentCol)){
        return true;
    } else {//si je suis plus sur la gauche il ne doit pas y avoir de collision à gauche
        if(isLeftObstacle(currentRow,currentCol))
            return false;
    }
    return true;;
}

void HexGridModel::handleShot(int angle, Bubble *b){
    bool bubblePlaced = false;
    //qDebug()<<"La grille réceptionne le tir ("<<angle<<"degrés)";

    int currentRow = m_nrows-1;
    QPoint initPos = intersectRowAndNormalize(angle,currentRow);
    QVector<int> initMatrixPos = cartesianToMatrix2D(initPos.x(),initPos.y());
    setPositionWithOffset(initMatrixPos[0],initMatrixPos[1]);

    int currentCol = initMatrixPos[1];
    if(isOutOfGrid(currentRow,currentCol)){
        emit shotOutOfGrid();
        delete b;
        return;
    }


    QVector<int> lastValidPositionMatrix = initMatrixPos;
    int cptIter = 0;
    while(isValid(currentRow,currentCol) && validTrajectory(initPos.x(),currentRow,currentCol,angle) && cptIter<m_nrows){
        currentRow--;
        QPoint currentPos = intersectRowAndNormalize(angle,currentRow);
        QVector<int> currentMatrixPos = cartesianToMatrix2D(currentPos.x(),currentPos.y());
        setPositionWithOffset(currentMatrixPos[0],currentMatrixPos[1]);
        currentRow = currentMatrixPos[0];
        currentCol = currentMatrixPos[1];
        if(isValid(currentRow,currentCol) && isEmpty(currentRow,currentCol))
            lastValidPositionMatrix = currentMatrixPos;

        //je suis au bord je ne peux pas aller plus loin
        if(currentCol==0 || currentCol==m_ncols-1 && !isGripPossible(currentRow,currentCol))
            break;
        cptIter++;
    }

    if(currentRow==-1 && currentCol==-1 && lastValidPositionMatrix[0]==0){
        if(isEmpty(lastValidPositionMatrix[0],lastValidPositionMatrix[1])){
            addBubbleMatrix(lastValidPositionMatrix[0],lastValidPositionMatrix[1],b);
            bubblePlaced = true;
        }
    } else {
        if(isOutOfGrid(currentRow,currentCol)){
            emit shotOutOfGrid();
            delete b;
            return;
        }

    }






    if(!bubblePlaced){
        if(isValid(currentRow,currentCol) && isEmpty(currentRow,currentCol)){
            if(isGripPossible(currentRow,currentCol)){
                addBubbleMatrix(currentRow,currentCol,b);
                bubblePlaced = true;
            }
        } else {
            if(isGripPossible(lastValidPositionMatrix[0],lastValidPositionMatrix[1])){
                addBubbleMatrix(lastValidPositionMatrix[0],lastValidPositionMatrix[1],b);
                bubblePlaced = true;
            } else {
                int diffRow = abs(currentRow-lastValidPositionMatrix[0]);
                int diffCol = abs(currentCol-lastValidPositionMatrix[1]);
                currentRow+=diffRow;
                if(isValid(currentRow,currentCol) && isGripPossible(currentRow,currentCol)){
                    addBubbleMatrix(currentRow,currentCol,b);
                    bubblePlaced = true;
                } else{
                    currentCol+=diffCol;
                    if(isValid(currentRow,currentCol) && isGripPossible(currentRow,currentCol)){
                        addBubbleMatrix(currentRow,currentCol,b);
                        bubblePlaced = true;
                    }
                }
            }
        }

    }


    if(bubblePlaced){
        if(lastRowEmpty()){
            emit shotHandled(b);
        } else {
            emit lastRowReached();
        }
    } else {
        emit shotOutOfGrid();
        delete b;
    }
}

void HexGridModel::handleBurst(QVector<Bubble *> vec){
    removeBubblesMatrix(vec);
    emit findDisconnectedBubbles();
}












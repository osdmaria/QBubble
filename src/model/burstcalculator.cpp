#include "burstcalculator.h"

BurstCalculator::BurstCalculator(HexGridModel *hexGrid, QObject *parent) :
    QObject{parent}, m_hexGrid{hexGrid}
{
    m_music = new Music();
}



QVector<Bubble*> BurstCalculator::getConnectedBubblesColor(int row, int col){
    if(m_hexGrid->isEmpty(row,col))
        return {};
    QSet<Bubble*> visited;
    QQueue<Bubble*> queue;
    queue.enqueue(m_hexGrid->bubble(row,col));

    while(!queue.isEmpty()){
        Bubble *currentBubble = queue.dequeue();
        QVector<int> pos = currentBubble->gridPosition();
        QVector<Bubble*> neighbors = m_hexGrid->getNeighborsSameColor(pos[0], pos[1]);
        for(int i=0; i<neighbors.size();i++){
            if(!visited.contains(neighbors[i]))
                queue.enqueue(neighbors[i]);
        }
        visited.insert(currentBubble);
    }
    if(visited.size()<3)
        return QVector<Bubble*>();

    return QVector<Bubble*>::fromList(visited.values());
}


QVector<Bubble*> BurstCalculator::getConnectedBubblesExplosion(int row, int col){
    if(m_hexGrid->isEmpty(row,col))
        return {};
    QSet<Bubble*> visited;
    QQueue<Bubble*> queue;
    queue.enqueue(m_hexGrid->bubble(row,col));

    Bubble* current = m_hexGrid->bubble(row, col);
    ExplosiveBubble* explosiveBubble = dynamic_cast<ExplosiveBubble*>(current);

    if(explosiveBubble){
        int cpt = 0;
        int nbNeighbors = 0;
        while(!queue.isEmpty()){
            Bubble *currentBubble = queue.dequeue();
            if(cpt<explosiveBubble->explosionRadius()){
                QVector<int> pos = currentBubble->gridPosition();
                QVector<Bubble*> neighbors = m_hexGrid->getNeighborsDestructible(pos[0], pos[1]);
                if(nbNeighbors==0){
                    nbNeighbors = neighbors.size();
                    cpt++;
                }

                for(int i=0; i<neighbors.size();i++){
                    if(!visited.contains(neighbors[i]))
                        queue.enqueue(neighbors[i]);
                }
            }
            if(!visited.contains(currentBubble)){
                visited.insert(currentBubble);
                nbNeighbors--;
            }
        }
    }
    return QVector<Bubble*>::fromList(visited.values());
}

QVector<Bubble*> BurstCalculator::getDisconnectedBubbles(){
    QVector<QVector<int>> matrix(m_hexGrid->nrows(), QVector<int>(m_hexGrid->ncols(), -1));

    //On met des 1 aux coordonnées des grilles rattachées au plafond, 0 sinon
    for(int row=0; row<matrix.size(); row++){
        for(int col=0; col<matrix[0].size(); col++){
            if(!m_hexGrid->isEmpty(row,col)){
                if(row==0){
                    matrix[row][col] = 1;
                } else {
                    matrix[row][col] = 0;
                }
            }
        }
    }

    //On transforme en 1 les bulles connexes à la première rangées de bulles
    for(int row=1; row<matrix.size(); row++){
        for(int col=0; col<matrix[0].size(); col++){
            if(matrix[row][col]==0){
                QVector<Bubble*> neighbors = m_hexGrid->getNeighbors(row,col);
                if(neighbors.size()>0){
                    for(int k=0; k<neighbors.size();k++){
                        QVector<int> pos = neighbors[k]->gridPosition();
                        if(matrix[pos[0]][pos[1]]==1){
                            matrix[row][col] = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    //Les bulles encore à 0 sont donc non connexes au reste, on les récupère
    QVector<Bubble*> vec;
    for(int row=0; row<matrix.size(); row++){
        for(int col=0; col<matrix[0].size(); col++){
            if(matrix[row][col]==0)
                vec.push_back(m_hexGrid->bubble(row,col));
        }
    }
    return vec;
}


void BurstCalculator::burstFromColoredBubble(int row, int col){
    QVector<Bubble*> res = getConnectedBubblesColor(row,col);
    if(res.size()>0){
        emit bubblesToBurst(res);
        m_destroyedBubbles += res.size();
        m_music->soundEffectExplore("explore");
    } else {
        emit amountDestroyedBubbles(m_destroyedBubbles);
        m_destroyedBubbles = 0;
    }
}

void BurstCalculator::burstFromExplosiveBubble(int row, int col){
    QVector<Bubble*> res = getConnectedBubblesExplosion(row,col);
    if(res.size()>0){
        emit bubblesToBurst(res);
        m_destroyedBubbles += res.size();
    } else {
        emit amountDestroyedBubbles(m_destroyedBubbles);
        m_destroyedBubbles = 0;
    }
    m_music->soundEffectExplore("explore");
}

void BurstCalculator::burstDisconnectedBubbles(){
    QVector<Bubble*> res = getDisconnectedBubbles();
    if(res.size()>0){
        emit bubblesDisconnected(res);
        m_destroyedBubbles += res.size();
    }

    emit amountDestroyedBubbles(m_destroyedBubbles);
    m_destroyedBubbles = 0;
}




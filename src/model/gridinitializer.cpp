#include "gridinitializer.h"

GridInitializer::GridInitializer(HexGridModel *hexGrid, QObject *parent) :
    QObject{parent}, m_hexGridModel{hexGrid}
{}

void GridInitializer::initLevel1(){
    for(int i=0; i<m_hexGridModel->ncols();i++)
        m_hexGridModel->addBubbleMatrix(0,i,new ColoredBubble("bordeaux"));
    m_hexGridModel->addBubbleMatrix(1,1,new ColoredBubble("bordeaux"));
    m_hexGridModel->addBubbleMatrix(2,0,new ColoredBubble("bordeaux"));
    m_hexGridModel->addBubbleMatrix(1,m_hexGridModel->ncols()-1,new ColoredBubble("bordeaux"));
    m_hexGridModel->addBubbleMatrix(2,m_hexGridModel->ncols()-2,new ColoredBubble("bordeaux"));

    for(int i=2; i<m_hexGridModel->ncols()-1;i++)
        m_hexGridModel->addBubbleMatrix(1,i,new ColoredBubble("lightblue"));

    for(int i=1; i<m_hexGridModel->ncols();i++){
        if(i%2==0)
            m_hexGridModel->addBubbleMatrix(2,i,new ColoredBubble("green"));
        else
            m_hexGridModel->addBubbleMatrix(2,i,new ColoredBubble("brown"));
    }

}

void GridInitializer::initLevel2(){
    for(int i=0; i<m_hexGridModel->ncols();i++){
        if(i%2==0)
            m_hexGridModel->addBubbleMatrix(0,i,new ColoredBubble("green"));
        else
            m_hexGridModel->addBubbleMatrix(0,i,new ColoredBubble("brown"));
    }

    for(int i=0; i<m_hexGridModel->ncols();i++){
        if(i%4)
            m_hexGridModel->addBubbleMatrix(1,i,new ColoredBubble("lightblue"));
        else
            m_hexGridModel->addBubbleMatrix(1,i,new ColoredBubble("bordeaux"));
    }

}


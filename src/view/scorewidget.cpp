#include "src/view/scorewidget.h"
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>


ScoreWidget::ScoreWidget(QWidget *parent)
    : QWidget{parent}
{
    m_scoreLabel = new QLabel("Score: 0",this);
    setupUi();
}

ScoreWidget::~ScoreWidget(){}

void ScoreWidget::setupUi() {
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setColor(Qt::darkGray);
    shadow->setOffset(0, 0);
    m_scoreLabel->setGraphicsEffect(shadow);
    m_scoreLabel->setStyleSheet("");

}


void ScoreWidget::updateLabel(int x){
    if (m_scoreLabel) {
        m_scoreLabel->setText("Score: " + QString::number(x));

    }
}

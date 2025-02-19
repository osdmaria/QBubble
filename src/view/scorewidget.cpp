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
    shadow->setColor(Qt::white);
    shadow->setOffset(0, 0);
    m_scoreLabel->setStyleSheet("color: #EEFF6A; "
                                "font-size: 24px; "
                                "font-weight: bold;");
    m_scoreLabel->setGraphicsEffect(shadow);
}


void ScoreWidget::updateLabel(int x){
    if (m_scoreLabel) {
        m_scoreLabel->setText("Score: " + QString::number(x));

    }
}

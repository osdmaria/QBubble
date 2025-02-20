#include "src/view/scorewidget.h"
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>


ScoreWidget::ScoreWidget(QWidget *parent)
    : QWidget{parent}
{
    m_scoreLabel = new QLabel("Score<br>=0",this);

    setupUi();
}

ScoreWidget::~ScoreWidget(){}

void ScoreWidget::setupUi() {
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setColor(Qt::white);
    shadow->setOffset(0, 0);
    m_scoreLabel->setStyleSheet(
                                "background-color: #31B472;"
                                "color: #EEFF6A;"
                                "border-radius: 15px;"
                                "font-size: 28px;"
                                "font-weight: bold;"
                                "border: 2px solid #EEFF6A;");
    m_scoreLabel->setGraphicsEffect(shadow);
}


void ScoreWidget::updateLabel(int x){
    if (m_scoreLabel) {
        m_scoreLabel->setText("Score<br>=" + QString::number(x));


    }
}

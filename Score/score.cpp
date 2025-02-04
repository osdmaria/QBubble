#include "score.h"
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

Score::Score(QWidget *parent)
    : QWidget(parent), score(0)
{
    setupUi(this);
    // charge font font resources.qrc
    int fontId = QFontDatabase::addApplicationFont(":/font/Bubblegum.otf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    if (!fontFamilies.isEmpty()) {
        QFont gameFont(fontFamilies.at(0), 15);
        label->setFont(gameFont);
    } else {
        label->setFont(QFont("Arial", 15));  // Font secour si load echouer
    }
    //charge les couleur pour font
    label->setStyleSheet("color: #00BFFF;");
    label->setAlignment(Qt::AlignCenter);

    //gerer le shadow pour font
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setColor(Qt::darkGray);
    shadow->setOffset(0, 0);
    label->setGraphicsEffect(shadow);

    label->setText("Score: 0");


}

void Score::updateScore(int points) {
    score += points;

    // gerer animation
    QPropertyAnimation *anim = new QPropertyAnimation(label, "geometry");
    anim->setDuration(200);
    anim->setStartValue(QRect(label->x(), label->y(), label->width(), label->height()));
    anim->setKeyValueAt(0.5, QRect(label->x() - 5, label->y() - 5, label->width() + 10, label->height() + 10));
    anim->setEndValue(QRect(label->x(), label->y(), label->width(), label->height()));
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    label->setText("Score: " + QString::number(score));
}

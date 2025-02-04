#ifndef SCORE_H
#define SCORE_H

#include "ui_score.h"

class Score : public QWidget, private Ui::Score
{
    Q_OBJECT

public:
    explicit Score(QWidget *parent = nullptr);
    void updateScore(int points);

private:
    int score;
};

#endif // SCORE_H

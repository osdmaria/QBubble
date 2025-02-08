#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class ScoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScoreWidget(QWidget *parent = nullptr);
    ~ScoreWidget();

    void updateLabel(int x);


private:
    void setupUi();

    QLabel *m_scoreLabel;

signals:
};

#endif // SCOREWIDGET_H

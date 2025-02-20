#include "src/view/gameoverwindow.h"

gameOverWindow::gameOverWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
    connectSignals();
    setFont(QApplication::font());
    setWindowFlag(Qt::FramelessWindowHint);
    if (parent) {
        QWidget *parentWidget = qobject_cast<QWidget*>(parent);
        if (parentWidget) {
            int x = parentWidget->x() + (parentWidget->width() - this->width()) / 2;
            int y = parentWidget->y() + (parentWidget->height() - this->height()) / 2;
            move(x, y);
        }
    }
}

gameOverWindow::~gameOverWindow() {}

void gameOverWindow::setupUi() {

    // //Style des boutons
    // QString buttonStyle = "QPushButton {"
    //                       "background-color: #31B472;"
    //                       "color: #EEFF6A;"
    //                       "border-radius: 15px;"
    //                       "font-size: 20px;"
    //                       "border: 2px solid #EEFF6A;"
    //                       "}"
    //                       "QPushButton:hover {"
    //                       "background-color: #aade90;"
    //                       "}"
    //                       "QPushButton:pressed {"
    //                       "background-color: #6c9956;"
    //                       "}";

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Game Over", this);
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);

    m_scoreLabel = new QLabel("Score: 0", this); // Initialize the score label
    m_scoreLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_scoreLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // QPushButton *m_rejouerButton = new QPushButton("Rejouer", this);
    // QPushButton *m_menuPrincipalButton = new QPushButton("Menu Principal", this);
    // m_rejouerButton->setStyleSheet(buttonStyle);
    // m_menuPrincipalButton ->setStyleSheet(buttonStyle);


    m_rejouerButton = new QPushButton("Rejouer", this);
    m_menuPrincipalButton = new QPushButton("Menu Principal", this);
    buttonLayout->addWidget(m_rejouerButton);
    buttonLayout->addWidget(m_menuPrincipalButton);
    mainLayout->addLayout(buttonLayout);
}


void gameOverWindow::connectSignals() {
    if (!m_menuPrincipalButton) {
        qDebug() << "ERROR: m_reprendreButton nullptr!";
    }
    if (!m_rejouerButton) {
        qDebug() << "ERROR: m_retryButton nullptr!";
    }

    connect(m_menuPrincipalButton, &QPushButton::clicked, [this]() {
        qDebug() << "revenir vers menu clicked!";
        emit backMenuClicked();
    });

    connect(m_rejouerButton, &QPushButton::clicked, [this]() {
        qDebug() << "Retry button clicked!";
        emit replayClicked();
    });
}

void gameOverWindow::setScore(int score) {
    m_scoreLabel->setText("Score: " + QString::number(score));
}

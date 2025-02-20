#include "pausewindow.h"


PauseWindow::PauseWindow(QWidget *parent)
    : QDialog(parent),m_music(new Music())
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

PauseWindow::~PauseWindow() {
    delete m_music;
}

void PauseWindow::setupUi() {
    setFixedSize(400, 250);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    QSpacerItem *topSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(topSpacer);

    QString buttonStyle = "QPushButton {"
                          "background-color: #31B472;"
                          "color: #EEFF6A;"
                          "border-radius: 15px;"
                          "font-size: 20px;"
                          "border: 2px solid #EEFF6A;"
                          "padding: 10px 20px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #aade90;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #6c9956;"
                          "}";

    m_reprendreButton = new QPushButton("Reprendre", this);
    m_retryButton = new QPushButton("Recommencer", this);

    m_reprendreButton->setFixedSize(200, 60);
    m_retryButton->setFixedSize(200, 60);

    m_reprendreButton->setStyleSheet(buttonStyle);
    m_retryButton->setStyleSheet(buttonStyle);

    mainLayout->addWidget(m_reprendreButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_retryButton, 0, Qt::AlignCenter);

    QSpacerItem *bottomSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(bottomSpacer);

    setLayout(mainLayout);
}

void PauseWindow::connectSignals() {

    if (!m_reprendreButton) {
        qDebug() << "ERROR: m_reprendreButton nullptr!";
    }
    if (!m_retryButton) {
        qDebug() << "ERROR: m_retryButton nullptr!";
    }

    connect(m_reprendreButton, &QPushButton::clicked, [this]() {
        qDebug() << "Reprendre clicked!";
        m_music->playSoundEffect("click");
        emit reprendreClicked();
    });

    connect(m_retryButton, &QPushButton::clicked, [this]() {
        qDebug() << "Retry clicked!";
        m_music->playSoundEffect("click");
        emit retryClicked();
    });

}


void PauseWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap background(":/images/wood.jpg");

    if (!background.isNull()) {
        QPixmap scaledBackground = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, scaledBackground);
    } else {
        qDebug() << "Erreur : Impossible de charger l'image de fond.";
    }

    QWidget::paintEvent(event);
}

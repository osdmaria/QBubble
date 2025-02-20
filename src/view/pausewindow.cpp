#include "pausewindow.h"
//#include "sologamewindow.h"
#include "src/delegate/sologamecontroller.h"


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

    setGeometry(0, 0, 400, 300);
    setWindowTitle("Dialog");

    QWidget *verticalLayoutWidget = new QWidget(this);
    verticalLayoutWidget->setGeometry(QRect(100, 90, 203, 97));

    QVBoxLayout *verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    //Style des boutons
    QString buttonStyle = "QPushButton {"
                          "background-color: #31B472;"
                          "color: #EEFF6A;"
                          "border-radius: 15px;"
                          "font-size: 20px;"
                          "border: 2px solid #EEFF6A;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #aade90;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #6c9956;"
                          "}";
    m_reprendreButton= new QPushButton("Reprendre", verticalLayoutWidget);
    m_reprendreButton->setStyleSheet(buttonStyle);
    verticalLayout->addWidget(m_reprendreButton);

    // m_saveGameButton = new QPushButton("Enregistrer", verticalLayoutWidget);
    // m_saveGameButton->setStyleSheet(buttonStyle);
    // verticalLayout->addWidget(m_saveGameButton);

    m_retryButton = new QPushButton("Recommencer", verticalLayoutWidget);
    m_retryButton->setStyleSheet(buttonStyle);
    verticalLayout->addWidget(m_retryButton);

    verticalLayoutWidget->setLayout(verticalLayout);




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
        QPixmap scaledBackground = background.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, scaledBackground);
    } else {
        qDebug() << "Erreur : Impossible de charger l'image de fond.";
    }

    QWidget::paintEvent(event);
}

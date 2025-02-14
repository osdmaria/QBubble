#include "pausewindow.h"
//#include "sologamewindow.h"
#include "src/delegate/sologamecontroller.h"


pausewindow::pausewindow(QWidget *parent)
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

pausewindow::~pausewindow() {}

void pausewindow::setupUi() {

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

    m_menuPrincipalButton = new QPushButton("Menu Principal", verticalLayoutWidget);
    m_menuPrincipalButton->setStyleSheet(buttonStyle);
    verticalLayout->addWidget(m_menuPrincipalButton);

    verticalLayoutWidget->setLayout(verticalLayout);




}

void pausewindow::connectSignals() {
    connect(m_reprendreButton, &QPushButton::clicked, this, &pausewindow::close);
    //connect(m_menuPrincipalButton, &QPushButton::clicked, this, &SoloGameController::openMainMenuFromPause);
}

void pausewindow::paintEvent(QPaintEvent *event) {
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




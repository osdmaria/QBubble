#include "pausewindow.h"



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
    QPushButton *reprendreButton= new QPushButton("Reprendre", verticalLayoutWidget);
    reprendreButton->setStyleSheet(buttonStyle);
    verticalLayout->addWidget(reprendreButton);

    QPushButton *menuPrincipalButton = new QPushButton("Menu Principal", verticalLayoutWidget);
    menuPrincipalButton->setStyleSheet(buttonStyle);
    verticalLayout->addWidget(menuPrincipalButton);

    verticalLayoutWidget->setLayout(verticalLayout);




}

void pausewindow::connectSignals() {
    //connect(m_reprendreButton, &QPushButton::clicked, this, &MainMenuWindow::openMainWindow);
}

void pausewindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap background(":/images/wood.jpg");

    // Vérifier si l'image est correctement chargée
    if (!background.isNull()) {
        // Redimensionner l'image avec une transformation fluide
        QPixmap scaledBackground = background.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Dessiner l'image redimensionnée
        painter.drawPixmap(0, 0, scaledBackground);
    } else {
        qDebug() << "Erreur : Impossible de charger l'image de fond.";
    }

    QWidget::paintEvent(event);
}


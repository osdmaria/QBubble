#include "game_main_window.h"
#include "Canon/canon_widget.h"
#include "Grid/grid_logic.h"
#include "Grid/grid_view.h"
#include "Score/score.h"
#include "BubblesContainer/bubblescontainer.h"  // Include the BubblesContainer header

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    // Create a central widget and apply a vertical layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("background-color: #98ecff;");
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create a horizontal layout for the top section
    QHBoxLayout *topLayout = new QHBoxLayout();

    // Add a horizontal spacer to push the score widget to the right
    topLayout->addStretch();

    // Create and add the score widget at the top-right
    Score *scoreWidget = new Score(this);
    scoreWidget->updateScore(10); // Ensure this method actually updates the score display
    scoreWidget->setMinimumSize(150, 100); // Set a reasonable minimum size
    scoreWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // Prevent resizing

    topLayout->addWidget(scoreWidget);

    // Add the top layout to the main layout
    mainLayout->addLayout(topLayout);

    // Ensure the top layout expands horizontally
    topLayout->setContentsMargins(0, 0, 0, 0); // Remove unnecessary margins
    topLayout->setSpacing(0); // Remove spacing between widgets

    // Create and add the grid logic & grid view
    GridLogic *grid_logic = new GridLogic(10, 15, this);
    GridView *grid_view = new GridView(grid_logic, this);
    grid_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(grid_view);

    // Create a horizontal layout for the bottom section
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    // Add a spacer to push the cannon to the center of the screen
    // This spacer will take up half the space of the BubblesContainer
    bottomLayout->addStretch(1); // Add stretch with a factor of 1

    // Create and add the cannon at the bottom
    CanonWidget *cannon = new CanonWidget(this);
    cannon->setMinimumSize(130, 130);  // Set minimum size
    cannon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    bottomLayout->addWidget(cannon, 0, Qt::AlignCenter);

    // Add another spacer to push the BubblesContainer to the right
    // This spacer will take up the remaining space
    bottomLayout->addStretch(1); // Add stretch with a factor of 1

    // Create and add the BubblesContainer to the bottom-right
    BubblesContainer *bubblesContainer = new BubblesContainer(this);
    bubblesContainer->setMinimumSize(250, 60);  // Increase the size of the container
    bubblesContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    bottomLayout->addWidget(bubblesContainer, 0, Qt::AlignRight);

    // Add the bottom layout to the main layout
    mainLayout->addLayout(bottomLayout);

    // Set the central widget with the layout
    setCentralWidget(centralWidget);

    // Connect the cannon's fireBubble signal
    connect(cannon, &CanonWidget::fireBubble, this, &MainWindow::onFireBubble);
}

MainWindow::~MainWindow() {}

void MainWindow::onFireBubble(QPointF start, QPointF end)
{
    qDebug() << "Firing bubble from:" << start << "to" << end;
}

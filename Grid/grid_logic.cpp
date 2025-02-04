#include "Grid/grid_logic.h"

GridLogic::GridLogic(int max_number_rows, int nb_cols, QObject *parent)
    : QGraphicsScene(parent),
    m_max_nb_rows(max_number_rows),
    m_nb_cols(nb_cols),
    m_curr_nb_rows(0),
    m_graphic_offset(5),
    m_bubble_radius(25),
    m_is_on_left(true),
    m_grid(max_number_rows, QVector<Bubble*>(nb_cols, nullptr))
{
    setSceneRect(0, 0, m_nb_cols * 2 * m_bubble_radius, m_max_nb_rows * 2 * m_bubble_radius);
}

void GridLogic::addBubble(int row, int col, QColor color) {
    if (row < 0 ||
        row >= m_max_nb_rows ||
        col < 0 ||
        col >= m_nb_cols ||
        m_grid[row][col] != nullptr) {
        qDebug() << "addBubble :" << row << ", " << col <<  "Pas le bon emplacement";
        return;
    }

    // Determine the image path based on the color
    QString imagePath;
    if (color == Qt::red) {
        imagePath = ":/images/bubble_red.png";
    } else if (color == Qt::blue) {
        imagePath = ":/images/bubble_blue.png";
    } else if (color == Qt::yellow) {
        imagePath = ":/images/bubble_yellow.png";
    } else if (color == Qt::black){
        imagePath = ":/images/bubble_purple.png"; // Default color
    }

    // Create a new bubble and place it in the scene
    Bubble *bubble = new Bubble(imagePath, m_bubble_radius);
    if(m_is_on_left){
        bubble->setPosition(col * 2 * m_bubble_radius + m_graphic_offset - m_bubble_radius/2,
                            row * 2 * m_bubble_radius + m_graphic_offset);
    }else{
        bubble->setPosition(col * 2 * m_bubble_radius + m_graphic_offset + m_bubble_radius/2,
                            row * 2 * m_bubble_radius + m_graphic_offset);
    }

    addItem(bubble); // Adds the bubble onto the scene

    // Store in the grid
    m_grid[row][col] = bubble;
}

void GridLogic::removeBubble(int row, int col) {
    if (row < 0 || row >= m_max_nb_rows ||
        col < 0 || col >= m_nb_cols ||
        m_grid[row][col] == nullptr) {
        return;  // No bubble to remove
    }

    // Remove the bubble from the scene
    removeItem(m_grid[row][col]);
    delete m_grid[row][col];
    m_grid[row][col] = nullptr;

    emit bubblePopped(row, col);
}

void GridLogic::popBubbles() {
    // Example logic: Remove all bubbles (for now)
    for (int row = 0; row < m_curr_nb_rows; ++row) {
        for (int col = 0; col < m_nb_cols ; ++col) {
            if (m_grid[row][col] != nullptr) {
                removeBubble(row, col);
            }
        }
    }
}

void GridLogic::fillFirstRow() {
    if (m_curr_nb_rows > 0){
        m_is_on_left = !m_is_on_left;
        for (QGraphicsItem *item : items()) {
            item->setY(item->y() + m_bubble_radius * 2 + m_graphic_offset);
        }

        for (int col = 0; col < m_nb_cols ; ++col) {
            addBubble(0, col, getRandomColor());
        }
    }
}

void GridLogic::addRow() {
    if (m_curr_nb_rows + 1 >= m_max_nb_rows){
        qDebug() << "Game Over: "
                 << m_curr_nb_rows << " nombre de Rangs pour"
                 << m_max_nb_rows << " maximum !";
        emit gameOver();
    }
    QVector<Bubble*> newRow(m_nb_cols, nullptr);
    m_grid.prepend(newRow);  // Add a new row at the top
    m_curr_nb_rows++;
    fillFirstRow();
    emit rowAdded();
}

QColor GridLogic::getRandomColor() {
    QList<QColor> colors = {Qt::red, Qt::blue, Qt::yellow, Qt::black}; // List of possible colors
    int randomIndex = QRandomGenerator::global()->bounded(colors.size()); // Get a random index
    return colors[randomIndex]; // Return the selected color
}

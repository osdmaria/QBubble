#include "gridmodel.h"
#include "qpropertyanimation.h"

GridModel::GridModel(int max_number_rows, int nb_cols, QObject *parent)
    : QGraphicsScene(parent),
    m_max_nb_rows(max_number_rows),
    m_nb_cols(nb_cols),
    m_curr_nb_rows(0),
    m_graphic_offset(5),
    m_bubble_radius(20),
    m_offset_tab(0, true),
    m_grid(0, QVector<Bubble*>(nb_cols, nullptr))
{
    qDebug() << "GridModel Initialized.";

    setSceneRect(0, 0, m_nb_cols * 2*m_bubble_radius, m_max_nb_rows* 2* m_bubble_radius);



}


void GridModel::addBubble(int row, int col, QColor color) {

    if (row < 0 || row >= m_max_nb_rows
        || col < 0 || col >= m_nb_cols
        || m_grid[row][col] != nullptr) {
        return;
    }

    // Create a new bubble with the correct color
    Bubble* bubble = new Bubble(color, QPointF(row, col));
    m_grid[row][col] = bubble; // Store in the grid

    // Notify the view
    emit bubbleAdded(bubble, m_offset_tab[row]);
}


Bubble* GridModel::addBubble(int row, int col, QColor color, int random) {

    if (row < 0 || row >= m_max_nb_rows
        || col < 0 || col >= m_nb_cols
        || m_grid[row][col] != nullptr) {
        return nullptr;
    }

    // Create a new bubble with the correct color
    Bubble* bubble = new Bubble(color, QPointF(row, col));
    m_grid[row][col] = bubble; // Store in the grid

    // Notify the view
    emit bubbleAdded(bubble, m_offset_tab[row]);

    return bubble;
}

void GridModel::removeBubble(int row, int col) {
    if (row < 0 || row >= m_max_nb_rows ||
        col < 0 || col >= m_nb_cols ||
        m_grid[row][col] == nullptr) {
        qDebug() << "No bubble to remove";
        return;
    }

    qDebug() << "GridModel::removeBubble : row = " << row << ", col = " << col;

    // Remove the bubble from the scene
    emit bubblePopped(m_grid[row][col]);

    m_grid[row][col] = nullptr;
}

void GridModel::popAllBubbles() {
    // Example logic: Remove all bubbles (for now)
    for (int row = 0; row < m_curr_nb_rows; ++row) {
        for (int col = 0; col < m_nb_cols ; ++col) {
            if (m_grid[row][col] != nullptr) {
                removeBubble(row, col);
            }
        }
    }
}

void GridModel::fillFirstRow() {
    if (m_curr_nb_rows > 0){
        for (int col = 0; col < m_nb_cols ; ++col) {
            addBubble(0, col, getRandomColor());
        }
    }
}

bool GridModel::isGameOver(){
    if (m_curr_nb_rows + 1 >= m_max_nb_rows){
        qDebug() << "Game Over: "
                 << m_curr_nb_rows << " nombre de Rangs pour"
                 << m_max_nb_rows << " maximum !";
        emit gameOver();
        return true;
    }
    return false;
}

void GridModel::addNewLineOfBubbles() {
    if (isGameOver()) {
        return;
    }

    QVector<Bubble*> newRow(m_nb_cols, nullptr);
    m_grid.prepend(newRow);

    bool newOffset = (m_curr_nb_rows == 0) ? true : !m_offset_tab[0];
    m_offset_tab.prepend(newOffset); // Track shifted row
    m_curr_nb_rows++;


    for (int row = m_curr_nb_rows - 1; row >= 0; row--) {
        for (int col = 0; col < m_nb_cols; col++) {
            if (m_grid[row][col]) {
                int x = m_grid[row][col]->position().x();
                int y = m_grid[row][col]->position().y();
                m_grid[row][col]->setPosition(QPointF(x+1,y), m_offset_tab[row]);

            }

        }
    }


    emit rowAdded();
    fillFirstRow(); // Fill the new top row with bubbles

}


void GridModel::addRandomBubbleInAvaibleSpace() {
    if (isFirstRowFull()) {
        QVector<Bubble*> newRow(m_nb_cols, nullptr);
        m_grid.append(newRow);  // Add a new row at the bottom
        if (m_curr_nb_rows == 0) {
            m_offset_tab.append(true);
        } else {
            m_offset_tab.append(!m_offset_tab[m_curr_nb_rows - 1]); // Add a new row at the top
        }
        m_curr_nb_rows++;

        if (isGameOver()) { return; }
    }

    QVector<QPair<int, int>> spacesToPlay = getAccessibleBlankSpace();
    int randomIndex = QRandomGenerator::global()->bounded(spacesToPlay.size());
    int row = spacesToPlay[randomIndex].first;
    int col = spacesToPlay[randomIndex].second;
    qDebug() << "Adding Bubble at (" << row << ", " << col << ")";

    // Find the lowest row where a bubble exists
    int startRow = m_curr_nb_rows - 1; // Start at the last row
    while (startRow > 0 && (m_grid[startRow][col] == nullptr)) {
        startRow--; // Move upwards until we find a valid bubble
    }
    startRow = qMin(m_curr_nb_rows - 1, startRow + 1); // Make sure it starts below the bubbles
    int startCol = col;

    qDebug() << "Start Position: (" << startRow << ", " << startCol << ")";
    qDebug() << "Target Position: (" << row << ", " << col << ")";

    Bubble* newBubble = addBubble(row, col, getRandomColor(), 1);
    if (!newBubble) {
        qDebug() << "Failed to create bubble!";
        return;
    }

    // Ensure start and target positions are valid before animating
    if (startRow >= m_grid.size() || startCol >= m_nb_cols || m_grid[startRow][startCol] == nullptr) {
        qDebug() << "Invalid start position! Adjusting...";
        return;
    }
    if (row >= m_grid.size() || col >= m_nb_cols || m_grid[row][col] == nullptr) {
        qDebug() << "Invalid target position!";
        return;
    }

    // Create animation
    QPropertyAnimation* animation = new QPropertyAnimation(newBubble, "pos");
    animation->setDuration(500); // Animation time in milliseconds
    animation->setStartValue(m_grid[startRow][startCol]->pos()); // Use the current position
    animation->setEndValue(m_grid[row][col]->pos()); // Use the target position
    animation->setEasingCurve(QEasingCurve::OutBounce);  // Smooth movement

    connect(animation, &QPropertyAnimation::finished, [=]() {
        handlePossiblePoppableBubbles(row, col);
        handlePossibleDroppableBubbles();
        handlePossibleEmptyFirstRow();
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}





void GridModel::addBubbleInCanonDirection(int angle) {
    // Gestion des lignes pleines (commun aux deux fonctions)
    if (isFirstRowFull()) {
        QVector<Bubble*> newRow(m_nb_cols, nullptr);
        m_grid.append(newRow);  // Ajouter une nouvelle ligne en bas
        if (m_curr_nb_rows == 0) {
            m_offset_tab.append(true);
        } else {
            m_offset_tab.append(!m_offset_tab[m_curr_nb_rows - 1]); // Ajouter une nouvelle ligne en haut
        }
        m_curr_nb_rows++;

        if (isGameOver()) { return; }
    }

    // Convertir l'angle en radians
    double radians = angle * M_PI / 180.0;

    // Calculer le vecteur de direction
    double dx = cos(radians);
    double dy = sin(radians);

    // Position de départ (en supposant que le canon est au centre en bas)
    double x = m_nb_cols / 2.0;
    double y = m_curr_nb_rows - 1;

    // Simuler le chemin de la bulle
    while (true) {
        x += dx;
        y += dy;

        // Vérifier si la bulle est hors des limites
        if (x < 0 || x >= m_nb_cols || y < 0 || y >= m_curr_nb_rows) {
            break;
        }

        // Vérifier si la bulle touche une autre bulle
        int row = static_cast<int>(y);
        int col = static_cast<int>(x);

        if (m_grid[row][col] != nullptr) {
            // Ajuster la position en fonction de l'offset
            if (m_offset_tab[row]) {
                if (x - col > 0.5) {
                    col++;
                }
            } else {
                if (x - col > 0.5) {
                    col++;
                }
            }

            // Assurer que la colonne est dans les limites
            if (col < 0) col = 0;
            if (col >= m_nb_cols) col = m_nb_cols - 1;

            // Ajouter la bulle à la position calculée
            qDebug() << "Adding Bubble at (" << row << ", " << col << ")";
            Bubble* newBubble = addBubble(row, col, getRandomColor(), 1);
            if (!newBubble) {
                qDebug() << "Failed to create bubble!";
                return;
            }

            // Trouver la ligne la plus basse où une bulle existe
            int startRow = m_curr_nb_rows - 1; // Commencer à la dernière ligne
            while (startRow > 0 && (m_grid[startRow][col] == nullptr)) {
                startRow--; // Remonter jusqu'à trouver une bulle valide
            }
            startRow = qMin(m_curr_nb_rows - 1, startRow + 1); // S'assurer qu'elle commence en dessous des bulles
            int startCol = col;

            // Créer l'animation
            QPropertyAnimation* animation = new QPropertyAnimation(newBubble, "pos");
            animation->setDuration(500); // Durée de l'animation en millisecondes
            animation->setStartValue(m_grid[startRow][startCol]->pos()); // Utiliser la position actuelle
            animation->setEndValue(m_grid[row][col]->pos()); // Utiliser la position cible
            animation->setEasingCurve(QEasingCurve::OutBounce);  // Mouvement fluide

            connect(animation, &QPropertyAnimation::finished, [=]() {
                handlePossiblePoppableBubbles(row, col);
                handlePossibleDroppableBubbles();
                handlePossibleEmptyFirstRow();
            });

            animation->start(QAbstractAnimation::DeleteWhenStopped);

            break;
        }
    }
}

bool GridModel::isFirstRowFull(){
    if(m_curr_nb_rows > 0){
        for (int col = 0; col < m_nb_cols; col ++){
            if (m_grid[m_curr_nb_rows-1][col] == nullptr){
                return false;
            }
        }
    }
    qDebug() << "First row is full";
    return true;

}


bool GridModel::isFirstRowEmpty(){
    if(m_curr_nb_rows > 0){
        for (int col = 0; col < m_nb_cols; col ++){
            if (m_grid[m_curr_nb_rows-1][col] != nullptr){
                return false;
            }
        }
    }
    return true;
}

void GridModel::handlePossibleEmptyFirstRow(){
    if(isFirstRowEmpty()){
        m_grid.removeAt(m_curr_nb_rows - 1);
        if(m_curr_nb_rows == 0){
            m_offset_tab.removeAt(m_curr_nb_rows - 1);
        }
        else{
            m_offset_tab.removeAt(m_curr_nb_rows - 1);    // Add a new row at the top
        }
        m_curr_nb_rows--;
    }
}

void GridModel::handlePossibleDroppableBubbles(){
    QVector<QPair<int, int>> bubblesToDrop = getDroppableBubbles();
    qDebug() << "Bulle a faire tomber : " << bubblesToDrop;
    for (auto bubble_index: bubblesToDrop) {
        removeBubble(bubble_index.first, bubble_index.second);
    }

}

void GridModel::handlePossiblePoppableBubbles(int row, int col){
    QVector<QPair<int, int>> bubblesToPop = getSameColorConnectedBubbles(row, col);
    qDebug() << "Bulle a exploser : " << bubblesToPop;

    for (auto bubble_index: bubblesToPop) {
        removeBubble(bubble_index.first, bubble_index.second);
    }
}

QVector<QPair<int, int>> GridModel::getSameColorConnectedBubbles(int bubble_row, int bubble_col) {
    if (!m_grid[bubble_row][bubble_col]) return {}; // Safety check

    /* m_off_set_tab a true si il est à gauche
     * Notre grille ayant un décalage, on créer un pattern de recherche:
     * Depuis (i,j) si on à un décalage vers la droite, les voisins seront:
     *   - (i-1,j), (i-1,j+1)   :   Haut gauche, Haut droite
     *   - (i,j-1), (i,j+1)     :   Gauche, Droite
     *   - (i+1,j), (i+1,j+1)   :   Bas gauche, Bas droite
     * Si on a un décalge à gauche:
     *   - (i-1,j-1), (i-1,j)   :   Haut gauche, Haut droite
     *   - (i,j-1), (i,j+1)     :   Gauche, Droite
     *   - (i+1,j-1), (i+1,j)   :   Bas gauche, Bas droite
    */
    auto getAdjacentIndexes = [&](int row_index, int col_index) -> QVector<QPair<int, int>> {
        return {
            {row_index-1, m_offset_tab[row_index] ? col_index-1 : col_index}, // Haut Gauche
            {row_index-1, m_offset_tab[row_index] ? col_index : col_index+1},  // Haut Droite
            {row_index, col_index-1}, {row_index, col_index+1},                // Gauche, Droite
            {row_index+1, m_offset_tab[row_index] ? col_index-1 : col_index},  // Bas Gauche
            {row_index+1, m_offset_tab[row_index] ? col_index : col_index+1}    // Bas Droite
        };
    };

    QColor targetColor = m_grid[bubble_row][bubble_col]->color();

    QSet<QPair<int, int>> visited;
    QQueue<QPair<int, int>> queue;

    // Start by adding the initial bubble
    queue.enqueue({bubble_row, bubble_col});
    visited.insert({bubble_row, bubble_col});

    while (!queue.isEmpty()) {
        QPair<int, int> current = queue.dequeue();
        int r = current.first, c = current.second;

        for (auto dir : getAdjacentIndexes(r, c)) {
            int row = dir.first, col = dir.second;
            if (row >= 0 && row < m_curr_nb_rows &&
                col >= 0 && col < m_nb_cols &&
                m_grid[row][col] &&
                m_grid[row][col]->color() == targetColor &&
                !visited.contains({row, col})) {
                visited.insert({row, col});
                queue.enqueue({row, col});
            }
        }
    }
    if (visited.size() < 3) { return QVector<QPair<int, int>>();}
    return QVector<QPair<int, int>>::fromList(visited.values());
}

QVector<QPair<int, int>> GridModel::getAccessibleBlankSpace() {
    if (m_curr_nb_rows == 0) return {};

    auto getAdjacentIndexes = [&](int row_index, int col_index) -> QVector<QPair<int, int>> {
        return {
            {row_index-1, m_offset_tab[row_index] ? col_index-1 : col_index}, // Haut Gauche
            {row_index-1, m_offset_tab[row_index] ? col_index : col_index+1},  // Haut Droite
            {row_index, col_index-1}, {row_index, col_index+1},                        // Gauche, Droite
            {row_index+1, m_offset_tab[row_index] ? col_index-1 : col_index},  // Bas Gauche
            {row_index+1, m_offset_tab[row_index] ? col_index : col_index+1}    // Bas Droite
        };
    };

    int lastRow = m_curr_nb_rows - 1;
    QSet<QPair<int, int>> visited;
    QQueue<QPair<int, int>> queue;

    // Initialize queue with all blank spaces in the last row
    for (int col = 0; col < m_nb_cols; ++col) {
        if (m_grid[lastRow][col] == nullptr) {
            queue.enqueue({lastRow, col});
            visited.insert({lastRow, col});
        }
    }

    while (!queue.isEmpty()) {
        QPair<int, int> current = queue.dequeue();
        int r = current.first, c = current.second;

        for (auto dir : getAdjacentIndexes(r, c)) {
            int row = dir.first, col = dir.second;
            if (row >= 0 && row < m_curr_nb_rows &&
                col >= 0 && col < m_nb_cols &&
                m_grid[row][col] == nullptr &&
                !visited.contains({row, col})) {
                visited.insert({row, col});
                queue.enqueue({row, col});
            }
        }
    }

    return QVector<QPair<int, int>>::fromList(visited.values());
}

QVector<QPair<int, int>> GridModel::getDroppableBubbles() {
    if (m_curr_nb_rows == 0) return {};

    auto getAdjacentIndexes = [&](int row_index, int col_index) -> QVector<QPair<int, int>> {
        return {
            {row_index-1, m_offset_tab[row_index] ? col_index-1 : col_index}, // Haut Gauche
            {row_index-1, m_offset_tab[row_index] ? col_index : col_index+1},  // Haut Droite
            {row_index, col_index-1}, {row_index, col_index+1},               // Gauche, Droite
            {row_index+1, m_offset_tab[row_index] ? col_index-1 : col_index}, // Bas Gauche
            {row_index+1, m_offset_tab[row_index] ? col_index : col_index+1}  // Bas Droite
        };
    };

    QSet<QPair<int,int>> toDrop;
    QQueue<QPair<int, int>> toVisit;
    QSet<QPair<int, int>> connectedBubbles;

    // Prepare all cells to visit
    QSet<QPair<int, int>> notVisited;
    for (int col = 0; col < m_nb_cols; ++col) {
        for (int row = 0; row < m_curr_nb_rows; ++row) {
            if (m_grid[row][col]) {
                notVisited.insert({row, col});
            }
        }
    }

    while (!notVisited.isEmpty()) {
        QPair<int, int> focusedCell = *notVisited.begin();
        toVisit.enqueue(focusedCell);
        notVisited.remove(focusedCell);
        connectedBubbles.insert(focusedCell);

        bool frontierMet = false;

        while (!toVisit.isEmpty()) {
            QPair<int, int> current = toVisit.dequeue();
            int r = current.first, c = current.second;
            //if (r == 0  || c == 0 || c == m_nb_cols-1) {

            if (r == 0 ) {
                // si a un voisin frontiere
                frontierMet = true;
            }
            for (auto dir : getAdjacentIndexes(r, c)) {
                int row = dir.first, col = dir.second;

                if (row >= 0 && row < m_curr_nb_rows &&
                    col >= 0 && col < m_nb_cols &&
                    notVisited.contains({row, col}) ) {
                    toVisit.enqueue({row, col});
                    notVisited.remove({row, col});
                    connectedBubbles.insert({row, col});
                }
            }
        }
        if (!frontierMet) {
            for (const auto& bubble : connectedBubbles) {
                if (m_grid[bubble.first][bubble.second]){
                    toDrop.insert({bubble.first,bubble.second});
                }
            }
        }
        connectedBubbles.clear();
    }

    return QVector<QPair<int, int>>::fromList(toDrop.values());
}



void GridModel::setOffset(int row, bool offset) {
    if (row < 0 || row >= m_offset_tab.size()) return;
    m_offset_tab[row] = offset;
    emit offsetUpdated(row, m_offset_tab[row]);
}

bool GridModel::getOffset(int row) const {
    if (row < 0 || row >= m_offset_tab.size()) return false;
    return m_offset_tab[row];
}


void GridModel::addNewLineOfBubblesRequest()
{
    qDebug() << "Adding a new line of bubbles!";
    addNewLineOfBubbles();
}

void GridModel::addRandomBubbleInAvaibleSpaceRequest()
{
    qDebug() << "Adding a random bubble!";
    addRandomBubbleInAvaibleSpace();
}


QColor GridModel::getRandomColor() {

    QList<QColor> colors = {QColor(128,0,32), // Bordeaux
        QColor(105,105,25), // Brown
        Qt::green,      // Green
        QColor(176,213,230)  //lightblue
    };

    // Get a random index from the list of colors
    int randomIndex = QRandomGenerator::global()->bounded(colors.size());

    return colors[randomIndex]; // Return the selected color
}




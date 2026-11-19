#include "mainwindow.h"

#include <QFont>
#include <QPen>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      timer(new QTimer(this)),
      cellSize(42),
      boardLeft(25),
      boardTop(75),
      playerRow(1),
      playerCol(1),
      enemyRows{3, 6},
      enemyCols{6, 8},
      score(0),
      lives(3),
      hasKey(false),
      gameWon(false),
      gameOver(false),
      collision(false)
{
    setWindowTitle("Treasure Hunt - CSCE 1001");
    setFixedSize(650, 560);

    connect(timer, &QTimer::timeout, this, &MainWindow::gameLoop);
    timer->start(150);

    initializeGame();
}

MainWindow::~MainWindow()
{
}

// ============================================================
// PROVIDED GUI CODE: students do not need to modify this part.
// ============================================================

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor(25, 29, 43));

    drawInstructions(painter);
    drawBoard(painter);
    drawPlayer(painter);
    drawEnemies(painter);
    drawStatus(painter);
}

void MainWindow::drawInstructions(QPainter &painter)
{
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 17, QFont::Bold));
    painter.drawText(25, 35, "TREASURE HUNT");

    painter.setFont(QFont("Arial", 9));
    painter.setPen(QColor(210, 215, 230));
    painter.drawText(250, 35, "Move with W A S D | Collect T and K | Reach X");
}

void MainWindow::drawBoard(QPainter &painter)
{
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            QRect cell(boardLeft + c * cellSize,
                       boardTop + r * cellSize,
                       cellSize - 2, cellSize - 2);

            if (maze[r][c] == '#') {
                painter.setBrush(QColor(65, 83, 130));
                painter.setPen(Qt::NoPen);
                painter.drawRoundedRect(cell, 5, 5);
            } else {
                painter.setBrush(QColor(43, 49, 67));
                painter.setPen(QPen(QColor(65, 72, 91), 1));
                painter.drawRoundedRect(cell, 4, 4);

                if (maze[r][c] == 'T') {
                    painter.setBrush(QColor(255, 205, 65));
                    painter.setPen(Qt::NoPen);
                    painter.drawEllipse(cell.center(), 7, 7);
                } else if (maze[r][c] == 'K') {
                    painter.setPen(QPen(QColor(255, 220, 70), 4));
                    painter.drawEllipse(cell.center().x() - 6,
                                        cell.center().y() - 6, 12, 12);
                    painter.drawLine(cell.center().x() + 6,
                                     cell.center().y(),
                                     cell.center().x() + 13,
                                     cell.center().y());
                } else if (maze[r][c] == 'X') {
                    painter.setPen(QPen(QColor(90, 230, 150), 3));
                    painter.drawRect(cell.adjusted(9, 6, -9, -6));
                } else if (maze[r][c] == 'H') {
                    painter.setBrush(QColor(235, 64, 85));
                    painter.setPen(Qt::NoPen);
                    QPoint c = cell.center();
                    QPoint tip[3] = {c + QPoint(-9, -1), c + QPoint(9, -1), c + QPoint(0, 10)};
                    painter.drawEllipse(c + QPoint(-5, -3), 5, 5);
                    painter.drawEllipse(c + QPoint(5, -3), 5, 5);
                    painter.drawPolygon(tip, 3);
                }
            }
        }
    }
}

void MainWindow::drawPlayer(QPainter &painter)
{
    QRect cell(boardLeft + playerCol * cellSize,
               boardTop + playerRow * cellSize,
               cellSize - 2, cellSize - 2);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 220, 55));
    painter.drawEllipse(cell.adjusted(7, 7, -7, -7));
}

void MainWindow::drawEnemies(QPainter &painter)
{
    for (int i = 0; i < ENEMY_COUNT; i++) {
        QRect cell(boardLeft + enemyCols[i] * cellSize,
                   boardTop + enemyRows[i] * cellSize,
                   cellSize - 2, cellSize - 2);

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(235, 85, 100));
        painter.drawEllipse(cell.adjusted(7, 7, -7, -7));
    }
}

void MainWindow::drawStatus(QPainter &painter)
{
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12, QFont::Bold));

    int y = boardTop + ROWS * cellSize + 27;
    painter.drawText(25, y, QString("Score: %1").arg(score));
    painter.drawText(160, y, QString("Lives: %1").arg(lives));
    painter.drawText(285, y, QString("Key: %1").arg(hasKey ? "Collected" : "No"));

    if (gameWon || gameOver) {
        painter.setFont(QFont("Arial", 18, QFont::Bold));
        painter.setPen(gameWon ? QColor(90, 230, 150) : QColor(255, 110, 110));
        painter.drawText(25, y + 35,
                         gameWon ? "YOU WIN! Press R to restart."
                                 : "GAME OVER! Press R to restart.");
    }
}

// ============================================================
// STUDENT CODE: complete the TODO sections below.
// ============================================================

void MainWindow::initializeGame()
{
    // TODO 1:
    // Reset player position, score, lives, key status, and game flags.
    // Reset enemy positions to their original starting positions.
    // Hint: player starts at row 1, column 1; lives = 3; score = 0.

    playerRow = 1;
    playerCol = 1;
    lives = 3;
    score = 0;
    collision = false;
    gameWon = false;
    gameOver = false;
    timer->start(150);
    hasKey = false;
    maze[7][1] = 'K';
    maze[1][7] = 'T';
    maze[3][10] = 'T';
    maze[5][4] = 'T';
    maze[8][6] = 'H';
    enemyRows[0] = 3;
    enemyCols[0] = 6;
    enemyRows[1] = 6;
    enemyCols[1] = 8;

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R) {
        initializeGame();
        update();
        return;
    }

    if (gameWon || gameOver)
        return;

    // TODO 2:
    // Call movePlayer() with the correct row/column changes:
    // W = (-1, 0), S = (1, 0), A = (0, -1), D = (0, 1).
    // After a valid player turn, call moveEnemies(), checkEnemyCollision(),
    // and checkGameState().
    // Finally call update() to refresh the GUI.

    int oplayerRow = playerRow;
    int oplayerCol = playerCol;

    if(event->key() == Qt::Key_W) {
        movePlayer(-1, 0);
    } else if (event->key() == Qt::Key_S) {
        movePlayer(1, 0);
    } else if(event->key() == Qt::Key_A) {
        movePlayer(0, -1);
    } else if(event->key() == Qt::Key_D) {
        movePlayer(0, 1);
    }

    if(oplayerRow != playerRow || oplayerCol != playerCol) {
        moveEnemies();
        checkEnemyCollision();
        checkGameState();
    }

    update();
}

void MainWindow::movePlayer(int rowChange, int colChange)
{
    // TODO 3:
    // Calculate the new row and column.
    // Use isValidMove() before changing the player's position.
    // If the move is valid:
    //   - update playerRow and playerCol
    //   - call collectItem() for the new position
    //   - check whether the player reached an enemy

    int newRow = playerRow + rowChange;
    int newCol = playerCol + colChange;

    bool valid = isValidMove(newRow, newCol);

    if (valid == true) {
        playerRow += rowChange;
        playerCol += colChange;
        collectItem(playerRow, playerCol);
        checkEnemyCollision();
    }

}

bool MainWindow::isValidMove(int newRow, int newCol)
{
    // TODO 4:
    // Return false if the position is outside the maze.
    // Return false if maze[newRow][newCol] is a wall '#'.
    // Return false if the exit 'X' is reached before collecting the key.
    // Otherwise return true.

    if (newCol < 0 || newCol > COLS - 1) {
        return false;
    }
    if (newRow < 0 || newRow > ROWS - 1) {
        return false;
    }
    if (maze[newRow][newCol] == '#') {
        return false;
    }
    if (maze[newRow][newCol] == 'X' && hasKey == false) {
        return false;
    }

    return true;
}

bool MainWindow::isEnemyAt(int row, int col)
{
    // TODO 5:
    // Use a loop over the enemyRows and enemyCols arrays.
    // Return true if an enemy occupies (row, col); otherwise false.

    for(int i = 0; i < ENEMY_COUNT; i++) {
        if(enemyRows[i] == row && enemyCols[i] == col) {
            return true;
        }
    }

    return false;
}

void MainWindow::collectItem(int row, int col)
{
    // TODO 6:
    // If the cell contains treasure 'T':
    //   add 10 points using updateScore(10, &score)
    //   replace the cell with '.'
    //
    // If the cell contains key 'K':
    //   set hasKey to true
    //   replace the cell with '.'

    if(maze[row][col] == 'T') {
        updateScore(10, &score);
        maze[row][col] = '.';
    }

    if(maze[row][col] == 'H') {
        updateScore(100, &score);
        lives += 10;
        maze[row][col] = '.';
    }

    if(maze[row][col] == 'K') {
        hasKey = true;
        maze[row][col] = '.';
    }

}

void MainWindow::moveEnemies()
{
    // TODO 7 (extension):
    // Use a loop to move each enemy.
    // Choose a random direction and move only if the destination is valid
    // and is not a wall. Keep enemies inside the maze.
    // Hint: QRandomGenerator::global()->bounded(4) returns 0, 1, 2, or 3.
    //
    // Suggested directions:
    // 0 = up, 1 = down, 2 = left, 3 = right.

    collision = false;

        for(int i = 0; i < ENEMY_COUNT; i++) {
            int colChangeE = 0, rowChangeE = 0;
            bool valid = true;
            int direction = QRandomGenerator::global()->bounded(4);
            if(direction == 0) {
                rowChangeE = -1;
            } else if(direction == 1) {
                rowChangeE = 1;
            } else if(direction == 2) {
                colChangeE = -1;
            } else if(direction == 3) {
                colChangeE = 1;
            }
            int newRow = enemyRows[i] + rowChangeE;
            int newCol = enemyCols[i] + colChangeE;
            if (newCol < 0 || newCol > COLS - 1) {
                valid = false;
            }
            else if (newRow < 0 || newRow > ROWS - 1) {
                valid = false;
            }
            else if (maze[newRow][newCol] == '#') {
                valid = false;
            }
            if (valid == true) {
                enemyRows[i] += rowChangeE;
                enemyCols[i] += colChangeE;
            }
        }
}

void MainWindow::checkEnemyCollision()
{
    // TODO 8:
    // If an enemy is at the player's current position:
    //   call loseLife(&lives)
    //   reset playerRow and playerCol to the starting position.
    // Optional: prevent repeated collision until the next enemy move.

    bool enemy = isEnemyAt(playerRow, playerCol);
    if(enemy == true && collision == false) {
        playerRow = 1;
        playerCol = 1;
        loseLife(&lives);
        collision = true;
    }
}

void MainWindow::checkGameState()
{
    // TODO 9:
    // Set gameWon = true when the player reaches 'X' and hasKey is true.
    // Set gameOver = true when lives <= 0.
    // Stop the timer if the game is won or over.

    if(maze[playerRow][playerCol] == 'X' && hasKey == true) {
        gameWon = true;

    }

    if(lives <= 0) {
        gameOver = true;
    }

    if(gameOver == true || gameWon == true) {
        timer->stop();
    }


}

void MainWindow::updateScore(int points, int *currentScore)
{
    // TODO 10:
    // Use the pointer to increase the score.
    // Example idea: *currentScore = *currentScore + points;

    *currentScore += points;
}

void MainWindow::loseLife(int *currentLives)
{
    // TODO 11:
    // Use the pointer to decrease the number of lives by one.

    *currentLives -= 1;
}

void MainWindow::gameLoop()
{
    // This slot is called by the timer.
    // Students may use it for timed enemy movement if desired.
    // Keep the GUI responsive and call update() after changing game data.
    if (!gameWon && !gameOver)
        update();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>

// Game symbols stored in the 2D maze array.
const int ROWS = 10;
const int COLS = 12;
const int ENEMY_COUNT = 2;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void gameLoop();

private:
    // ---------------- GUI / framework code ----------------
    QTimer *timer;
    int cellSize;
    int boardLeft;
    int boardTop;

    void drawBoard(QPainter &painter);
    void drawPlayer(QPainter &painter);
    void drawEnemies(QPainter &painter);
    void drawStatus(QPainter &painter);
    void drawInstructions(QPainter &painter);

    // ---------------- Game data ----------------
    // '#': wall, '.': path, 'T': treasure, 'K': key, 'X': exit
    char maze[ROWS][COLS] = {
        {'#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','#','.','.','T','.','.','.','#'},
        {'#','.','#','.','#','.','#','#','#','.','.','#'},
        {'#','.','#','.','.','.','.','.','#','.','T','#'},
        {'#','.','#','#','#','#','.','.','#','.','.','#'},
        {'#','.','.','.','T','#','.','#','#','#','.','#'},
        {'#','#','#','.','.','#','.','.','.','.','.','#'},
        {'#','K','.','.','#','#','#','.','#','.','X','#'},
        {'#','.','.','.','.','.','.','.','#','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#'}
    };

    int playerRow;
    int playerCol;

    bool collision;

    int enemyRows[ENEMY_COUNT];
    int enemyCols[ENEMY_COUNT];

    int score;
    int lives;
    bool hasKey;
    bool gameWon;
    bool gameOver;

    // ---------------- Student implementation ----------------
    void initializeGame();

    // Use pointer parameters where appropriate to update game data.
    void movePlayer(int rowChange, int colChange);
    bool isValidMove(int newRow, int newCol);
    bool isEnemyAt(int row, int col);
    void collectItem(int row, int col);
    void moveEnemies();
    void checkEnemyCollision();
    void checkGameState();

    // Suggested helper: pass score/lives by pointer and update them.
    void updateScore(int points, int *currentScore);
    void loseLife(int *currentLives);
};

#endif // MAINWINDOW_H

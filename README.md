# Treasure Hunt Qt Starter

An educational **Qt Widgets** game starter project for **CSCE 1001: Fundamentals of Computing I**. Students complete the marked TODO sections in `mainwindow.cpp` to practice arrays, functions, pointers, loops, conditions, and basic game logic.

## Gameplay

Move the player through the maze, collect treasure and the key, avoid enemies, and reach the exit. The starter code includes the GUI and project structure; the student exercises complete the game behavior.

### Controls

| Key | Action |
| --- | --- |
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |
| `R` | Restart after winning or losing |

### Map symbols

- `#` Wall
- `.` Empty path
- `T` Treasure
- `K` Key
- `X` Exit
- Yellow circle Player
- Red circles Enemies

## Requirements

- Qt Creator
- A desktop Qt Widgets kit
- A C++ compiler supported by the installed Qt version

## Build and run

1. Open `TreasureHunt.pro` in Qt Creator.
2. Select an installed desktop Qt kit when prompted.
3. Build the project.
4. Run the application.

The project uses Qt Widgets and C++11.

## Project structure

- `TreasureHunt.pro` - qmake project file
- `main.cpp` - application entry point
- `mainwindow.h` - window, maze, and game-state declarations
- `mainwindow.cpp` - drawing code and student implementation exercises

## Student exercises

The TODO sections in `mainwindow.cpp` cover initialization, player movement, move validation, enemy detection and movement, item collection, collision handling, win/loss state, and pointer-based score/life updates. Enemy movement is an optional extension that can be simplified by the instructor.

## Repository hygiene

Qt Creator user settings, macOS metadata, and generated build directories are excluded by `.gitignore`. Build artifacts should not be committed.

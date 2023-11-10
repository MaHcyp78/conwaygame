#define ROWS 10
#define COLS 10

#include <stdio.h>
int grid[ROWS][COLS];
void initializeGrid() {
    // Изначально все клетки мертвые
    for (int i = 0; i < ROWS; i++) { 
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }

    // Первое поколение живых клеток
    grid[2][3] = 1;
    grid[3][4] = 1;
    grid[4][2] = 1;
    grid[4][3] = 1;
    grid[4][4] = 1;
}
int countLiveNeighbors(int row, int col) {
    int count = 0;

    // Проверяем все соседние клетки
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            // Пропускаем саму клетку
            if (i == row && j == col) {
                continue;
            }

            // Проверяем, находится ли ячейка в пределах границ и жива ли она
            if (i >= 0 && i < ROWS && j >= 0 && j < COLS && grid[i][j] == 1) {
                count++;
            }
        }
    }

    return count; // Возвращаем кол-во живых клеток
}

void updateGrid() {
    int newGrid[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            newGrid[i][j] = grid[i][j];
        }
    }

    // Обновляем каждую ячейку по правилам
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int liveNeighbors = countLiveNeighbors(i, j);

            if (grid[i][j] == 1) {
                // Ячейка живая
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    // Любая живая клетка, имеющая менее двух живых соседей или более трех живых соседей, умирает
                    newGrid[i][j] = 0;
                }
            }
            else {
                // Клетка и так мертва
                if (liveNeighbors == 3) {
                    // Любая мертвая клетка с тремя живыми соседями, становится живой
                    newGrid[i][j] = 1;
                }
            }
        }
    }
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}
void printGrid() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == 1) {
                printf("* ");
            }
            else {
                printf(". ");
            }
        }
        printf("\n");
    }
}
int main() {
    initializeGrid();

    for (int generation = 1; generation <= 10; generation++) {
        printf("Generation %d:\n", generation);
        printGrid();
        printf("\n");

        updateGrid();
    }

    return 0;
}

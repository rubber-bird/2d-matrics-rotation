#include <iostream>
#include <cmath>

int** initializeMatrix(int rows, int cols) {
    int **matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void fillMatrix(int **matrix, int rows, int cols, int value) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = value;
}

int** rotateMatrix(int **p, int rows, int cols, double angle) {
    int **temp = initializeMatrix(rows, cols);

    fillMatrix(temp, rows, cols, 0);

    double delta = angle * M_PI / 180.0;

    const double HALF_X = (cols - 1) / 2.0;
    const double HALF_Y = (rows - 1) / 2.0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            double x = j - HALF_X;
            double y = i - HALF_Y;

            double srcX = x * cos(delta) + y * sin(delta);
            double srcY = -x * sin(delta) + y * cos(delta);

            int sj = round(srcX + HALF_X);
            int si = round(srcY + HALF_Y);

            if (sj >= 0 && sj < cols && si >= 0 && si < rows) {
                temp[i][j] = p[si][sj];
            }
        }

    return temp;
}

void printMatrix(int **p, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << p[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void normalizeMatrixValues(int **p, int rows, int cols, int rangeMin, int rangeMax) {
    int maxVal = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (p[i][j] > maxVal)
                maxVal = p[i][j];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            p[i][j] = p[i][j] * (rangeMax - rangeMin) / maxVal + rangeMin;
}

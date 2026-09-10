#include <iostream>
#include <cmath>

double** initializeMatrix(int rows, int cols) {
    double **matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    return matrix;
}

void fillMatrix(double **matrix, int rows, int cols, double value) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = value;
}

double** rotateMatrix(double **p, int rows, int cols, double angle) {
    double **temp = initializeMatrix(rows, cols);

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

void printMatrix(double **p, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << p[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double mse(double **a, double **b, int rows, int cols) {
    double sum = 0.0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            double diff = a[i][j] - b[i][j];
            sum += diff * diff;
        }
    return sum / (rows * cols);
}

void normalizeMatrixValues(double **p, int rows, int cols, double rangeMin, double rangeMax) {
    double maxVal = 0;
    double minVal = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            if (p[i][j] > maxVal)
                maxVal = p[i][j];
            else if (p[i][j] < minVal)
                minVal = p[i][j];
        }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            p[i][j] = p[i][j] * (rangeMax - rangeMin) / (maxVal - minVal) + rangeMin;
}

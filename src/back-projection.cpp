#include "matrix.h"

void backProjection(int** p, int rows, int cols) {
  int** result = initializeMatrix(rows, cols);
  fillMatrix(result, rows, cols, 0);

  for (int i = 0; i < 180; i++) {
    /**
     * Matrix in which we "backproject" the values of cols from 
     * sinogram row
     */
    int** projection_matrix = initializeMatrix(rows, cols);
    fillMatrix(projection_matrix, rows, cols, 0);
    
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++)
        projection_matrix[row][col] = p[i][col];

    int** rotatedProjectionMatrix = rotateMatrix(projection_matrix, rows, cols, i);

    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++)
        result[row][col] += rotatedProjectionMatrix[row][col];
  }

  normalizeMatrixValues(result, rows, cols, 0, 255);

  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++)
      p[row][col] = result[row][col];
}

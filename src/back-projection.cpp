#include "matrix.h"

#include <iostream>

void backProjection(double** p, int rows, int cols) {
  double** result = initializeMatrix(rows, cols);
  fillMatrix(result, rows, cols, 0);

  for (int i = 0; i < 180; i++) {
    /**
     * Matrix in which we "backproject" the values of cols from 
     * sinogram row
     */
    double** projection_matrix = initializeMatrix(rows, cols);
    fillMatrix(projection_matrix, rows, cols, 0);
    
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++)
        projection_matrix[row][col] = p[i][col];

    double** rotatedProjectionMatrix = rotateMatrix(projection_matrix, rows, cols, i);

    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++)
        result[row][col] += rotatedProjectionMatrix[row][col];
  }


  // normalizing
  double min = 9999999.0;
  double max = -9999999.0;
  for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (result[row][col] < min) {
                min = result[row][col];
            }
            if (result[row][col] > max) {
                max = result[row][col];
            }
        }
    }

  std::cout << "Min: " << min << std::endl;
  std::cout << "Max: " << max << std::endl;

  // normalizeMatrixValues(result, rows, cols, 0, 255);
  
  double** tempArray = initializeMatrix(rows, cols);
  fillMatrix(tempArray, rows, cols, 0);
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      result[row][col] = (result[row][col] - min) / (max - min) * 255;
      // tempArray[row][col] = (result[row][col] - min) * 255.0 / (max - min);
    }
  }

  for (int row = 0; row < rows; row++)
    for (int col = 0; col < cols; col++)
      p[row][col] = result[row][col];
}

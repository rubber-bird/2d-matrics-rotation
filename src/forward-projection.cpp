#include "matrix.h"

void forwardProjection(int** p, int rows, int cols) {
  int** result = initializeMatrix(rows, cols);
  fillMatrix(result, rows, cols, 0);

  // rotating the image from 0 to 179 degrees and accumulating the pixel values in the result matrix
  for (int i = 0; i < 180; i++) {
    int** temp = rotateMatrix(p, rows, cols, (-1) * i);

    /**
     * Accumulating stage
     */
    for (int r = 0; r < rows; r++)
      for (int c = 0; c < cols; c++)
        result[i][c] += temp[r][c];

    /**
     * Cleaning up temp
     */
    for (int r = 0; r < rows; r++)
      delete[] temp[r];

    delete[] temp;
  }

  /**
   * Normalizing the result to 0-255 for better visualization in HTML. The values in the result matrix can be greater than 255,
   * so we need to scale them down to fit within the 8-bit color range.
   */
  normalizeMatrixValues(result, rows, cols, 0, 255);

  for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
      p[r][c] = result[r][c];
}

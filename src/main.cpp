#include <iostream>
#include <cmath>

#include "Display.h"
#include "matrix.h"

using namespace std;

// Colors
const int COLOR_GREY = 200;
const int COLOR_GREY_LIGHT = 150;
const int COLOR_WHITE = 255;

// Function prototypes
void loadImage(int** p, int rows, int cols, string fileName);
void processImageWithPhantom(int** p, int rows, int cols);

int main() {
  int width = 180;
  int height = 180;

  int **matrix = initializeMatrix(height, width);

  // Just nullifying the image array before loading new image
  fillMatrix(matrix, height, width, 0);
  
  /**
   * Processing phantom_01
   */
  loadImage(matrix, height, width, "./data/shapesPhantom.txt");
  Display image01Pixels(matrix, height, width, "./output/Phantom_01_pixels");
  processImageWithPhantom(matrix, height, width);
  Display image01Sinogram(matrix, height, width, "./output/Phantom_01_sinogram");


  // Clean up
  fillMatrix(matrix, height, width, 0);

  /**
   * Processing phantom_02
   */
  loadImage(matrix, height, width, "./data/headPhantom.txt");
  Display image02Pixels(matrix, height, width, "./output/Phantom_02_pixels");
  processImageWithPhantom(matrix, height, width);
  Display image02Sinogram(matrix, height, width, "./output/Phantom_02_sinogram");

  return 0;
}

void processImageWithPhantom(int** p, int rows, int cols) {
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

// void clearImage(int pixels[][N]) {
//   for (int row = 0; row < N; row++)
//     for (int col = 0; col < N; col++)
//       pixels[row][col] = 0;
// }

// void normalizeImageColors(int sinogram[][N]) {
//   // Find max value for normalization to 0-255
//   int maxVal = 0;
//   for (int row = 0; row < N; row++)
//     for (int col = 0; col < N; col++)
//       if (sinogram[row][col] > maxVal) maxVal = sinogram[row][col];

//   for (int row = 0; row < N; row++)
//     for (int col = 0; col < N; col++)
//       sinogram[row][col] = sinogram[row][col] * 255 / maxVal;
// }

// /**
//  * URL = https://www.geeksforgeeks.org/maths/rotation-matrix/
//  * Section of page = 2D Rotation Matrix
//  */
// void rotateImage(int pixels[][N], int newPixels[][N], double angle) {
//   double delta = angle * M_PI / 180.0;

//   // Inverse mapping: for each destination pixel, find source pixel
//   for(int i = 0; i < N; i++) {
//     for(int j = 0; j < N; j++) {
//       double x = j - HALF;
//       double y = i - HALF;

//       double srcX = x * cos(delta) + y * sin(delta);
//       double srcY = -x * sin(delta) + y * cos(delta);

//       int sj = round(srcX + HALF);
//       int si = round(srcY + HALF);

//       if(sj >= 0 && sj < N && si >= 0 && si < N) {
//         newPixels[i][j] = pixels[si][sj];
//       }
//     }
//   }
// }

void loadImage(int** p, int rows, int cols, string fileName) {
    ifstream file;
    file.open(fileName);

    if (!file) {
      cout << "File does not exist!";
      return;
    }

    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            file >> p[row][col];

    file.close();
}

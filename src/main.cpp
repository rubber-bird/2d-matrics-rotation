#include <iostream>
#include <cmath>

#include "Display.h"
#include "matrix.h"
#include "forward-projection.h"
#include "back-projection.h"

using namespace std;

// Colors
const int COLOR_BLACK = 0;
const int COLOR_GREY = 200;
const int COLOR_GREY_LIGHT = 150;
const int COLOR_WHITE = 255;

// Function prototypes
void loadImage(int** p, int rows, int cols, string fileName);

int main() {
  int width = 400;
  int height = 400;

  int **matrix = initializeMatrix(height, width);
  fillMatrix(matrix, height, width, COLOR_BLACK);

  loadImage(matrix, height, width, "./data/sinograms/sinogram-004-400x400.txt");
  Display image04Pixels(matrix, height, width, "./output/sinograms/phantom-004-sinogram");
  backProjection(matrix, height, width);
  Display image04Sinogram(matrix, height, width, "./output/sinograms/phantom-004-backprojection");

  // Clean up
  fillMatrix(matrix, height, width, COLOR_BLACK);

  return 0;
}

void loadImage(int** p, int rows, int cols, string fileName) {
    ifstream file;
    file.open(fileName);

    if (!file) {
      cout << "File " << fileName << " does not exist!";
      return;
    }

    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            file >> p[row][col];

    file.close();
}

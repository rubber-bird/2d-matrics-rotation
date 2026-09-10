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
void loadImage(double** p, int rows, int cols, string fileName);

const int SIZE = 180;

void fourierTransform(
    double initial[SIZE],
    double transformedReal[SIZE],
    double transformedImaginary[SIZE]
) {
    for (int k = 0; k < SIZE; k++) {
        double sumReal = 0;
        double sumImaginary = 0;

        for (int n = 0; n < SIZE; n++) {
            sumReal += (initial[n] * cos((2 * M_PI * k * n) / SIZE));
            sumImaginary += (initial[n] * (sin((2 * M_PI * k * n) / SIZE) * -1));
        }

        transformedReal[k] = sumReal;
        transformedImaginary[k] = sumImaginary;
    }
}

void invertFourierTransform(
    double transformedReal[SIZE],
    double transformedImaginary[SIZE],
    double initial[SIZE]
) {
    for (int n = 0; n < SIZE; n++) {
        double res = 0;

        for (int k = 0; k < SIZE; k++) {
            res
                += ((transformedReal[k] * cos((2 * M_PI * k * n) / SIZE))
                - (transformedImaginary[k] * sin((2 * M_PI * k * n) / SIZE)));
        }

        initial[n] = res / SIZE;
    }
}

void createFilter(double filter[]) {
    double c;
    for (int i = 0; i < SIZE; i++) {
        c = abs(i - SIZE / 2);
        filter[i] = (SIZE - 2 * c) / SIZE;
    }
}

void createGaussianFilter(double filter[], double sigma) {
    createFilter(filter);
    for (int i = 0; i < SIZE; i++) {
        double ramp = filter[i];
        filter[i] = ramp * exp(-(ramp * ramp) / (2 * sigma * sigma));
    }
}

void createCosineFilter(double filter[]) {
    createFilter(filter);
    for (int i = 0; i < SIZE; i++) {
        double ramp = filter[i];
        filter[i] = ramp * cos(M_PI * ramp / 2.0);
    }
}

void createSheppLoganFilter(double filter[]) {
    createFilter(filter);
    for (int i = 0; i < SIZE; i++) {
        double ramp = filter[i];
        filter[i] = (2.0 / M_PI) * sin(M_PI * ramp / 2.0);
    }
}

void createHammingFilter(double filter[]) {
    createFilter(filter);
    for (int i = 0; i < SIZE; i++) {
        double ramp = filter[i];
        filter[i] = ramp * (0.54 + 0.46 * cos(M_PI * ramp));
    }
}

void createHannFilter(double filter[]) {
    createFilter(filter);
    for (int i = 0; i < SIZE; i++) {
        double ramp = filter[i];
        filter[i] = ramp * 0.5 * (1.0 + cos(M_PI * ramp));
    }
}

void createButterworthFilter(double filter[], double cutoff, int order) {
    createFilter(filter);
    for (int i = 0; i < SIZE; i++) {
        double ramp = filter[i];
        filter[i] = ramp / (1.0 + pow(ramp / cutoff, 2 * order));
    }
}

// void applyFilters(double **p, int rows, int cols) {
    
// }

int main() {
  int width = SIZE;
  int height = SIZE;

  double **matrix = initializeMatrix(height, width);
  fillMatrix(matrix, height, width, COLOR_BLACK);

  loadImage(matrix, height, width, "./data/sinograms/sinogram-001-180x180.txt");
//   applyFilters(matrix, height, width);

  double **tempArray = initializeMatrix(height, width);
  fillMatrix(tempArray, height, width, COLOR_BLACK);

  double min = 9999999.9999999;
  double max = -9999999.9999999;

  double rampFilter[SIZE];
  createFilter(rampFilter);
//   createGaussianFilter(rampFilter, 0.5);
//   createCosineFilter(rampFilter);
//   createSheppLoganFilter(rampFilter);
//   createHammingFilter(rampFilter);
    // createHannFilter(rampFilter);
    // createButterworthFilter(rampFilter, 0.5, 2);

  for (int row = 0; row < SIZE; row++) {
    double initial[SIZE];
    double transformedReal[SIZE];
    double transformedImaginary[SIZE];

    for (int col = 0; col < SIZE; col++) {
      initial[col] = matrix[row][col];
    }

    fourierTransform(initial, transformedReal, transformedImaginary);

    for (int i = 0; i < SIZE; i++) {
        transformedReal[i] = rampFilter[i] * transformedReal[i];
            transformedImaginary[i] = rampFilter[i] * transformedImaginary[i];
        }

        invertFourierTransform(transformedReal, transformedImaginary, initial);

        for (int col = 0; col < SIZE; col++) {
            tempArray[row][col] = initial[col];
        }
    }

//     for (int row = 0; row < height; row++) {
//         for (int col = 0; col < width; col++) {
//             if (tempArray[row][col] < min) {
//                 min = tempArray[row][col];
//             }
//             if (tempArray[row][col] > max) {
//                 max = tempArray[row][col];
//             }
//         }
//     }

//   cout << "Min-main.cpp: " << min << endl;
//   cout << "Max-main.cpp: " << max << endl;

//   for (int row = 0; row < height; row++) {
//     for (int col = 0; col < width; col++) {
//         matrix[row][col] = ((tempArray[row][col] - min) / (max - min) * 255);
//     }
//   }

//   Display image04Pixels(matrix, height, width, "./output/sinograms/phantom-004-sinogram");
  backProjection(tempArray, height, width);

  double **phantom = initializeMatrix(height, width);
  fillMatrix(phantom, height, width, COLOR_BLACK);
  loadImage(phantom, height, width, "./data/phantoms/phantom-002-180x180.txt");

  cout << "MSE: " << mse(phantom, tempArray, height, width) << endl;

  Display image04Sinogram(tempArray, height, width, "./output/sinograms/phantom-002-filtered-backprojection");

  // Clean up
  fillMatrix(matrix, height, width, COLOR_BLACK);

  return 0;
}

void loadImage(double** p, int rows, int cols, string fileName) {
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

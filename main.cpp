#include <iostream>
#include <cmath>
#include "Display.h"

using namespace std;

// Image Size N x N
const int N = 180;
const int HALF = (N - 1) / 2;

// Colors
const short COLOR_GREY = 200;
const short COLOR_GREY_LIGHT = 150;
const short COLOR_WHITE = 255;

// Function prototypes
void loadImage(short pixels[][N], string);
void rotateImage(short pixels[][N], short newPixels[][N], double angle);
void clearImage(short pixels[][N]);
void normalizeImageColors(int sinogram[][N]);
void processImageWithPhantom(short Pixels[][N]);

int main() {
  short Pixels[N][N];

  // Just nullifying the image array before loading new image
  clearImage(Pixels);
  
  /**
   * Processing phantom_01
   */
  loadImage(Pixels, "./data/shapesPhantom.txt");
  Display image01Pixels(Pixels, "./output/Phantom_01_pixels");
  processImageWithPhantom(Pixels);
  Display image01Sinogram(Pixels, "./output/Phantom_01_sinogram");


  // Clean up
  clearImage(Pixels);

  /**
   * Processing phantom_02
   */
  loadImage(Pixels, "./data/headPhantom.txt");
  Display image02Pixels(Pixels, "./output/Phantom_02_pixels");
  processImageWithPhantom(Pixels);
  Display image02Sinogram(Pixels, "./output/Phantom_02_sinogram");

  return 0;
}

void processImageWithPhantom(short Pixels[][N]) {
  int sinogram[N][N] = {};

  for (int i = 0; i < N; i++) {
    short newPixels[N][N];

    clearImage(newPixels);
    rotateImage(Pixels, newPixels, (-1) * i);

    for (int row = 0; row < N; row++) {
      for (int col = 0; col < N; col++) {
        sinogram[i][col] += newPixels[row][col];
      }
    }
  }

  normalizeImageColors(sinogram);

  for (int r = 0; r < N; r++)
    for (int c = 0; c < N; c++)
      Pixels[r][c] = (short)sinogram[r][c];
}

void clearImage(short pixels[][N]) {
  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      pixels[row][col] = 0;
}

void normalizeImageColors(int sinogram[][N]) {
  // Find max value for normalization to 0-255
  int maxVal = 0;
  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      if (sinogram[row][col] > maxVal) maxVal = sinogram[row][col];

  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      sinogram[row][col] = sinogram[row][col] * 255 / maxVal;
}

/**
 * URL = https://www.geeksforgeeks.org/maths/rotation-matrix/
 * Section of page = 2D Rotation Matrix
 */
void rotateImage(short pixels[][N], short newPixels[][N], double angle) {
  double delta = angle * M_PI / 180.0;
  double cosineOfDelta = cos(delta);
  double sineOfDelta = sin(delta);

  // Inverse mapping: for each destination pixel, find source pixel
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      double x = j - HALF;
      double y = i - HALF;

      double srcX = x * cosineOfDelta + y * sineOfDelta;
      double srcY = -x * sineOfDelta + y * cosineOfDelta;

      int sj = round(srcX + HALF);
      int si = round(srcY + HALF);

      if(sj >= 0 && sj < N && si >= 0 && si < N) {
        newPixels[i][j] = pixels[si][sj];
      }
    }
  }
}

void loadImage(short pixels[][N], string fileName) {
    ifstream file;
    file.open(fileName);
    if (!file) cout << "File does not exist!";
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            file >> pixels[row][col];
    file.close();
}

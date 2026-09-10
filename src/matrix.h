
double** initializeMatrix(int rows, int cols);

void fillMatrix(double **p, int rows, int cols, double value);

double** rotateMatrix(double **p, int rows, int cols, double angle);

void printMatrix(double **p, int rows, int cols);

void normalizeMatrixValues(double **p, int rows, int cols, double rangeMin, double rangeMax);

double mse(double **a, double **b, int rows, int cols);

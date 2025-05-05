#ifndef MATRIX_H
#define MATRIX_H

double euclidean_distance(double* vec1, double* vec2, int vector_size);
void copy(double** source, double** destination, int rows, int cols);
double** multiply(double** mat1, int mat1_rows, int mat1_cols, double** mat2, int mat2_cols);
double** transpose(double** mat, int rows, int cols);
void differnce_matrix(double** diff, double** mat1, double** mat2, int rows, int cols);
double frobenius_norm_squared(double** mat, int rows, int cols);

#endif
#include <math.h>
#include "array_2d.h"
#include "matrix.h"

/*
 * Calculates the distance (squared) between two vectors
 * param: vec1 - a pointer to the 1st vector of doubles
 * param: vec2 - a pointer to the 2nd vector of doubles
 * param: vector_size - number of elements in vec1 and vec2
 */
double euclidean_distance(double* vec1, double* vec2, int vector_size)
{
    int i;
    double result;
    double diff;
    result = 0;
    for (i = 0; i < vector_size; i++)
    {
        diff = vec1[i] - vec2[i];
        result += (diff * diff);
    }
    return result;
}

/*
 * Copies a 2-d array of doubles
 * param: source - a pointer to the source array
 * param: destination - a pointer to the destination array
 * remark: performs a deep copy of the arrays
 */
void copy(double** source, double** destination, int rows, int cols)
{
    int i, j;
    {
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                destination[i][j] = source[i][j];
            }
        }
    }
}

/*
 * Multiples two matrices
 * param: mat1 - left matrix as a pointer to 2-d array
 * param: mat1_rows - number of rows in the left matrix
 * param: mat1_cols - number of cols in the left matrix (also number of rows in the right matrix)
 * param: mat2 - right matrix as a pointer to 2-d array
 * param: mat2_cols - number of cols in the right matrix
 * return: multiplication result as a newly allocated 2-d array
 */
double** multiply(double** mat1, int mat1_rows, int mat1_cols, double** mat2, int mat2_cols)
{
    double** result;
    int i, j, k;
    double sum;
    result = allocate_two_dimension_array(mat1_rows, mat2_cols);
    if (result != 0)
    {
        for (i = 0; i < mat1_rows; i++)
        {
            for (j = 0; j < mat2_cols; j++)
            {
                sum = 0;
                for (k = 0; k < mat1_cols; k++)
                {
                    sum += mat1[i][k] * mat2[k][j];
                }
                result[i][j] = sum;
            }
        }
    }
    return result;
}

/*
 * Transposes a matrix
 * param: mat - matrix as a pointer to 2-d array
 * param: rows - number of rows in the matrix
 * param: cols - number of cols in the matrix
 * return: transpose result as a newly allocated 2-d array
 */
double** transpose(double** mat, int rows, int cols)
{
    double** result;
    int i, j;
    result = allocate_two_dimension_array(cols, rows);
    if (result != 0)
    {
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                result[j][i] = mat[i][j];
            }
        }
    }
    return result;
}

/*
 * Calculates a subtraction of 2 matrices
 * param: diff - result matrix as a pointer to 2-d array
 * param: mat1 - matrix to subtract from as a pointer to 2-d array
 * param: mat2 - matrix to be subtracted as a pointer to 2-d array
 * param: rows - number of rows in the matrix
 * param: cols - number of cols in the matrix
 */
void differnce_matrix(double** diff, double** mat1, double** mat2, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            diff[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

/*
 * Calclates the frobenius normal (squared) of a matrix
 * param: mat - matrix as a pointer to 2-d array
 * param: rows - number of rows in the matrix
 * param: cols - number of cols in the matrix
 * return: the frobenius matrix (squared)
 */
double frobenius_norm_squared(double** mat, int rows, int cols)
{
    int i, j;
    double result;
    result = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            result += mat[i][j] * mat[i][j];
        }
    }
    return result;
}
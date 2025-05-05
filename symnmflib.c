#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "symnmflib.h"
#include "array_2d.h"
#include "matrix.h"

#define BETA 0.5
#define EPSILON 0.0001
#define MAX_ITER 300

void update_H(double** H, double** H_new, double** W, int n, int k);

/*
 * calculates the similarity matrix of the datapoints
 * param: pointer to the datapoints arranged as a 2-d array of doubles
 * param: num_datapoints - the number of datapoints (vectors)
 * param: datapoint_size - the number of elements in each datapoint (vector)
 * return: the similarity matrix as a newly allocated 2-d array
 */
double** sym(double** datapoints, int num_datapoints, int datapoint_size)
{
    double** result;
    int i, j;
    double value;
    result = allocate_two_dimension_array(num_datapoints, num_datapoints);
    if (result != 0)
    {
        for (i=0; i<num_datapoints - 1; i++)
        {
            result[i][i] = 0;
            for (j = i + 1; j < num_datapoints; j++)
            {
                value = exp(-0.5 * euclidean_distance(datapoints[i], datapoints[j], datapoint_size));
                result[i][j] = value;
            result[j][i] = value;
            }
        }
        result[num_datapoints - 1][num_datapoints - 1] = 0;
    }
    return result;
}

/*
 * calculates the diagonal degree matrix of the datapoints
 * param: pointer to the datapoints arranged as a 2-d array of doubles
 * param: num_datapoints - the number of datapoints (vectors)
 * param: datapoint_size - the number of elements in each datapoint (vector)
 * return: the diagonal degree matrix as a newly allocated 2-d array
 * remark: first stage is getting the similarity matrix
 */
double** ddg(double** datapoints, int num_datapoints, int datapoint_size)
{
    double** sym_matrix;
    double** result;
    int i, j;
    double sum;

    sym_matrix = sym(datapoints, num_datapoints, datapoint_size);
    result = allocate_two_dimension_array(num_datapoints, num_datapoints);
    if (result != 0)
    {
        for (i = 0; i < num_datapoints; i++)
        {
            sum = 0;
            for (j = 0; j < num_datapoints; j++)
            {
                sum += sym_matrix[i][j];
            }

            for (j = 0; j < num_datapoints; j++)
            {
                result[i][j] = (i == j ? sum : 0.0);
            }
        }
    }
    free_two_dimension_array(sym_matrix, num_datapoints);
    return result;
}

/*
 * calculates the normalized similarity matrix of the datapoints
 * param: pointer to the datapoints arranged as a 2-d array of doubles
 * param: num_datapoints - the number of datapoints (vectors)
 * param: datapoint_size - the number of elements in each datapoint (vector)
 * return: the normalized similarity matrix as a newly allocated 2-d array
 * remark: first stage is getting the similarity matrix
 *         second stage is getting the diagonal degree matrix. Since it is diagonal
 *         and the values are to be powered by -0.5, it is converted to a 1-d array
 *         of the values in the diagonal powered by -0.5
 */
double** norm(double** datapoints, int num_datapoints, int datapoint_size)
{
    double** sym_matrix;
    double** ddg_matrix;
    double** result;
    int i, j;
    double *sqrt_ddg;

    result = 0;
    sym_matrix=sym(datapoints, num_datapoints, datapoint_size);
    ddg_matrix=ddg(datapoints, num_datapoints, datapoint_size);
    sqrt_ddg=(double*)malloc(num_datapoints * sizeof(double));
    if (sqrt_ddg != 0)
    {
        for (i = 0; i < num_datapoints; i++)
        {
            sqrt_ddg[i] = 1.0 / sqrt(ddg_matrix[i][i]);
        }
        free_two_dimension_array(ddg_matrix, num_datapoints);
    
        result = allocate_two_dimension_array(num_datapoints, num_datapoints);
        if (result != 0)
        {
            for (i = 0; i < num_datapoints; i++)
            {
                for (j = 0; j < num_datapoints; j++)
                {
                    result[i][j] = sqrt_ddg[i] * sym_matrix[i][j] * sqrt_ddg[j];
                }
            }
        }
        free(sqrt_ddg);
    }
    free_two_dimension_array(sym_matrix, num_datapoints);
    return result;
}

/*
 * calculates the optimized decomposition matrix H using the symmetric Non-negative Matrix Factorization model
 * param: H_initial - pointer to the initial decomposition matrix arranged as a 2-d array of doubles
 * param: W - pointer to the normalized similarity matrix of the datapoints
 * param: n - the number of datapoints
 * param: k - number of elements in the decomposition matrix H
 * return: the optimized decomposition matrix as a newly allocated 2-d array
 */
double** symnmf(double** H_initial, double** W, int n, int k)
{
    double** H;
    double** H_new;
    double** diff;
    int iteration;
    double diff_squared;

    H = allocate_two_dimension_array(n, k);
    H_new = allocate_two_dimension_array(n, k);
    diff = allocate_two_dimension_array(n, k);

    copy(H_initial, H, n, k);

    for (iteration = 0; iteration < MAX_ITER; iteration++)
    {
        update_H(H, H_new, W, n, k);
        differnce_matrix(diff, H_new, H, n, k);
        diff_squared = frobenius_norm_squared(diff, n, k);
        if (diff_squared < EPSILON) break;
        copy(H_new, H, n, k);
    }

    free_two_dimension_array(diff, n);
    free_two_dimension_array(H, n);
    return H_new;
}

/*
 * Updates the decomposition matrix H
 * param: H - pointer to the current decomposition matrix arranged as a 2-d array of doubles
 * param: H_new - pointer to the updated decomposition matrix arranged as a 2-d array of doubles
 * param: W - pointer to the normalized similarity matrix of the datapoints
 * param: n - the number of datapoints
 * param: k - number of elements in the decomposition matrix H
 */
void update_H(double** H, double** H_new, double** W, int n, int k)
{
    double** W_H;
    double** H_trans;
    double** H_H_trans;
    double** H_H_trans_H;
    int row, col;

    W_H = multiply(W, n, n, H, k);
    H_trans = transpose(H, n, k);
    H_H_trans = multiply(H, n, k, H_trans, n);
    H_H_trans_H = multiply(H_H_trans, n, n, H, k);

    for (row = 0; row < n; row++)
    {
        for (col = 0; col < k; col++)
        {
            H_new[row][col] = H[row][col] * (1 - BETA + BETA * W_H[row][col] / H_H_trans_H[row][col]);
        }
    }
    free_two_dimension_array(H_H_trans_H, n);
    free_two_dimension_array(H_H_trans, n);
    free_two_dimension_array(H_trans, k);
    free_two_dimension_array(W_H, n);
}
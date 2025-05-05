#include <stdio.h>
#include <stdlib.h>
#include "array_2d.h"

/*
 * Allocates a 2-dimension array of doubles
 * param: rows - number of rows in the array
 * param: cols - number of cols in the array
 * return: pointer to the new 2-dimension array of doubles
 */
double** allocate_two_dimension_array(int rows, int cols)
{
    int i;
    double* row;
    double** result = (double**)malloc(rows * sizeof(double*));
    if (result != 0)
    {
        for (i = 0; i < rows; i++)
        {
            row = (double*)malloc(cols * sizeof(double));
            if (row == 0)
            {
                free (result);
                return 0;
            }
            result[i] = row;
        }
    }
    return result;    
}

/*
 * Frees a 2-dimension array of doubles
 * param: array - the array to be freed
 * param: rows - number of rows in the array
 */
void free_two_dimension_array(double** array, int rows)
{
    int i;
    for (i = 0; i < rows; i++)
    {
        free(array[i]);
    }
    free (array);    
}

/*
 * Prints a 2-dimension array of doubles to the console (STDOUT)
 * param: array - the array to be printed
 * param: rows - number of rows in the array
 * param: cols - number of cols in the array
 * remark: The numbers are formatted with 4 decimal digits
 */
void print_two_dimension_array(double** array, int rows, int cols)
{
    int i;
    int j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%.4f", array[i][j]);
            if (j == cols - 1)
            {
                printf("\n");
            }
            else
            {
                printf(",");
            }
        }
    }
}
#ifndef ARRAY_2D_H
#define ARRAY_2D_H

double** allocate_two_dimension_array(int num_rows, int num_cols);
void free_two_dimension_array(double** array, int num_rows);
void print_two_dimension_array(double** array, int rows, int cols);

#endif
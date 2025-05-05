#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "symnmflib.h"
#include "datapoint_file.h"
#include "array_2d.h"

#define GENERAL_ERROR "An Error Has Occurred\n"
#define SYM_CHOICE "sym"
#define DDG_CHOICE "ddg"
#define NORM_CHOICE "norm"

int main (int argc, char** argv)
{
    double** datapoints;
    double** H;
    double** W;
    double** result;

    int num_datapoints;
    int datapoint_size;
    int k;
    char* filename;
    int i, j;

    if (argc != 3)
    {
        printf(GENERAL_ERROR);
        return 1;
    }
    k = atoi(argv[1]);
    filename = argv[2];
    
    datapoints = read_datapoints_from_file(filename, &num_datapoints, &datapoint_size);

    result = sym(datapoints, num_datapoints, datapoint_size);
    print_two_dimension_array(result, num_datapoints, num_datapoints);
    free_two_dimension_array(result, num_datapoints);

    result = ddg(datapoints, num_datapoints, datapoint_size);
    print_two_dimension_array(result, num_datapoints, num_datapoints);
    free_two_dimension_array(result, num_datapoints);

    result = norm(datapoints, num_datapoints, datapoint_size);
    print_two_dimension_array(result, num_datapoints, num_datapoints);
    free_two_dimension_array(result, num_datapoints);

    H = allocate_two_dimension_array(num_datapoints, k);
    srand(time(NULL));
    
    for (i = 0; i < num_datapoints; i++)
    {
        for (j = 0; j < k; j++)
        {
            H[i][j] = rand() / (double) RAND_MAX;
        }
    }

    W = norm(datapoints, num_datapoints, datapoint_size);

    result = symnmf(H, W, num_datapoints, k);
    print_two_dimension_array(result, num_datapoints, k);
    free_two_dimension_array(result, num_datapoints);
    free_two_dimension_array(W, num_datapoints);
    free_two_dimension_array(H, num_datapoints);
    free_two_dimension_array(datapoints, num_datapoints);
    return 0;
}
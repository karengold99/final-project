#include <stdio.h>
#include <string.h>
#include "symnmflib.h"
#include "datapoint_file.h"
#include "array_2d.h"

#define GENERAL_ERROR "An Error Has Occurred\n"
#define SYM_CHOICE "sym"
#define DDG_CHOICE "ddg"
#define NORM_CHOICE "norm"

int process_data(char* goal, char* filename);

/*
 * main entry. checks for appropriate number of args and calls process_data
 * param: argc - number of arguments
 * param: argv -array of arguments
 * return: error code. 0 if OK
 */
int main (int argc, char** argv)
{
    int process_status;
    if (argc != 3)
    {
        printf(GENERAL_ERROR);
        return 1;
    }
    process_status = process_data(argv[1], argv[2]);
    if (process_status == 1)
    {
        printf(GENERAL_ERROR);
        return 1;
    }
    return 0;
}

/*
 * Processes the data, calls the proper function and prints the results
 * param: goal - the function to be performed as a string
 * param: filename - file to be processed containing the datapoints
 * return: error code. 0 if OK
 */
int process_data(char* goal, char* filename)
{
    double** datapoints;
    double** result;

    int num_datapoints, datapoint_size;
    datapoints = read_datapoints_from_file(filename, &num_datapoints, &datapoint_size);
    
    if (strcmp(goal, SYM_CHOICE) == 0)
    {
        result = sym(datapoints, num_datapoints, datapoint_size);
    }
    else if (strcmp(goal, DDG_CHOICE) == 0)
    {
        result = ddg(datapoints, num_datapoints, datapoint_size);
    }
    else if (strcmp(goal, NORM_CHOICE) == 0)
    {
        result = norm(datapoints, num_datapoints,datapoint_size);
    }
    else return 1;

    print_two_dimension_array(result, num_datapoints, num_datapoints);
    free_two_dimension_array(result, num_datapoints);
    free_two_dimension_array(datapoints, num_datapoints);
    return 0;
}
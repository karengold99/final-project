#include <stdio.h>
#include <stdlib.h>
#include "datapoint_file.h"

#define READ_BUFFER_SIZE 300
#define INITIAL_CAPACITY 16
#define MAX_DATAPOINT_LENGTH 30

int get_datapoint_length(char* buffer);
void get_datapoint_elements(double* datapoint, char* buffer);
int read_line(FILE* file, char* buffer);
double** expand_datapoints_array(double** array, int current_capacity, int new_capacity);
void get_datapoint_elements(double* datapoint, char* buffer);

/*
 * Reads a datapoints file
 * param: filename - the filename to read from
 * param: num_datapoints - the number of datapoints (vectors) read from the file. Returns the value to caller
 * param: datapoint_size - the number of elements in each datapoint (vector) read from the file. Returns the value to caller
 * return: pointer to the datapoints arranged as a 2-d array of doubles 
 * remark: opens the file and reads lines of chars until no more lines are avaiable
 *         each input line is read into a new array of doubles
 *         uses an automatic size array which doubles in capacity when the size reaches current capacity
 */
double** read_datapoints_from_file(char* filename, int* num_datapoints, int* datapoint_size)
{
    int capacity = INITIAL_CAPACITY;
    double** result = (double**)malloc(capacity * sizeof(double*));
    FILE* file;
    char* buffer;

    int size = 0;
    int datapoint_length = 0;
    file = fopen(filename, "r");
    buffer = (char*)malloc(READ_BUFFER_SIZE * sizeof(char));
    while(1)
    {
        int len = read_line(file, buffer);
        if (len == 0) break;
        if (datapoint_length == 0) 
        {
            datapoint_length = get_datapoint_length(buffer);
        }
        if (size == capacity)
        {
            int new_capacity = capacity * 2;
            result = expand_datapoints_array(result, capacity, new_capacity);
            capacity = new_capacity;
        }
        result[size] = (double*)malloc(datapoint_length * sizeof(double));
        get_datapoint_elements(result[size], buffer);
        size++;
    }
    fclose(file);
    free (buffer);
    *num_datapoints = size;
    *datapoint_size = datapoint_length;
    return result;
}

/*
 * Reads a line from datapoints file
 * param: file - a pointer to the data file structure
 * param: buffer - a pointer to the char buffer
 * return: the length of the line read to buffer
 */
int read_line(FILE* file, char* buffer)
{
    int pointer = 0;
    while (1)
    {
        int character_read = fgetc(file);
        if (character_read == '\n' || character_read == EOF) break;
        buffer[pointer++] = character_read;
    }
    buffer[pointer] = '\0';
    return pointer;
}

/*
 * Calculates the number of elements in a datapoint
 * param: buffer - a pointer to the char buffer containing an input line
 * return: the number of elements in a datapoint (vector)
 * remark: the number of elements is the number of commas in the line plus 1
 */
int get_datapoint_length(char* buffer)
{
    int counter = 0;
    int loc = 0;
    while (buffer[loc] != '\0')
    {
        if (buffer[loc] == ',')
        {
            counter++;
        }
        loc++;
    }
    return counter + 1;
}

/*
 * Expands an array of double vectors 
 * param: array - the 2-d double array
 * param: current_capacity - the current capacity of the array
 * param: new_capacity - the required capacity of the array
 * return: a pointer to the new array
 * remark: allocates a new array of pointers, copies the content of the old array and frees the old array
 */
double** expand_datapoints_array(double** array, int current_capacity, int new_capacity)
{
    int i;
    double** new_array;
    new_array = (double**)malloc(new_capacity * sizeof(double*));
    for (i = 0; i < current_capacity; i++)
    {
        new_array[i] = array[i];
    }
    free(array);
    return new_array;
}

/*
 * Reads numbers from an input line and fills a datapoint array
 * param: datapoint - a pointer to the datapoint to be filled
 * param: buffer - a pointer to the char buffer containing an input line
 * remark: seeks numbers separated by commas
 */
void get_datapoint_elements(double* datapoint, char* buffer)
{
    int element, number_loc, buffer_loc, end_of_string;
    char* number_string;
    number_string = (char*)malloc(MAX_DATAPOINT_LENGTH * sizeof(char));
    element = 0;
    number_loc = 0;
    buffer_loc = 0;
    end_of_string = 0;
    while (!end_of_string)
    {
        char c = buffer[buffer_loc];
        if (c == '\0')
        {
            end_of_string = 1;
        }
        if (c == ',')
        {
            c = '\0';
        }
        number_string[number_loc] = c;
        number_loc++;
        buffer_loc++;
        if (c == '\0')
        {
            datapoint[element] = atof(number_string);
            element++;
            number_loc=0;
        }
     }
    free(number_string);
}
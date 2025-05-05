#include "python_args.h"
#include "array_2d.h"

double** get_two_dimension_double_array(PyObject* arg, int* p_rows, int* p_cols)
{
    int i, j, rows, cols;
    double** result;
    PyObject* firstRow;
    PyObject* row;
    PyObject* item;

    rows = PyList_Size(arg);
    if (rows < 0)
    {
        return NULL;
    }

    firstRow = PyList_GetItem(arg, 0);
    if (!PyList_Check(firstRow))
    {
        return NULL;
    }

    cols = PyList_Size(firstRow);

    result = allocate_two_dimension_array(rows, cols);

    for (i = 0; i < rows; i++)
    {
        row = PyList_GetItem(arg, i);
        if (!PyList_Check(row)) 
        {
            return NULL;
        }
        for (j = 0; j < cols; j++) 
        {
            item = PyList_GetItem(row, j);
            result[i][j] = PyFloat_AsDouble(item);
        }
    }

    *p_rows = rows;
    *p_cols = cols;
    return result;
}

PyObject* create_python_return_two_dimension_array(double** array, int rows, int cols)
{
    int i, j;
    PyObject* py_list_of_lists;
    PyObject* py_row;
    PyObject* py_value;

    if (array == NULL)
    {
        return NULL; 
    }

    py_list_of_lists = PyList_New(rows);
    if (!py_list_of_lists) 
    {
        return NULL; 
    }

    for (i = 0; i < rows; i++) 
    {
        py_row = PyList_New(cols);
        if (!py_row)
        {
            Py_DECREF(py_list_of_lists);
            return NULL;
        }

        for (j = 0; j < cols; j++) 
        {
            py_value = PyFloat_FromDouble(array[i][j]);
            if (!py_value) 
            {
                Py_DECREF(py_row);
                Py_DECREF(py_list_of_lists);
                return NULL;
            }
            PyList_SetItem(py_row, j, py_value);
        }

        PyList_SetItem(py_list_of_lists, i, py_row);
    }

    return py_list_of_lists;
}

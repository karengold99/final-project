#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifndef PYTHON_ARGS_H
#define PYTHON_ARGS_H

double** get_two_dimension_double_array(PyObject* arg, int* rows, int* cols);
PyObject* create_python_return_two_dimension_array(double** array, int rows, int cols);

#endif
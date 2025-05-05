#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "python_args.h"
#include "symnmflib.h"
#include "array_2d.h"

#define SYM 0
#define DDG 1
#define NORM 2

/*
 * Exported function - Calculates the optimized decomposition matrix using symNMF
 * param: self - the instance of the Python Object. usually null
 * param: args - a Python object containing the arguments for the calculation as Python tuples
 * param: function - determines which function will be called
 * return: a PyObject containing the required reuslt based on function
 * remark: gets the initial decomposition matrix as an array and its size from the 1st arg in args
 *         gets the normalized similarity matrix of the datapoints as an array and its size from the 2nd arg in args
 *         checks for errors and if there are none calls the symnmf function from the library. any error will return a NULL
 */ 
static PyObject* py_symnmf(PyObject* self, PyObject* args)
{
    double** h_initial;
    double** w_norm_sim;
    double** final_h;

    int h_initial_rows, h_initial_cols;
    int w_norm_sim_rows, w_norm_sim_cols;

    PyObject* h_initial_from_python;
    PyObject* w_norm_sim_from_python;
    PyObject* result;

    if (!PyArg_ParseTuple(args, "OO", &h_initial_from_python, &w_norm_sim_from_python)) return NULL;
    h_initial = get_two_dimension_double_array(h_initial_from_python, &h_initial_rows, &h_initial_cols);
    if (h_initial == NULL) return NULL;

    w_norm_sim = get_two_dimension_double_array(w_norm_sim_from_python, &w_norm_sim_rows, &w_norm_sim_cols);
    if (w_norm_sim == NULL || w_norm_sim_rows != w_norm_sim_cols || h_initial_rows != w_norm_sim_rows) return NULL;
 
    final_h = symnmf(h_initial, w_norm_sim, h_initial_rows, h_initial_cols);
    result =  create_python_return_two_dimension_array(final_h, h_initial_rows, h_initial_cols);

    free_two_dimension_array(final_h, h_initial_rows);
    free_two_dimension_array(w_norm_sim, h_initial_rows);
    free_two_dimension_array(h_initial, h_initial_rows);

    return result;
}

/*
 * Calculates a function of the datapoints using input from Python
 * param: self - the instance of the Python Object. usually null
 * param: args - a Python object containing the arguments for the calculation as Python tuples
 * param: function - determines which function will be called
 * return: a PyObject containing the required reuslt based on function
 * remark: gets the datapoints array and its size from the single arg in args
 *         then calls the appropriate function. Any error will return a NULL
 */
static PyObject* py_get_result_by_function(PyObject* self, PyObject* args, int function)
{
    double** datapoints;
    double** function_result;
    int num_datapoints, datapoints_size;
    PyObject* datapoints_from_python;
    PyObject* result;

    if (!PyArg_ParseTuple(args, "O", &datapoints_from_python)) return NULL; 
    datapoints = get_two_dimension_double_array(datapoints_from_python, &num_datapoints, &datapoints_size);
    if (datapoints == NULL) return NULL;

    switch (function)
    {
        case SYM:
            function_result = sym(datapoints, num_datapoints, datapoints_size);
            break;
        case DDG:
            function_result = ddg(datapoints, num_datapoints, datapoints_size);
            break;
        case NORM:
            function_result = norm(datapoints, num_datapoints, datapoints_size);
            break;
        default:
            return NULL;
    }
    result =  create_python_return_two_dimension_array(function_result, num_datapoints, num_datapoints);
    free_two_dimension_array(function_result, num_datapoints);
    free_two_dimension_array(datapoints, num_datapoints);
    return result;
}

/*
 * Exported function - calculates the similarity matrix of the datapoints using input from Python
 * param: self - the instance of the Python Object. usually null
 * param: args - a Python object containing the arguments for the calculation as Python tuples
 * return: a PyObject containing the similarity matrix
 * remark: calls py_get_result_by_function with the parameter SYM
 */
static PyObject* py_sym(PyObject* self, PyObject* args)
{
    return py_get_result_by_function(self, args, SYM);
}

/*
 * Exported function - calculates the diagonal degree matrix of the datapoints using input from Python
 * param: self - the instance of the Python Object. usually null
 * param: args - a Python object containing the arguments for the calculation as Python tuples
 * return: a PyObject containing the diagonal degree matrix
 * remark: calls py_get_result_by_function with the parameter DDG
 */
static PyObject* py_ddg(PyObject *self, PyObject *args)
{
    return py_get_result_by_function(self, args, DDG);
}

/*
 * Exported function - calculates the normalized similarity matrix of the datapoints using input from Python
 * param: self - the instance of the Python Object. usually null
 * param: args - a Python object containing the arguments for the calculation as Python tuples
 * return: a PyObject containing the normalized similarity matrix
 * remark: calls py_get_result_by_function with the parameter NORM
 */
static PyObject* py_norm(PyObject *self, PyObject *args)
{
    return py_get_result_by_function(self, args, NORM);
}

/*
 * exported method table as an array of Python Method Definitions
 */
static PyMethodDef MyMethods[] = {
    {"symnmf", py_symnmf, METH_VARARGS, "Get the optimized decomposition matrix using symNMF"},
    {"sym", py_sym, METH_VARARGS, "Get similarity matrix"},
    {"ddg", py_ddg, METH_VARARGS, "Get the diagonal degree matrix"},
    {"norm", py_norm, METH_VARARGS, "Get the normalized similarity matrix"},
    {NULL, NULL, 0, NULL}
};

/*
 * Python module definition struct
 */
static struct PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    "symnmfsp",
    NULL, // Module documentation (can be NULL)
    -1,
    MyMethods
};

/*
 * Python module initialization
 * return: a PyObject describing the module and exported methods
 */
PyMODINIT_FUNC PyInit_symnmfsp(void) 
{
    PyObject* m;
    m = PyModule_Create(&mymodule);
    if (!m) {
        return NULL;
    }
    return m;
}
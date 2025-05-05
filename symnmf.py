import numpy as np
import sys
import symnmfsp as nmf

GENERAL_ERROR = "An Error Has Occurred"
SYMNMF_CHOICE = "symnmf"
SYM_CHOICE = "sym"
DDG_CHOICE = "ddg"
NORM_CHOICE = "norm"

def main():
    """
    Program Entry. Performs a calculation on datapoint vectors in a file according to the goal argument
    """
    args = sys.argv
    if len(args) != 3:
        error_and_exit
    try:
        k = int(args[1])
    except ValueError as ve:
        error_and_exit
    goal = args[2]
    file_name = args[3]
    datapoints = get_datapoints(file_name)    
    np.random.seed(1234)

    if (goal == SYMNMF_CHOICE):
        result=symnmf(datapoints, k)
    elif (goal == SYM_CHOICE):
        result=nmf.sym(datapoints)
    elif (goal == DDG_CHOICE):
        result=nmf.ddg(datapoints)
    elif (goal == NORM_CHOICE):
        result=nmf.norm(datapoints)
    else:
        error_and_exit
    print_array(result)

def symnmf(datapoints, k):
    """
    Calculates the optimized decomposition matrix using symNMF model
    
    Parameters:
        datapoints (list[list]): 2d array of the datapoint vectors
        k (int): number of elements in the decomposition matrix H
    
    Returns:
        list[list]: a 2d array of the optimized decomposition matrix
    """
    
    W = nmf.norm(datapoints)
    W_average = np.mean(np.array(W))
    
    # initialize the decomposition matrix randomly
    H_initial = []
    for i in range(len(datapoints)):
        H_initial.append([])
        for j in range(k):
            H_initial[i].append(2 * np.sqrt(W_average / k) * np.random.uniform())

    return nmf.symnmf(H_initial, W)

def get_datapoints(file_to_read):
    """
    Read the file to get the datapoint vectors
    
    Parameters:
        file_to_read (str) filename
    
    Returns:
        list[list]: a 2d array of the datapoint vectors
    """
    datapoints=[]
    try:
        with open(file_to_read) as file:
            for line in file:
                new_vector=[]
                strings=line.rstrip().split(',')
                for s in strings:
                    new_vector.append(float(s))
                datapoints.append(new_vector)
    except FileNotFoundError as err:
        error_and_exit
    return datapoints

def print_array(array):
    """
    Prints a 2-d array (list[list])
    
    Parameters:
        array (list[List]): array to print
    """
    for c in array:
        line=""
        for element in c:
            line += ("{e:.4f},").format(e=element)
        print (line[:-1])

def error_and_exit():
    print (GENERAL_ERROR)
    exit()   

if (__name__ == "__main__"):
    main()

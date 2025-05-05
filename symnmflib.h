#ifndef SYMNMFLIB_H
#define SYMNMFLIB_H

double** symnmf(double** H_initial, double** W, int n, int k);
double** sym(double** datapoints, int num_datapoints, int datapoint_size);
double** ddg(double** datapoints, int num_datapoints, int datapoint_size);
double** norm(double** datapoints, int num_datapoints, int datapoint_size);

#endif
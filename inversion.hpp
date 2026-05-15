#ifndef INVERSION_H
#define INVERSION_H

void gaussian_elimination(double* arr_ptr, double* inv_arr_return, int n, double epsilon=1e-6);
void print_matrix(double* arr, int n, std::string title="", int setw_size=10);
void mat_multiply(double* arr_1_ptr, double* arr_2_ptr, int n_1, int m_1, int n_2, int m_2, double* product);
double determinant(double* arr_ptr, int n, double epsilon=1e-9);

#endif


#include <iostream>
#include "inversion.hpp"

int main()
{
    int n = 4;
    int m = 2;
    double* arr_ptr;
    // double arr[n*n] = {  1,  3,  4,  3,
    //                     -1, -3,  7,  8,
    //                      5,  6,  6,  4,
    //                      1,  2,  2,  6
    //                    };

    double arr[n*n] = { 1,  1,  1,  1,
                       -1, -1,  1,  1,
                        0,  0,  1,  1,
                        0,  0,  0,  1
                      };

    arr_ptr = arr;


    double* arr_2_ptr;
    double arr_2[n*m] = { 5, 4,
                          3, 7,
                          4, 3,
                          8, 0 };

    arr_2_ptr = arr_2;

    double  product[n*m];
    double* product_ptr;
    product_ptr = product;

    // mat_multiply(arr_ptr, arr_2_ptr, n, n, n, m, product_ptr);

    double  inverse[n*n];
    double* inverse_ptr;
    inverse_ptr = inverse;

    // std::cout << "determinant = " << determinant(arr, n) << std::endl;

    gaussian_elimination(arr, inverse_ptr, n);

    return 0;
}

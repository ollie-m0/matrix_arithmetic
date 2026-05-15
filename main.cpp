#include <iostream>
#include "inversion.hpp"

int main()
{
    int n = 3;
    double* arr_ptr;
    double arr[n*n] = {  1,  3,  4, // 3,
                        -1, -3,  7, // 8,
                         5,  6,  6 // 4,
                         //1,  2,  2,  6
                       };
    arr_ptr = arr;

    double* arr_2_ptr;
    double arr_2[4*2] = { 5, 4,
                          3, 7,
                          // 4, 3,
                          8, 0 };

    arr_2_ptr = arr_2;

    double  product[3*2];
    double* product_ptr;
    product_ptr = product;

    mat_multiply(arr_ptr, arr_2_ptr, 3, 3, 3, 2, product_ptr);

    double  inverse[n*n];
    double* inverse_ptr;
    inverse_ptr = inverse;

    std::cout << determinant(arr, n) << std::endl;

    // gaussian_elimination(arr, inverse_ptr, n);

    return 0;
}

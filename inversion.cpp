#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

void print_matrix(double* arr, int n, int m, std::string title="", int setw_size=10)
    // An immensely helpful function for bug fixing.
    // Prints an n by m matrix to the terminal.
{
    for (int i=0; i<(setw_size+1)*m; i++)
        std::cout << "_";
    std::cout << "__" << std::endl;
    std::cout << title << std::endl;

    for (int i=0; i<n; i++)
    {
        std::cout << '[';
        for (int j=0; j<m; j++)
        {
            std::cout << ' ' << std::setw(setw_size) << *(arr + i*m + j);
            if (j==m-1) { std::cout << ']' << std::endl; }
        }
    }
    for (int i=0; i<(setw_size+1)*m; i++)
        std::cout << "_";
    std::cout << "__" << std::endl;
}



void change_zero_row(double* arr, double* inv_arr, int n, int row, int column, double epsilon=1e-9)
{
    for (int j=row+1; j<n; j++)
    {
        if (std::fabs(*(arr + j*n + column)) <= epsilon)
        {
            if (j!=n-1) { continue; }
            else
            {
                std::cout << "Error encountered: divide by zero unavoidable. Check that det(matrix) != 0" << std::endl;
                std::abort();
            }
        }
        else
        {
            for (int k=0; k<n; k++)
            {
                *(arr + row*n + k)     += *(arr + j*n + k);
                *(inv_arr + row*n + k) += *(inv_arr + j*n + k);
            }
            break;
        }
    }
}


double determinant(double* arr_ptr, int n, double epsilon=1e-9)
    // This function calculates the determinant of the provided matrix
{
    double det;

    switch (n)
    {
        case 1:
            det = *(arr_ptr);
            break;

        case 2:
            det = *(arr_ptr) * *(arr_ptr + 3) - *(arr_ptr + 1) * *(arr_ptr + 2);
            break;

        default:
            det = 0;
            double sub_arr[(n-1) * (n-1)];
            int m;
            for (int k=0; k<n; k++)
            {
                for (int i=1; i<n; i++)
                {
                    for (int j=0; j<n; j++)
                    {
                        if      (j==k) { continue; }
                        else if (j>k)  { m = j-1;  }
                        else           { m = j;    }

                        sub_arr[(i-1)*(n-1) + m] = *(arr_ptr + i*n + j);
                        // det += determinant(sub_arr, n-1) * arr[n*(i+1)];
                    }
                }
                det += determinant(sub_arr, n-1) * *(arr_ptr + k) * pow(-1, k);
            }
    }
    return det;
}

void mat_multiply(double* arr_1_ptr, double* arr_2_ptr, int n_1, int m_1, int n_2, int m_2, double* product)
    // Calculate the matrix multiplication arr_1 * arr_2
    // where arr_1 is an n_1 by m_1 matrix and arr_2 is an n_2 by m_2 matrix.
{
    if (m_1 != n_2)
    {
        std::cout << "Matricies are not multipliable, as they have incompatible dimensions. Aborting process." << std::endl;
        std::abort();
    }

    for (int k=0; k<n_1; k++)
    {
        for (int j=0; j<m_2; j++)
        {
            *(product + k*m_2 + j) = 0;
            for (int i=0; i<m_1; i++)
            {
                *(product + k*m_2 + j) += *(arr_1_ptr + k*m_1 + i) * *(arr_2_ptr + i*m_2 + j);
            }
        }
    }
    print_matrix(product, n_1, m_2, "product");
}

void gaussian_elimination(double* arr_ptr, double* inv_arr_return, int n, double epsilon=1e-9)
    // This function calculates the inverse of the provided matrix through Gaussian elimination
{
    // Define the identity matrix, which will be returned as the inverted matrix at the end.
    double inv_arr[n*n];
    inv_arr_return = inv_arr;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            inv_arr[n*i+j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Reconstruct the initial array from the pointer.
    double arr[n*n];
    for (int i=0; i<n*n; i++)
    {
        arr[i] = *(arr_ptr + i);
    }

    // Handle the case in which the 0th element is 0
    if (std::fabs(arr[0]) <= epsilon)
    {
        change_zero_row(&arr[0], &inv_arr[0], n, 0, 0, epsilon);
    }


    // Reduce matrix to row-echelon form.
    double factor;
    for (int k=0; k<n-1; k++)
    {

        if (std::fabs(arr[k*(n+1)]) <= epsilon)
        // Avoid divide-by-zero errors
        {
            change_zero_row(&arr[0], &inv_arr[0], n, k, k, epsilon);
        }

        // Matrix reduction
        for (int i=k+1; i<n; i++)
        {
            factor = -(arr[i*n + k] / arr[k*(n+1)]); // Factor by which to multiply kth row before addition to ith row.

            for (int j=0; j<n; j++)
            {
                arr[i*n + j]     += factor * arr[k*n + j];
                inv_arr[i*n + j] += factor * inv_arr[k*n + j];
            }
        }
    }

    // Back substitution
    for (int k=n-1; k>0; k--)
    {
        for (int i=0; i<k; i++)
        {
            factor = -(arr[i*n + k] / arr[k*(n+1)]);
            for (int j=0; j<n; j++)
            {
                arr[i*n + j]     = arr[i*n + j]     + factor * arr[k*n + j];
                inv_arr[i*n + j] = inv_arr[i*n + j] + factor * inv_arr[k*n + j];
            }
        }
    }

    // Divide by relevant factors such that the "old" matrix becomes the identity
    for (int i=0; i<n; i++)
    {
        factor = 1 / arr[n*i + i];
        for (int j=0; j<n; j++)
        {
            inv_arr[n*i + j] = inv_arr[n*i + j] * factor;
            // No need to perform the same opperation on arr[n*i + j],
            // as we are finished with that array.
        }
    }

    // Check for garbage values that should be 0
    for (int i=0; i<n*n; i++)
    {
        inv_arr[i] =  (std::fabs(inv_arr[i]) < epsilon) ? 0.0 : inv_arr[i];
    }

    // Print the matrix (only for small n)
    if (n<=50)
    { print_matrix(&inv_arr[0], n, n, "Inverted matrix:", 10); }

}

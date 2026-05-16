GitHub page: https://github.com/ollie-m0/matrix_arithmetic

# Matrix Arithmetic

This code currently has functions to calculate the determinant and inverse of a square matrix, and the product of two general (real-valued) matricies.

In the future, I wish to write a function to find the eigenvalues and vectors of a matrix, and to extend all of the above to complex-valued matricies.
I also have ideas about parallelising some of the functions, which would be a neat exercise.

## Inversion

The code inverts the provided matrix through Gaussian elimination. The algorithm is very simple. First, we must convert the matrix to row-echelon form.

Consider an $n \times n$ matrix $A$ with elements $A^i_j$. Separating the matrix's rows into row-vectors, $\mathbf{a}^i \equiv (A^i_1, \ldots, A^i_n)$, 
we aim to make the first element of each row zero. To achieve this, we add to each $i \neq 1$ row the first row multiplied by a factor 
$k^i = A^i_1 / A^1_1$. The rows become $\mathbf{a}^i \mapsto \mathbf{a}'^i = \mathbf{a}^i - k^i \mathbf{a}^1$. This gives each row (excluding 
the first) a first element equal to zero, $A^i_1 = 0, i \neq 1$. This process is repeated, this time subtracting from each $i > 2$ row the second row
multiplied by the factor $k^i = A^i_2 / A^2_2$. This is repeated for each row until every element below the diagonal is zero.

Following this, a similar process is used (back-substitution) to make every off-diagonal element zero. The rows are then divided by the numerical value
of their non-zero elements, and the resulting matrix is the identity. 

When all of the above steps are applied to the identity matrix, the result is the inverse of the original matrix, $A^{-1}.

In the standard notation of Gaussian elimination, this process goes as follows:


$$
    \begin{pmatrix}
    A^1_1  & \cdots & A^1_n  & 1 &        &   \\
    \vdots & \ddots & \vdots &   & \ddots &   \\
    A^n_1  & \cdots & A^n_n  &   &        & 1 \\
    \end{pmatrix}       \\
    \rightarrow
    \begin{pmatrix}
    A^1_1                             & \cdots & A^1_n                             & 1                    &        &   \\
    \vdots                            & \ddots & \vdots                            &                      & \ddots &   \\
    A^n_1 - A^1_1 \frac{A^n_1}{A^1_1} & \cdots & A^n_n - A^1_n \frac{A^n_1}{A^1_1} & -\frac{A^n_1}{A^1_1} & \ddots & 1 \\
    \end{pmatrix}
$$




[GitHub page](https://github.com/ollie-m0/matrix_arithmetic)

# Matrix Arithmetic

This code currently has functions to calculate the determinant and inverse of a square matrix, and the product of two general (real-valued) matricies.

In the future, I wish to write a function to find the eigenvalues and vectors of a matrix, and to extend all of the above to complex-valued matricies.
I also have ideas about parallelising some of the functions, which would be a neat exercise.

## Inversion

The code inverts the provided matrix through [Gaussian elimination](https://math.libretexts.org/Courses/Palo_Alto_College/College_Algebra/05:_Systems_of_Equations_and_Inequalities/5.04:_Solving_Systems_with_Gaussian_Elimination). The algorithm is very simple. First, we must convert the matrix to row-echelon form.

Consider an $n \times n$ matrix $A$ with elements $A^i_j$. Separating the matrix's rows into row-vectors, $\mathbf{a}^i \equiv (A^i_1, \ldots, A^i_n)$, 
we aim to make the first element of each row zero. To achieve this, we add to each $i \neq 1$ row the first row multiplied by a factor 
$k^i = A^i_1 / A^1_1$. The rows become $\mathbf{a}^i \mapsto \mathbf{a}'^i = \mathbf{a}^i - k^i \mathbf{a}^1$. This gives each row (excluding 
the first) a first element equal to zero, $A^i_1 = 0, i \neq 1$. This process is repeated, this time subtracting from each $i > 2$ row the second row
multiplied by the factor $k^i = A^i_2 / A^2_2$. This is repeated for each row until every element below the diagonal is zero.

Following this, a similar process is used (back-substitution) to make every off-diagonal element zero. The rows are then divided by the numerical value
of their non-zero elements, and the resulting matrix is the identity. 

When all of the above steps are applied to the identity matrix, the result is the inverse of the original matrix, $A^{-1}.

If a diagonal element of the original matrix is zero, this will lead to a divide by zero error when the multiplication factor is calculated using
this value. To avoid this, the code searches for rows below with non-zero values in the relevant column, and will swap the rows when one is found.
I do not know if there are diagonisable matricies for which there are no suitable rows beneath the diagonal zero. If such a matrix exists, then this
code cannot diagonalise it in its current form.

## Determinant

The code uses [Laplace expansion](https://en.wikipedia.org/wiki/Laplace_expansion) to calculate the determinant of the provided matrix, using a
recursive function.

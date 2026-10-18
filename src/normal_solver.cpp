#include "Group-7-project-ridge-lib/normal_solver.hpp"
#include <cmath>

namespace linear_ml {

Matrix NormalSolver::solve_normal_equation(const Matrix& X, const Matrix& y) {
    // 1. Compute X^T (Transpose of X)
    Matrix XT = X.transpose();

    // 2. Compute A = X^T * X
    Matrix A = XT.multiply(X);

    // 3. Compute b = X^T * y
    Matrix b = XT.multiply(y);

    // 4. Solve the linear system A * w = b for w
    return solve_linear_system(A, b);
}

Matrix NormalSolver::solve_linear_system(const Matrix& A, const Matrix& b) {
    // Assumes Matrix class provides rows(), cols(), get(r,c), set(r,c) methods
    int n = A.rows();
    
    // Create augmented-like working copies since we need to modify values
    Matrix M = A; 
    Matrix x_vec = b; 

    // Gaussian Elimination with Partial Pivoting
    for (int i = 0; i < n; ++i) {
        // Find the pivot row
        int max_row = i;
        double max_val = std::abs(M.get(i, i));
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(M.get(k, i)) > max_val) {
                max_val = std::abs(M.get(k, i));
                max_row = k;
            }
        }

        // Check for singularity (near zero pivot element)
        if (max_val < 1e-9) {
            throw SingularMatrixException();
        }

        // Swap rows in M and x_vec if needed
        if (max_row != i) {
            for (int j = 0; j < n; ++j) {
                double temp = M.get(i, j);
                M.set(i, j, M.get(max_row, j));
                M.set(max_row, j, temp);
            }
            double temp_b = x_vec.get(i, 0);
            x_vec.set(i, 0, x_vec.get(max_row, 0));
            x_vec.set(max_row, 0, temp_b);
        }

        // Eliminate lower rows
        for (int k = i + 1; k < n; ++k) {
            double factor = M.get(k, i) / M.get(i, i);
            for (int j = i; j < n; ++j) {
                double val = M.get(k, j) - factor * M.get(i, j);
                M.set(k, j, val);
            }
            double val_b = x_vec.get(k, 0) - factor * x_vec.get(i, 0);
            x_vec.set(k, 0, val_b);
        }
    }

    // Back Substitution
    // Assuming Person 1's Matrix constructor allocates dimensions properly
    Matrix w(n, 1); 
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += M.get(i, j) * w.get(j, 0);
        }
        double weight = (x_vec.get(i, 0) - sum) / M.get(i, i);
        w.set(i, 0, weight);
    }

    return w;
}

} // namespace linear_ml

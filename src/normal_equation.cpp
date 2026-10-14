#include "../include/Group-7-project-ridge-lib/normal_equation.hpp"
#include <cmath>
#include <stdexcept>

namespace ridge {

Vector gaussian_solve(const Matrix& A, const Vector& b) {
    if (A.rows()!= A.cols())
        throw std::invalid_argument("gaussian_solve: A must be square");
    if (A.rows()!= b.size())
        throw std::invalid_argument("gaussian_solve: size mismatch");

    size_t n = A.rows();
    // Make augmented matrix copy [A|b]
    Matrix aug(n, n+1);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) aug(i,j) = A(i,j);
        aug(i,n) = b[i];
    }

    // Forward elimination with partial pivoting
    for (size_t k = 0; k < n; ++k) {
        // Find max pivot
        size_t max_row = k;
        double max_val = std::abs(aug(k,k));
        for (size_t i = k+1; i < n; ++i) {
            if (std::abs(aug(i,k)) > max_val) {
                max_val = std::abs(aug(i,k));
                max_row = i;
            }
        }
        if (max_val < 1e-12)
            throw std::runtime_error("Singular matrix - XtX not invertible");

        // Swap rows
        if (max_row!= k) {
            for (size_t j = k; j <= n; ++j)
                std::swap(aug(k,j), aug(max_row,j));
        }

        // Eliminate
        for (size_t i = k+1; i < n; ++i) {
            double factor = aug(i,k) / aug(k,k);
            for (size_t j = k; j <= n; ++j)
                aug(i,j) -= factor * aug(k,j);
        }
    }

    // Back substitution
    Vector x(n);
    for (int i = (int)n-1; i >= 0; --i) {
        double sum = aug(i,n);
        for (size_t j = i+1; j < n; ++j)
            sum -= aug(i,j) * x[j];
        x[i] = sum / aug(i,i);
    }
    return x;
}

Vector fit_normal_equation(const Matrix& X, const Vector& y) {
    // theta = (X^T X)^-1 X^T y - using Person 1's API
    Matrix Xt = X.transpose(); // Person 1
    Matrix XtX = Xt * X; // Person 1: (n x m) * (m x n) = n x n
    Vector Xty = Xt.multiply(y); // Person 1: (n x m) * (m) = n

    return gaussian_solve(XtX, Xty); // My solver
}

}

#pragma once
#include "linear_ml/matrix.hpp" 
#include <stdexcept>

namespace linear_ml {

/**
 * @brief Custom runtime exception thrown when the design matrix structure 
 * cannot be reliably decomposed due to numerical singularity.
 */
class SingularMatrixException : public std::runtime_error {
public:
    SingularMatrixException() 
        : std::runtime_error("Normal Equation Error: System matrix (X^T * X) is singular or near-singular. Inverse cannot be found.") {}
};

class NormalSolver {
public:
    /**
     * @brief Solves the classic closed-form Normal Equation: (X^T * X) * w = X^T * y
     * @param X Feature matrix dimensions (N x M)
     * @param y Targets matching vector matrix dimensions (N x 1)
     * @return Matrix Vector matching coefficients (M x 1)
     * @throws SingularMatrixException if system has no unique analytical solution
     */
    static Matrix solve_normal_equation(const Matrix& X, const Matrix& y);

private:
    /**
     * @brief Computes explicit system solving using Gaussian Elimination with partial pivoting
     * @param A Square linear combinations system matrix (M x M)
     * @param b Transformed target projections vector matrix (M x 1)
     * @return Matrix Solution weight coefficients vector (M x 1)
     */
    static Matrix solve_linear_system(const Matrix& A, const Matrix& b);
};

} 

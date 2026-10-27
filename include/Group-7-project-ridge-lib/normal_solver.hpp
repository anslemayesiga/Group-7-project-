#pragma once

#include "Group-7-project-ridge-lib/matrix.hpp"

#include <stdexcept>

namespace linear_ml {

// Preserve the original namespace/API while using RidgeLib's matrix type.
using Matrix = ridge_ml::Matrix;

// Thrown when the normal-equation matrix has no reliable unique solution.
class SingularMatrixException : public std::runtime_error {
public:
    SingularMatrixException()
        : std::runtime_error("Normal equation system is singular or near-singular") {}
};

class NormalSolver {
public:
    // Solve the normal equation for a target supplied as an N-by-1 matrix.
    static Matrix solve_normal_equation(const Matrix& X, const Matrix& y);
};

} // namespace linear_ml

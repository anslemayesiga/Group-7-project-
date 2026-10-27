#ifndef RIDGE_ML_NORMAL_EQUATION_HPP
#define RIDGE_ML_NORMAL_EQUATION_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"

namespace ridge_ml {

// Solve a square linear system A x = b using Gaussian elimination.
Vector gaussian_solve(const Matrix& matrix, const Vector& right_hand_side);

// Solve ordinary least squares. Add a column of ones to features for an intercept.
Vector fit_normal_equation(const Matrix& features, const Vector& targets);

} // namespace ridge_ml

#endif // RIDGE_ML_NORMAL_EQUATION_HPP

#ifndef RIDGE_ML_NORMAL_EQUATION_HPP
#define RIDGE_ML_NORMAL_EQUATION_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"

namespace ridge_ml {

// Solves A x = b using Gaussian elimination with partial pivoting.
Vector gaussian_solve(const Matrix& matrix, const Vector& right_hand_side);

// Computes the unregularized normal equation. Include a column of ones in X
// when the caller wants an intercept term.
Vector fit_normal_equation(const Matrix& features, const Vector& targets);

} // namespace ridge_ml

#endif // RIDGE_ML_NORMAL_EQUATION_HPP

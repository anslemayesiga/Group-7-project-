#include "Group-7-project-ridge-lib/normal_solver.hpp"

#include "Group-7-project-ridge-lib/normal_equation.hpp"

namespace linear_ml {

// Keep the legacy matrix-shaped API while sharing RidgeLib's tested solver.
ridge_ml::Matrix NormalSolver::solve_normal_equation(
    const ridge_ml::Matrix& X, const ridge_ml::Matrix& y) {
    // Preserve clear shape errors before passing data to the shared solver.
    if (X.rows() != y.rows()) {
        throw std::invalid_argument("Feature and target row counts must match");
    }
    if (y.cols() != 1) {
        throw std::invalid_argument("Targets must be a single-column matrix");
    }

    try {
        // The shared solver accepts targets as a vector, so extract column zero.
        const ridge_ml::Vector coefficients =
            ridge_ml::fit_normal_equation(X, y.column(0));
        // Restore the legacy API's column-matrix result.
        return ridge_ml::Matrix(coefficients.size(), 1, coefficients);
    } catch (const std::runtime_error&) {
        // Translate the shared solver's singular-system error to the legacy type.
        throw SingularMatrixException();
    }
}

} // namespace linear_ml

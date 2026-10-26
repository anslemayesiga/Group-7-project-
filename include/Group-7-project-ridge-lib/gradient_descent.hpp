#ifndef GROUP_7_PROJECT_RIDGE_LIB_GRADIENT_DESCENT_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_GRADIENT_DESCENT_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"

#include <cstddef>

namespace ridge_ml {

// Captures the fitted parameters and progress made by gradient descent.
struct GradientDescentResult {
    // Final model coefficients, in the same order as design columns.
    Vector parameters;
    // Objective value recorded at each completed iteration.
    Vector cost_history;
    // Number of iterations completed before stopping.
    std::size_t iterations_run = 0;
    // True only when tolerance-based early stopping occurred.
    bool converged = false;
};

class GradientDescent {
public:
    // tolerance is an absolute change-in-cost threshold; zero disables early stopping.
    // The design matrix should include an intercept as its first column.
    GradientDescent(double learning_rate, std::size_t iterations, double lambda = 0.0,
                    double tolerance = 0.0);
    // Start from zero parameters when initial_parameters is omitted.
    GradientDescentResult fit(const Matrix& design, const Vector& targets,
                              Vector initial_parameters = {}) const;

private:
    double learning_rate_;
    std::size_t iterations_;
    double lambda_;
    double tolerance_;
};

} // namespace ridge_ml

#endif // GROUP_7_PROJECT_RIDGE_LIB_GRADIENT_DESCENT_HPP

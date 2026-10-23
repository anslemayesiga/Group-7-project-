#ifndef GROUP_7_PROJECT_RIDGE_LIB_GRADIENT_DESCENT_HPP
#define GROUP_7_PROJECT_RIDGE_LIB_GRADIENT_DESCENT_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"

#include <cstddef>

namespace ridge_ml {

struct GradientDescentResult {
    Vector parameters;
    Vector cost_history;
    std::size_t iterations_run = 0;
    bool converged = false;
};

class GradientDescent {
public:
    // tolerance is an absolute change-in-cost threshold; zero disables early stopping.
    GradientDescent(double learning_rate, std::size_t iterations, double lambda = 0.0,
                    double tolerance = 0.0);
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

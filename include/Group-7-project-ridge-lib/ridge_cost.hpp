#ifndef RIDGE_ML_RIDGE_COST_HPP
#define RIDGE_ML_RIDGE_COST_HPP

#include "Group-7-project-ridge-lib/matrix.hpp"

namespace ridge_ml {

// Return squared-error cost plus an L2 penalty; theta[0] is the unpenalized
// intercept and all later parameters are treated as feature coefficients.
// actual and predicted must have equal non-zero lengths; lambda must be non-negative.
double ridge_cost(
    const Vector& actual,
    const Vector& predicted,
    const Vector& theta,
    double lambda
);

} // namespace ridge_ml

#endif // RIDGE_ML_RIDGE_COST_HPP
